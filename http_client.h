/*
 * http_client.h - HTTP client interface
 * Project: apex7-custom-clock
 * Author: Bipin Adhikari
 * Description: HTTP POST request handling
 */

#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <stdbool.h>

// Initialize HTTP client (call once at startup)
bool http_client_init(void);

// Cleanup HTTP client (call at shutdown)
void http_client_cleanup(void);

// Send HTTP POST request
// Returns true on success (HTTP 200), false otherwise
bool http_post(const char* url, const char* json_data);

#endif // HTTP_CLIENT_H
