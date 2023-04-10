#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "collections.h"
#include "events.h"

HashMap *__events; // hash map of events

__Event *find_event_by_name(const char *event_name) {
    return (__Event *)hash_map_get(__events, event_name);
}

#define do_check_event_not_found(exit_code) \
    do {                                     \
        if (event == NULL)                   \
            return exit_code;                \
    } while (0)

void create_event(const char *event_name) {
    if (__events == NULL) {
        __events = hash_map_create(100);
    }

    __Event *event = (__Event *)malloc(sizeof(__Event));
    event->name = strdup(event_name);
    event->callbacks = create_linked_list();
    hash_map_put(__events, event_name, event);
}

int destroy_event(const char *event_name) {
    __Event *event = find_event_by_name(event_name);
    do_check_event_not_found(-2);

    free(event->name);
    destroy_linked_list(&event->callbacks);
    hash_map_remove(__events, event_name);
    free(event);
    return 0;
}

int register_callback(const char *event_name, Callback callback) {
    __Event *event = find_event_by_name(event_name);
    do_check_event_not_found(-2);
    Callback *callback_ptr = (Callback *)malloc(sizeof(Callback));
    *callback_ptr = callback;
    linked_list_append(&event->callbacks, callback_ptr);
    return 0;
}

int unregister_callback(const char *event_name, Callback callback) {
    __Event *event = find_event_by_name(event_name);
    do_check_event_not_found(-2);

    LinkedListNode *callback_node = event->callbacks.head;
    int index = 0;
    while (callback_node != NULL) {
        Callback *callback_ptr = (Callback *)callback_node->data;
        if (*callback_ptr == callback) {
            linked_list_remove(&event->callbacks, index);
            free(callback_ptr);
            return 0;
        }
        index++;
        callback_node = callback_node->next;
    }
    return 0;
}

int trigger_event(const char *event_name, ...) {
    __Event *event = find_event_by_name(event_name);
    do_check_event_not_found(-2);
    LinkedListNode *callback_node = event->callbacks.head;
    while (callback_node != NULL) {
        Callback *callback_ptr = (Callback *)callback_node->data;
        va_list args;
        va_start(args, event_name);
        (*callback_ptr)(args);
        va_end(args);
        callback_node = callback_node->next;
    }
    return 0;
}
