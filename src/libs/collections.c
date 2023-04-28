#include <stdlib.h>
#include <string.h>

#include "collections.h"

LinkedList* create_linked_list(){
    LinkedList* list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int linked_list_append(LinkedList* list, void* data) {
    LinkedListNode* new_node = (LinkedListNode*) malloc(sizeof(LinkedListNode));
    new_node->data = data;
    new_node->next = NULL;
    if (list->head == NULL)
        list->head = new_node;
    else
        list->tail->next = new_node;
    list->tail = new_node;
    list->size++;
    return 0;
}

void* linked_list_remove(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        return NULL;
    }
    LinkedListNode* prev = NULL;
    LinkedListNode* current = list->head;
    for (int i = 0; i < index; i++) {
        prev = current;
        current = current->next;
    }
    if (prev) {
        prev->next = current->next;
    } else {
        list->head = current->next;
    }
    if (current == list->tail) {
        list->tail = prev;
    }
    void* data = current->data;
    free(current);
    list->size--;
    return data;
}

void destroy_linked_list(LinkedList* list) {
    LinkedListNode* current = list->head;
    while (current) {
        LinkedListNode* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

LinkedList* linked_list_copy(LinkedList* src_list) {
    LinkedList* dest_list = create_linked_list();
    LinkedListNode* current_node = src_list->head;
    while (current_node != NULL) {
        linked_list_append(dest_list, current_node->data);
        current_node = current_node->next;
    }
    return dest_list;
}

static unsigned long hash(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

HashMap* hash_map_create(size_t size) {
    HashMap *map = malloc(sizeof(HashMap));
    map->size = size;
    map->table = calloc(size, sizeof(HashNode *));
    return map;
}

void hash_map_put(HashMap* map, const char* key, void* value) {
    unsigned long index = hash(key) % map->size;
    HashNode *node = map->table[index];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }
        node = node->next;
    }

    node = malloc(sizeof(HashNode));
    node->key = strdup(key);
    node->value = value;
    node->next = map->table[index];
    map->table[index] = node;
}

void* hash_map_get(HashMap* map, const char *key) {
    unsigned long index = hash(key) % map->size;
    HashNode *node = map->table[index];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }

    return NULL;
}

void hash_map_remove(HashMap* map, const char *key) {
    unsigned long index = hash(key) % map->size;
    HashNode *node = map->table[index];
    HashNode *prev = NULL;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                map->table[index] = node->next;
            }
            free(node->key);
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

void hash_map_free(HashMap* map) {
    for (size_t i = 0; i < map->size; i++) {
        HashNode *node = map->table[i];
        while (node) {
            HashNode *next = node->next;
            free(node->key);
            free(node);
            node = next;
        }
    }
    free(map->table);
    free(map);
}

HashMap* hash_map_copy(HashMap* src_map) {
    HashMap* dest_map = hash_map_create(src_map->size);
    for (size_t i = 0; i < src_map->size; i++) {
        HashNode* current_node = src_map->table[i];

        while (current_node != NULL) {
            hash_map_put(dest_map, current_node->key, current_node->value);
            current_node = current_node->next;
        }
    }
    return dest_map;
}