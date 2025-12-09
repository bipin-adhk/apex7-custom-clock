/*
 * main.c - Custom OLED Clock for SteelSeries Apex 7
 * Project: apex7-custom-clock
 * Author: Bipin Adhikari
 * Description: Main entry point and initialization
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "clock_handler.h"
#include "config.h"

int main(void) {
    // Hide console window for silent operation
    #ifdef RELEASE_BUILD
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_HIDE);
    #endif

    printf("Custom OLED Clock for SteelSeries Apex 7\n");
    printf("Version 1.0.0 by Bipin Adhikari\n\n");

    // Initialize clock handler
    ClockHandler* handler = clock_handler_create();
    if (!handler) {
        fprintf(stderr, "Failed to initialize clock handler\n");
        return 1;
    }

    // Start the main loop
    int result = clock_handler_run(handler);

    // Cleanup
    clock_handler_destroy(handler);

    return result;
}
