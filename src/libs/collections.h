#ifndef COLLECTIONS_H
#define COLLECTIONS_H

// Linked List
typedef struct LinkedListNode {
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

typedef struct {
    LinkedListNode* head;
    LinkedListNode* tail;
    int size;
} LinkedList;

LinkedList create_linked_list();
int linked_list_append(LinkedList* list, void* data);
void* linked_list_remove(LinkedList* list, int index);
void destroy_linked_list(LinkedList* list);

// Hash Map
typedef struct HashNode {
    char* key;
    void* value;
    struct HashNode* next;
} HashNode;

typedef struct HashMap {
    size_t size;
    HashNode** table;
} HashMap;

HashMap* hash_map_create(size_t size);
void hash_map_put(HashMap* map, const char* key, void* value);
void* hash_map_get(HashMap* map, const char* key);
void hash_map_remove(HashMap* map, const char* key);
void hash_map_free(HashMap* map);

#endif // COLLECTIONS_H
