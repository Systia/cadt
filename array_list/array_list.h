#pragma once

#include <stdbool.h>
#include <stddef.h>

#define ARRAY_LIST_DEFAULT_INITIAL_CAPACITY 15

struct array_list {
    void **array;
    size_t data_size;
    size_t resize_offset;
    size_t size;
    size_t capacity;
};

struct array_list *array_list_new(size_t data_size);
struct array_list *array_list_new2(size_t initial_capacity, size_t data_size);
bool array_list_resize(struct array_list *al, size_t new_capacity);
bool array_list_ensure_capacity(struct array_list *al, size_t minimum_capacity);
bool array_list_insert(struct array_list *al, size_t idx, void *data);
bool array_list_add(struct array_list *al, void *data);
bool array_list_remove(struct array_list *al, size_t idx);
void *array_list_get(struct array_list *a, size_t idx);
void array_list_free(struct array_list *al);
