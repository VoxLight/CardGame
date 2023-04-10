#include <assert.h>
#include <stdio.h>
#include "collections.h"

void test_linked_list_create() {
    LinkedList list = create_linked_list();
    assert(list.size == 0);
    assert(list.head == NULL);
    assert(list.tail == NULL);
}

void test_linked_list_append() {
    LinkedList list = create_linked_list();

    int data1 = 42;
    int data2 = 7;
    int data3 = 13;

    linked_list_append(&list, &data1);
    assert(list.size == 1);
    assert(list.head != NULL);
    assert(list.head == list.tail);
    assert(list.head->data == &data1);

    linked_list_append(&list, &data2);
    assert(list.size == 2);
    assert(list.tail != NULL);
    assert(list.head != list.tail);
    assert(list.tail->data == &data2);

    linked_list_append(&list, &data3);
    assert(list.size == 3);
    assert(list.tail != NULL);
    assert(list.tail->data == &data3);

    destroy_linked_list(&list);
}

void test_linked_list_remove() {
    LinkedList list = create_linked_list();

    int data1 = 42;
    int data2 = 7;
    int data3 = 13;

    linked_list_append(&list, &data1);
    linked_list_append(&list, &data2);
    linked_list_append(&list, &data3);

    int* removed_data = (int*)linked_list_remove(&list, 1);
    assert(removed_data == &data2);
    assert(list.size == 2);

    destroy_linked_list(&list);
}

void test_linked_list_destroy() {
    LinkedList list = create_linked_list();

    int data1 = 42;
    int data2 = 7;

    linked_list_append(&list, &data1);
    linked_list_append(&list, &data2);

    destroy_linked_list(&list);
    assert(list.size == 0);
    assert(list.head == NULL);
    assert(list.tail == NULL);
}

void test_hash_map_create() {
    HashMap *map = hash_map_create(10);
    assert(map != NULL);
    assert(map->size == 10);
    assert(map->table != NULL);
    hash_map_free(map);
}

void test_hash_map_put_get() {
    HashMap *map = hash_map_create(10);
    int data1 = 42;
    int data2 = 7;

    hash_map_put(map, "key1", &data1);
    hash_map_put(map, "key2", &data2);

    int *retrieved_data1 = (int *)hash_map_get(map, "key1");
    int *retrieved_data2 = (int *)hash_map_get(map, "key2");

    assert(retrieved_data1 != NULL);
    assert(*retrieved_data1 == data1);
    assert(retrieved_data2 != NULL);
    assert(*retrieved_data2 == data2);

    hash_map_free(map);
}

void test_hash_map_remove() {
    HashMap *map = hash_map_create(10);
    int data1 = 42;
    int data2 = 7;

    hash_map_put(map, "key1", &data1);
    hash_map_put(map, "key2", &data2);

    hash_map_remove(map, "key1");
    void *retrieved_data1 = hash_map_get(map, "key1");
    int *retrieved_data2 = (int *)hash_map_get(map, "key2");

    assert(retrieved_data1 == NULL);
    assert(retrieved_data2 != NULL);
    assert(*retrieved_data2 == data2);

    hash_map_free(map);
}

int main() {
    test_linked_list_create();
    test_linked_list_append();
    test_linked_list_remove();
    test_linked_list_destroy();

    test_hash_map_create();
    test_hash_map_put_get();
    test_hash_map_remove();

    printf("All tests passed.\n");

    return 0;
}
