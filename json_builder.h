/*
 * json_builder.h - JSON builder interface
 * Project: apex7-custom-clock
 * Author: Bipin Adhikari
 * Description: JSON payload construction
 */

#ifndef JSON_BUILDER_H
#define JSON_BUILDER_H

// Build JSON for registering event
char* build_register_event_json(void);

// Build JSON for binding event with handlers
char* build_bind_event_json(void);

// Build JSON for game event with time/date data
char* build_game_event_json(const char* time_line, const char* date_line);

#endif // JSON_BUILDER_H
