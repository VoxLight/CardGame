#ifndef CONSOLE_H
#define CONSOLE_H

#include "stdbool.h"

#define MAX_MESSAGE_LENGTH 1024

extern const char* ON_CHAT_EVENT_NAME;

typedef void (*CommandCallback)(char* command_name, char** args);

typedef struct {
    char* name;
    char* description;
    char* usage;
    CommandCallback callback;
} Command;

int register_command(char* name, char* description, char* usage, CommandCallback callback);
bool is_printable(const char* message);

void init_console(); // Initialize and start the console
void start_console_loop(); // Main loop for the console

#endif // CONSOLE_H
