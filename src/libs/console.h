/**
 * @file console.h
 * @brief This header file contains the declarations of functions and structs for a console interface.
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include "stdbool.h"

#define MAX_MESSAGE_LENGTH 1024 /**< The maximum length of a console message */

extern const char* ON_CHAT_EVENT_NAME; /**< The name of the chat event */

/**
 * @brief A function pointer to a command callback function.
 * 
 * @param command_name The name of the command that was executed.
 * @param args An array of arguments passed to the command.
 */
typedef void (*CommandCallback)(char* command_name, char** args);

/**
 * @struct Command
 * @brief A console command.
 */
typedef struct {
    char* name; /**< The name of the command */
    char* description; /**< A brief description of the command */
    char* usage; /**< The usage syntax of the command */
    CommandCallback callback; /**< A pointer to the command's callback function */
} Command;

/**
 * @brief Registers a new command with the console.
 * 
 * @param name The name of the command.
 * @param description A brief description of the command.
 * @param usage The usage syntax of the command.
 * @param callback A pointer to the command's callback function.
 * @return 0 if the command was successfully registered, or -1 if an error occurred.
 */
int register_command(char* name, char* description, char* usage, CommandCallback callback);

/**
 * @brief Checks whether the specified message is printable (contains only printable ASCII characters).
 * 
 * @param message The message to check.
 * @return true if the message is printable, false otherwise.
 */
bool is_printable(const char* message);

/**
 * @brief Initializes and starts the console interface.
 */
void init_console();

/**
 * @brief Starts the main loop for the console interface.
 */
void start_console_loop();

#endif // CONSOLE_H
