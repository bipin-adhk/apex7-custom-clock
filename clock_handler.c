/*
 * clock_handler.c - Clock handler implementation
 * Project: apex7-custom-clock
 * Author: Bipin Adhikari
 * Description: Main clock logic and event loop
 */

#include "clock_handler.h"
#include "config.h"
#include "http_client.h"
#include "time_formatter.h"
#include "json_builder.h"
#include "file_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

ClockHandler* clock_handler_create(void) {
    ClockHandler* handler = (ClockHandler*)malloc(sizeof(ClockHandler));
    if (!handler) {
        return NULL;
    }

    memset(handler->destination_address, 0, sizeof(handler->destination_address));
    handler->update_interval_ms = UPDATE_INTERVAL_MS;
    handler->registered = false;

    return handler;
}

void clock_handler_destroy(ClockHandler* handler) {
    if (handler) {
        free(handler);
    }
}

bool clock_handler_initialize(ClockHandler* handler) {
    // Read destination address from SteelSeries config
    if (!read_destination_address(SSE_CONFIG_PATH, handler->destination_address, 
                                   sizeof(handler->destination_address))) {
        fprintf(stderr, "Failed to read SteelSeries Engine configuration\n");
        return false;
    }

    printf("Destination: %s\n", handler->destination_address);

    // Try to bind event
    char url[URL_SIZE];
    snprintf(url, sizeof(url), "http://%s%s", handler->destination_address, BIND_GAME_EVENT_PATH);

    char* bind_json = build_bind_event_json();
    if (!bind_json) {
        return false;
    }

    bool success = http_post(url, bind_json);
    free(bind_json);

    if (success) {
        handler->registered = true;
        return true;
    }

    // If bind failed, try register
    snprintf(url, sizeof(url), "http://%s%s", handler->destination_address, REGISTER_GAME_EVENT_PATH);

    char* register_json = build_register_event_json();
    if (!register_json) {
        return false;
    }

    success = http_post(url, register_json);
    free(register_json);

    if (success) {
        handler->registered = true;
    }

    return success;
}

void clock_handler_main_loop(ClockHandler* handler) {
    int fail_count = 0;
    char url[URL_SIZE];
    char time_line[TIME_STRING_SIZE];
    char date_line[TIME_STRING_SIZE];

    snprintf(url, sizeof(url), "http://%s%s", handler->destination_address, GAME_EVENT_PATH);

    while (1) {
        if (fail_count > MAX_FAIL_COUNT) {
            fprintf(stderr, "Too many failures, restarting...\n");
            break;
        }

        // Format current time and date
        format_time_hms(time_line, sizeof(time_line));
        format_date_ymd(date_line, sizeof(date_line));

        // Build JSON payload
        char* json = build_game_event_json(time_line, date_line);
        if (!json) {
            fail_count++;
            Sleep(handler->update_interval_ms);
            continue;
        }

        // Send to SteelSeries
        bool success = http_post(url, json);
        free(json);

        if (!success) {
            fail_count++;
        } else {
            fail_count = 0;
        }

        Sleep(handler->update_interval_ms);
    }
}

int clock_handler_run(ClockHandler* handler) {
    if (!handler) {
        return 1;
    }

    while (1) {
        if (!clock_handler_initialize(handler)) {
            fprintf(stderr, "Initialization failed, retrying in 30 seconds...\n");
            Sleep(RESTART_DELAY_MS);
            continue;
        }

        printf("Clock started successfully\n");
        clock_handler_main_loop(handler);

        // If we exit the main loop, reinitialize
        Sleep(RESTART_DELAY_MS);
    }

    return 0;
}
