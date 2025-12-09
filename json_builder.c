/*
 * json_builder.c - JSON builder implementation
 * Project: apex7-custom-clock
 * Author: Bipin Adhikari
 * Description: JSON payload construction using manual string building
 */

#include "json_builder.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* build_register_event_json(void) {
    char* json = (char*)malloc(JSON_SIZE);
    if (!json) {
        return NULL;
    }

    snprintf(json, JSON_SIZE,
        "{"
        "\"game\":\"%s\","
        "\"event\":\"%s\","
        "\"min_value\":0,"
        "\"max_value\":59,"
        "\"value_optional\":true"
        "}",
        GAME_NAME, EVENT_NAME);

    return json;
}

char* build_bind_event_json(void) {
    char* json = (char*)malloc(JSON_SIZE);
    if (!json) {
        return NULL;
    }

    snprintf(json, JSON_SIZE,
        "{"
        "\"game\":\"%s\","
        "\"event\":\"%s\","
        "\"min_value\":0,"
        "\"max_value\":59,"
        "\"value_optional\":true,"
        "\"handlers\":["
        "{"
        "\"device-type\":\"screened\","
        "\"zone\":\"one\","
        "\"mode\":\"screen\","
        "\"datas\":["
        "{"
        "\"lines\":["
        "{"
        "\"has-text\":true,"
        "\"context-frame-key\":\"time_line\","
        "\"bold\":true"
        "},"
        "{"
        "\"has-text\":true,"
        "\"context-frame-key\":\"date_line\","
        "\"bold\":false"
        "}"
        "]"
        "}"
        "]"
        "}"
        "]"
        "}",
        GAME_NAME, EVENT_NAME);

    return json;
}

char* build_game_event_json(const char* time_line, const char* date_line) {
    char* json = (char*)malloc(JSON_SIZE);
    if (!json) {
        return NULL;
    }

    snprintf(json, JSON_SIZE,
        "{"
        "\"game\":\"%s\","
        "\"event\":\"%s\","
        "\"data\":{"
        "\"value\":15,"
        "\"frame\":{"
        "\"time_line\":\"%s\","
        "\"date_line\":\"%s\""
        "}"
        "}"
        "}",
        GAME_NAME, EVENT_NAME, time_line, date_line);

    return json;
}
