#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "collections.h"
#include "console.h"
#include "events.h"
#include "color_print.h"

const char* ON_CHAT_EVENT_NAME = "on_chat";

bool is_printable(const char* message) {
    // Validate the input message
    for (int i = 0; message[i] != 0; ++i) {
        // There were some unrecognized escape sequences getting through the 'isprint' function.
        // This isn't very pretty, but helps us get around that. Before, the 
        // string ' \"\'\p\t '" would cause a seg fault when entered into the console and it
        // managed to get past isprint. Now it works as expected.
        if (message[i] == '\\') {
            if (message[i + 1] != 0 && strchr("abfnrtv\\\'\"", message[i + 1]) == NULL) {
                return false;
            } else {
                ++i;  // Skip the next character (the recognized escape sequence)
            }
        } else if (!isprint(message[i])) {
            return false;
        }
    }
    return true;
}



// create in main
HashMap* __commands;

int register_command(char* name, char* description, char* usage, CommandCallback callback) {
    Command* command = (Command*)malloc(sizeof(Command));
    // Check if malloc failed
    if (command == NULL) {
        return -1;
    }
    command->name = name;
    command->description = description;
    command->callback = callback;
    command->usage = usage;
    hash_map_put(__commands, name, command);
    return 0;
}

void _command_help(char* command_name, char** args) {
    print_colored(COLOR_PRINT_YELLOW ,"Commands:\n");
    set_text_color(COLOR_PRINT_MAGENTA);
    for (int i = 0; i < __commands->size; i++) {
        if (__commands->table[i] != NULL) {
            Command* command = (Command*)__commands->table[i]->value;
            printf("  %s - %s\n", command->usage, command->description);
        }
    }
    puts("");
    reset_text_color();
}

void _command_not_found(char* command_name, char** args){
    print_colored(COLOR_PRINT_RED ,"Command \"%s\" not found.\n", command_name);
    print_colored(COLOR_PRINT_MAGENTA ,"Use 'help' for usage examples.\n");
}

char** _command_parse(const char *input) {
    char *str = strdup(input);
    int capacity = 10;
    char **words = (char **)malloc(capacity * sizeof(char *));
    int count = 0;
    bool in_quotes = false;
    char *start = str;
    bool last_char_space = true;

    for (char *ptr = str; *ptr != '\0'; ++ptr) {
        if (*ptr == '\"') {
            in_quotes = !in_quotes;
            if (in_quotes) {
                start = ptr + 1;
            } else {
                *ptr = '\0';
                words[count++] = strdup(start);
                last_char_space = true;
            }
        } else if (*ptr == ' ' && !in_quotes) {
            *ptr = '\0';
            if (!last_char_space && start != ptr) {
                words[count++] = strdup(start);
            }
            start = ptr + 1;
            last_char_space = true;
        } else {
            last_char_space = false;
        }

        if (count == capacity) {
            capacity *= 2;
            words = (char **)realloc(words, capacity * sizeof(char *));
        }
    }

    if (!in_quotes && start != str + strlen(str) && !last_char_space) {
        words[count++] = strdup(start);
    }
    words[count] = NULL;

    free(str);
    return words;
}

char** get_and_parse_input(char* prompt) {
    char message[MAX_MESSAGE_LENGTH];
    print_colored(COLOR_PRINT_GREEN, "%s", prompt);
    fgets(message, MAX_MESSAGE_LENGTH, stdin);

    // Check if nothing was entered
    if (message[0] == '\n') {
        puts("Nothing was entered.");
        return get_and_parse_input();
    }

    // Remove newline character from the input
    message[strcspn(message, "\n")] = 0;

    if (!is_printable(message)) {
        puts("Contains invalid characters.");
        return get_and_parse_input();
    }

    return _command_parse(message);
}

void _handle_on_chat(va_list args) {
    char** split_message = va_arg(args, char**);
    char* command_name = split_message[0];
    char** command_args = split_message + 1;

    // Get the command from the hash map and call its callback
    Command* command = (Command*)hash_map_get(__commands, command_name);

    if (command != NULL) {
        command->callback(command_name, command_args);
    }
    else {
        _command_not_found(command_name, command_args);
    }
}

// Internal function for the chat console loop
void start_console_loop() {
    // Main loop
    while (1) {
        char** split_message = get_and_parse_input("Enter a command: ");

        if (split_message == NULL) {
            continue;
        }

        char* command_name = split_message[0];
        if (strcmp(command_name, "exit") == 0) {
            break;
        }
        else {
            // Trigger the on_chat event with the input message
            trigger_event("on_chat", split_message);
        }
    }
}

void init_console() {
    // Create the on_chat event
    create_event(ON_CHAT_EVENT_NAME);
    register_callback(ON_CHAT_EVENT_NAME, (Callback)_handle_on_chat);
    __commands = hash_map_create(100);

    int help = register_command("help", "Displays a list of commands.", "help", _command_help);
    int exit = register_command("exit", "Exits the program.", "exit", _command_not_found);
    if (help != 0 || exit != 0) {
        print_colored(COLOR_PRINT_RED, "Failed to register commands.\n");
    }
}