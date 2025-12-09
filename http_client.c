/*
 * http_client.c - HTTP client implementation
 * Project: apex7-custom-clock
 * Author: Bipin Adhikari
 * Description: HTTP POST using Windows WinHTTP API (no external dependencies)
 */

#include "http_client.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winhttp.h>

#pragma comment(lib, "winhttp.lib")

bool http_client_init(void) {
    // No initialization needed for WinHTTP
    return true;
}

void http_client_cleanup(void) {
    // No cleanup needed
}

bool http_post(const char* url, const char* json_data) {
    if (!url || !json_data) {
        return false;
    }

    // Parse URL to extract host and path
    // Expected format: "http://127.0.0.1:PORT/path"
    char host[256] = {0};
    char path[512] = {0};
    int port = 0;

    // Skip "http://"
    const char* url_start = url;
    if (strncmp(url, "http://", 7) == 0) {
        url_start += 7;
    }

    // Extract host and port
    const char* path_start = strchr(url_start, '/');
    if (path_start) {
        size_t host_len = path_start - url_start;
        if (host_len >= sizeof(host)) {
            host_len = sizeof(host) - 1;
        }
        strncpy(host, url_start, host_len);
        host[host_len] = '\0';
        strncpy(path, path_start, sizeof(path) - 1);
    } else {
        strncpy(host, url_start, sizeof(host) - 1);
        strcpy(path, "/");
    }

    // Extract port from host
    char* colon = strchr(host, ':');
    if (colon) {
        *colon = '\0';
        port = atoi(colon + 1);
    } else {
        port = 80;
    }

    // Convert host to wide string
    wchar_t whost[256];
    MultiByteToWideChar(CP_UTF8, 0, host, -1, whost, 256);

    wchar_t wpath[512];
    MultiByteToWideChar(CP_UTF8, 0, path, -1, wpath, 512);

    // Initialize WinHTTP
    HINTERNET hSession = WinHttpOpen(L"SteelSeries Clock/1.0",
                                      WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                      WINHTTP_NO_PROXY_NAME,
                                      WINHTTP_NO_PROXY_BYPASS,
                                      0);
    if (!hSession) {
        return false;
    }

    // Connect to server
    HINTERNET hConnect = WinHttpConnect(hSession, whost, port, 0);
    if (!hConnect) {
        WinHttpCloseHandle(hSession);
        return false;
    }

    // Open request
    HINTERNET hRequest = WinHttpOpenRequest(hConnect,
                                             L"POST",
                                             wpath,
                                             NULL,
                                             WINHTTP_NO_REFERER,
                                             WINHTTP_DEFAULT_ACCEPT_TYPES,
                                             0);
    if (!hRequest) {
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return false;
    }

    // Set headers
    LPCWSTR headers = L"Content-Type: application/json\r\n";
    
    // Send request
    DWORD data_len = (DWORD)strlen(json_data);
    BOOL result = WinHttpSendRequest(hRequest,
                                      headers,
                                      -1,
                                      (LPVOID)json_data,
                                      data_len,
                                      data_len,
                                      0);

    bool success = false;
    if (result) {
        result = WinHttpReceiveResponse(hRequest, NULL);
        if (result) {
            DWORD status_code = 0;
            DWORD size = sizeof(DWORD);
            WinHttpQueryHeaders(hRequest,
                                WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
                                NULL,
                                &status_code,
                                &size,
                                NULL);
            
            success = (status_code == 200);
        }
    }

    // Cleanup
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return success;
}
