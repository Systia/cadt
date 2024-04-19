#include "array_list.h"

#include <stdlib.h>
#include <string.h>

struct array_list *array_list_new(size_t data_size) {
    return array_list_new2(ARRAY_LIST_DEFAULT_INITIAL_CAPACITY, data_size);
}

struct array_list *array_list_new2(size_t initial_capacity, size_t data_size) {
    if (initial_capacity <= 0 || data_size == 0)
        return NULL;

    struct array_list *al =
        (struct array_list *)malloc(sizeof(struct array_list));

    if ((al->array = (void **)calloc(sizeof(void *), initial_capacity)) ==
        NULL) {
        free(al);
        return NULL;
    }

    al->data_size = data_size;
    al->size = 0;
    al->resize_offset = initial_capacity;
    al->capacity = initial_capacity;

    return al;
}

bool array_list_resize(struct array_list *al, size_t new_capacity) {
    if (al == NULL || al->array == NULL)
        return false;

    if (new_capacity <= 0)
        return false;

    void **array = (void **)calloc(sizeof(void *), new_capacity);

    if (array == NULL)
        return false;

    if (new_capacity == al->size) {
        return true;
    } else if (new_capacity > al->size) {
        memcpy(array, al->array, sizeof(void *) * al->size);
    } else {
        memcpy(array, al->array, al->data_size * new_capacity);

        for (size_t i = new_capacity; i < al->size; i++) {
            free(al->array[i]);
        }
    }

    free(al->array);
    al->array = array;
    al->capacity = new_capacity;

    return true;
}

bool array_list_ensure_capacity(struct array_list *al,
                                size_t minimum_capacity) {
    if (al == NULL || al->array == NULL)
        return false;

    if (minimum_capacity <= 0)
        return false;

    if (al->capacity < minimum_capacity) {
        size_t new_capacity = al->capacity;

        while (new_capacity < minimum_capacity)
            new_capacity += al->resize_offset;

        if (!array_list_resize(al, new_capacity))
            return false;
    }

    return true;
}

bool array_list_insert(struct array_list *al, size_t idx, void *data) {
    if (al == NULL || al->array == NULL)
        return false;

    if (!array_list_ensure_capacity(al, idx + 1))
        return false;

    void *copy_data = (void *)malloc(al->data_size);

    if (copy_data == NULL)
        return false;

    memcpy(copy_data, data, al->data_size);

    if (al->array[idx] != NULL)
        free(al->array[idx]);

    al->array[idx] = copy_data;
    al->size = ((idx >= al->size) ? idx : al->size) + 1;

    return true;
}

bool array_list_add(struct array_list *al, void *data) {
    return array_list_insert(al, al->size, data);
}

bool array_list_remove(struct array_list *al, size_t idx) {
    if (al == NULL || al->array == NULL)
        return false;

    if (idx >= al->size)
        return NULL;

    if (al->array[idx] == NULL)
        return false;

    free(al->array[idx]);
    al->array[idx] = NULL;
    al->size--;

    return true;
}

void *array_list_get(struct array_list *al, size_t idx) {
    if (al == NULL || al->array == NULL)
        return false;

    if (idx >= al->size)
        return NULL;

    return al->array[idx];
}

void array_list_free(struct array_list *al) {
    for (size_t i = 0; i < al->size; i++) {
        free(al->array[i]);
    }

    free(al->array);
    free(al);
}
