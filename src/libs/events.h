/**
 * @file events.h
 * @brief This header file contains the declarations of functions and structs for event handling.
 */

#ifndef EVENTS_H
#define EVENTS_H

#include <stdarg.h> // for va_list

#include "collections.h"

/**
 * @typedef Callback
 * @brief A function pointer type for callbacks.
 * @param args The arguments for the callback function.
 */
typedef void (*Callback)(va_list args);

/**
 * @struct __Event
 * @brief An event structure that stores callbacks.
 */
typedef struct {
    char* name; /**< The name of the event */
    LinkedList* callbacks; /**< The linked list of function pointers to callbacks */
} Event;

/**
 * @brief Creates a new event with the specified name.
 * 
 * @param event_name The name of the event to create.
 */
void create_event(const char* event_name);

/**
 * @brief Destroys the event with the specified name.
 * 
 * @param event_name The name of the event to destroy.
 * @return 0 if the event was successfully destroyed, or -1 if the event was not found.
 */
int destroy_event(const char* event_name);

/**
 * @brief Registers a callback function to the event with the specified name.
 * 
 * @param event_name The name of the event to register the callback to.
 * @param callback The callback function to register.
 * @return 0 if the callback was successfully registered, or -1 if the event was not found or the callback was already registered.
 */
int register_callback(const char* event_name, Callback callback);

/**
 * @brief Unregisters a callback function from the event with the specified name.
 * 
 * @param event_name The name of the event to unregister the callback from.
 * @param callback The callback function to unregister.
 * @return 0 if the callback was successfully unregistered, or -1 if the event was not found or the callback was not registered.
 */
int unregister_callback(const char* event_name, Callback callback);

/**
 * @brief Triggers the event with the specified name and passes in the specified arguments.
 * 
 * @param event_name The name of the event to trigger.
 * @param ... The arguments to pass to the callbacks.
 * @return The number of callbacks that were successfully triggered.
 */
int trigger_event(const char* event_name, ...);

#endif // EVENTS_H
