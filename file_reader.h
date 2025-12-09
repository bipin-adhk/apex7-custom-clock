/*
 * file_reader.h - File reader interface
 * Project: apex7-custom-clock
 * Author: Bipin Adhikari
 * Description: Read and parse SteelSeries configuration
 */

#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdbool.h>
#include <stddef.h>

// Read destination address from SteelSeries config file
// Returns true on success, false on failure
bool read_destination_address(const char* config_path, char* dest_buffer, size_t buffer_size);

#endif // FILE_READER_H
