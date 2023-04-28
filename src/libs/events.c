#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "collections.h"
#include "events.h"

HashMap* __events; // hash map of events

void create_event(const char* event_name) {
    if (__events == NULL) {
        __events = hash_map_create(100);
    }

    Event*event = (Event*)malloc(sizeof(Event));
    event->name = strdup(event_name);
    event->callbacks = create_linked_list();
    hash_map_put(__events, event_name, event);
}

int destroy_event(const char* event_name) {
    Event* event = hash_map_get(__events, event_name);
    if (event == NULL) return -1;

    free(event->name);
    destroy_linked_list(event->callbacks);
    hash_map_remove(__events, event_name);
    free(event);
    return 0;
}

int register_callback(const char *event_name, Callback callback) {
    Event* event = hash_map_get(__events, event_name);
    if (event == NULL) return -1;
    Callback* callback_ptr = (Callback *)malloc(sizeof(Callback));
    *callback_ptr = callback;
    linked_list_append(event->callbacks, callback_ptr);
    return 0;
}

int unregister_callback(const char *event_name, Callback callback) {
    Event* event = hash_map_get(__events, event_name);
    if (event == NULL) return -1;

    LinkedListNode *callback_node = event->callbacks->head;
    int index = 0;
    while (callback_node != NULL) {
        Callback* callback_ptr = (Callback*)callback_node->data;
        if (*callback_ptr == callback) {
            linked_list_remove(event->callbacks, index);
            free(callback_ptr);
            return 0;
        }
        index++;
        callback_node = callback_node->next;
    }
    return 0;
}

int trigger_event(const char *event_name, ...) {
    Event* event = hash_map_get(__events, event_name);
    if (event == NULL) return -1;
    LinkedListNode* callback_node = event->callbacks->head;
    while (callback_node != NULL) {
        Callback* callback_ptr = (Callback *)callback_node->data;
        va_list args;
        va_start(args, event_name);
        (*callback_ptr)(args);
        va_end(args);
        callback_node = callback_node->next;
    }
    return 0;
}
