/*
 * file_reader.c - File reader implementation
 * Project: apex7-custom-clock
 * Author: Bipin Adhikari
 * Description: Read and parse SteelSeries JSON config file
 */

#include "file_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple JSON parser to extract "address" field
static bool extract_address_from_json(const char* json_content, char* dest_buffer, size_t buffer_size) {
    // Look for "address":"VALUE"
    const char* address_key = "\"address\"";
    const char* found = strstr(json_content, address_key);
    
    if (!found) {
        return false;
    }

    // Skip past the key
    found += strlen(address_key);

    // Skip whitespace and colon
    while (*found && (*found == ' ' || *found == '\t' || *found == ':')) {
        found++;
    }

    // Should be at opening quote
    if (*found != '"') {
        return false;
    }
    found++; // Skip opening quote

    // Extract value until closing quote
    size_t i = 0;
    while (*found && *found != '"' && i < buffer_size - 1) {
        dest_buffer[i++] = *found++;
    }
    dest_buffer[i] = '\0';

    return (i > 0);
}

bool read_destination_address(const char* config_path, char* dest_buffer, size_t buffer_size) {
    if (!config_path || !dest_buffer || buffer_size == 0) {
        return false;
    }

    // Open file
    FILE* file = fopen(config_path, "r");
    if (!file) {
        fprintf(stderr, "Failed to open config file: %s\n", config_path);
        return false;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size <= 0 || file_size > 1024 * 1024) { // Max 1MB
        fclose(file);
        return false;
    }

    // Read file content
    char* content = (char*)malloc(file_size + 1);
    if (!content) {
        fclose(file);
        return false;
    }

    size_t read_size = fread(content, 1, file_size, file);
    content[read_size] = '\0';
    fclose(file);

    // Parse JSON
    bool success = extract_address_from_json(content, dest_buffer, buffer_size);

    free(content);
    return success;
}
