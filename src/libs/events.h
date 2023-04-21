#ifndef EVENTS_H
#define EVENTS_H

#include <stdarg.h> // for va_list

#include "collections.h"

typedef void (*Callback)(va_list args);

// Event structure
typedef struct {
    char* name; // name of the event
    LinkedList callbacks; // linked list of function pointers to callbacks
} __Event;

void create_event(const char* event_name); // create a new event from the event name
int destroy_event(const char* event_name); // destroy an event

int register_callback(const char* event_name, Callback callback); // register a callback function to an event
int unregister_callback(const char* event_name, Callback callback); // unregister a callback from an event

int trigger_event(const char* event_name, ...); // trigger an event with the given arguments

#endif // EVENTS_H
