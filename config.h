/*
 * config.h - Configuration constants
 * Project: apex7-custom-clock
 * Author: Bipin Adhikari
 * Description: Global configuration and constants
 */

#ifndef CONFIG_H
#define CONFIG_H

// SteelSeries Engine paths
#define SSE_CONFIG_PATH "C:\\ProgramData\\SteelSeries\\SteelSeries Engine 3\\coreProps.json"

// API endpoints
#define REGISTER_GAME_EVENT_PATH "/register_game_event"
#define BIND_GAME_EVENT_PATH "/bind_game_event"
#define GAME_EVENT_PATH "/game_event"
#define REMOVE_GAME_EVENT_PATH "/remove_game_event"

// Game/Event names
#define GAME_NAME "CLOCK"
#define EVENT_NAME "TIME"
#define DISPLAY_NAME "Custom Clock"
#define DEVELOPER_NAME "Bipin Adhikari"

// Timing
#define UPDATE_INTERVAL_MS 1000  // 1 second
#define MAX_FAIL_COUNT 30
#define RETRY_DELAY_MS 5000
#define RESTART_DELAY_MS 30000

// Buffer sizes
#define BUFFER_SIZE 4096
#define TIME_STRING_SIZE 32
#define URL_SIZE 256
#define JSON_SIZE 2048

#endif // CONFIG_H
