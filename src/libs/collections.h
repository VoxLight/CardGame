/**
 * @file collections.h
 * @brief This header file contains the declarations of functions and structs for collections.
 */

#ifndef COLLECTIONS_H
#define COLLECTIONS_H

/**
 * @struct LinkedListNode
 * @brief A node in a linked list.
 */
typedef struct LinkedListNode {
    void* data; /**< The data stored in the node */
    struct LinkedListNode* next; /**< A pointer to the next node in the list */
} LinkedListNode;

/**
 * @struct LinkedList
 * @brief A linked list data structure.
 */
typedef struct {
    LinkedListNode* head; /**< A pointer to the first node in the list */
    LinkedListNode* tail; /**< A pointer to the last node in the list */
    int size; /**< The size of the list */
} LinkedList;

/**
 * @brief Creates a new linked list.
 * 
 * @return The newly created linked list.
 */
LinkedList create_linked_list();

/**
 * @brief Appends the specified data to the end of the list.
 * 
 * @param list The linked list to append to.
 * @param data The data to append.
 * @return 0 if the data was successfully appended, or -1 if an error occurred.
 */
int linked_list_append(LinkedList* list, void* data);

/**
 * @brief Removes the data at the specified index from the list.
 * 
 * @param list The linked list to remove from.
 * @param index The index of the data to remove.
 * @return The removed data, or NULL if an error occurred.
 */
void* linked_list_remove(LinkedList* list, int index);

/**
 * @brief Destroys the specified linked list and frees all the memory used by it.
 * 
 * @param list The linked list to destroy.
 */
void destroy_linked_list(LinkedList* list);

/**
 * @struct HashNode
 * @brief A node in a hash map.
 */
typedef struct HashNode {
    char* key; /**< The key of the node */
    void* value; /**< The value stored in the node */
    struct HashNode* next; /**< A pointer to the next node in the map */
} HashNode;

/**
 * @struct HashMap
 * @brief A hash map data structure.
 */
typedef struct {
    size_t size; /**< The size of the hash map */
    HashNode** table; /**< The table of hash nodes */
} HashMap;

/**
 * @brief Creates a new hash map with the specified size.
 * 
 * @param size The size of the hash map.
 * @return A pointer to the newly created hash map, or NULL if an error occurred.
 */
HashMap* hash_map_create(size_t size);

/**
 * @brief Puts the specified key-value pair in the hash map.
 * 
 * @param map The hash map to put the key-value pair in.
 * @param key The key to use.
 * @param value The value to put in the hash map.
 */
void hash_map_put(HashMap* map, const char* key, void* value);

/**
 * @brief Gets the value associated with the specified key from the hash map.
 * 
 * @param map The hash map to get the value from.
 * @param key The key to use.
 * @return The value associated with the key, or NULL if the key was not found.
 */
void* hash_map_get(HashMap* map, const char* key);

/**
 * @brief Removes the key-value pair associated with the specified key from the hash map.
 * 
 * @param map The hash map to remove the key-value pair from.
 * @param key The key to use.
 */
void hash_map_remove(HashMap* map, const char* key);

/**
 * @brief Frees all the memory used by the specified hash
 * 
 * @param map The hash map to free.
 */
void hash_map_free(HashMap* map);

#endif // COLLECTIONS_H
