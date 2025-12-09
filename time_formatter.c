/*
 * time_formatter.c - Time formatting implementation
 * Project: apex7-custom-clock
 * Author: Bipin Adhikari
 * Description: Time and date formatting logic
 */

#include "time_formatter.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

void format_time_hms(char* buffer, size_t buffer_size) {
    time_t now = time(NULL);
    struct tm* local_time = localtime(&now);

    snprintf(buffer, buffer_size, "%02d:%02d:%02d",
             local_time->tm_hour,
             local_time->tm_min,
             local_time->tm_sec);
}

void format_date_ymd(char* buffer, size_t buffer_size) {
    time_t now = time(NULL);
    struct tm* local_time = localtime(&now);

    const char* month_names[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    snprintf(buffer, buffer_size, "%04d/%s/%02d",
             local_time->tm_year + 1900,
             month_names[local_time->tm_mon],
             local_time->tm_mday);
}
