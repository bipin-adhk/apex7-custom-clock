/*
 * clock_handler.h - Clock handler interface
 * Project: apex7-custom-clock
 * Author: Bipin Adhikari
 * Description: Main clock handler declarations
 */

#ifndef CLOCK_HANDLER_H
#define CLOCK_HANDLER_H

#include <stdbool.h>

// Clock handler structure
typedef struct {
    char destination_address[256];
    int update_interval_ms;
    bool registered;
} ClockHandler;

// Function declarations
ClockHandler* clock_handler_create(void);
void clock_handler_destroy(ClockHandler* handler);
int clock_handler_run(ClockHandler* handler);
bool clock_handler_initialize(ClockHandler* handler);
void clock_handler_main_loop(ClockHandler* handler);

#endif // CLOCK_HANDLER_H
