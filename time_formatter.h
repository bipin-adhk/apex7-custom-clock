/*
 * time_formatter.h - Time formatting interface
 * Project: apex7-custom-clock
 * Author: Bipin Adhikari
 * Description: Time and date formatting functions
 */

#ifndef TIME_FORMATTER_H
#define TIME_FORMATTER_H

#include <stddef.h>

// Format time as "HH:MM:SS"
void format_time_hms(char* buffer, size_t buffer_size);

// Format date as "YYYY/MMM/DD"
void format_date_ymd(char* buffer, size_t buffer_size);

#endif // TIME_FORMATTER_H
