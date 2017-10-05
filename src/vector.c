#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

struct Vector *vector_create() {
    struct Vector *new_vector = malloc(sizeof(struct Vector));

    new_vector->capacity = VECTOR_INIT_CAPACITY;
    new_vector->size = 0;
    new_vector->items = malloc(sizeof(int) * new_vector->capacity);

    return new_vector;
}

int vector_resize(struct Vector *vector, int capacity) {
    int *items = realloc(vector->items, sizeof(int) * capacity);

    if (items == NULL)
        return 0;

    vector->items = items;
    vector->capacity = capacity;

    return 1;
}

int vector_add(struct Vector *vector, int item) {
    if (vector->capacity == vector->size) {
        if (vector_resize(vector, vector->capacity * 2) != 1)
            return 0;
    }

//    vector->items[vector->size] = item;
    vector->size += 1;

    return 1;
}

int vector_set(struct Vector *vector, int index, int item) {
    if (index < 0 || index >= vector->size)
        return 0;

    vector->items[index] = item; 

    return 1;
}

int vector_get(struct Vector *vector, int index) {
    if (index < 0 || index >= vector->size)
        return -1;

    return vector->items[index];
}

int vector_remove(struct Vector *vector, int index) {
    if (index < 0 || index >= vector->size)
        return 0;

    for (int shift_index = index; shift_index < vector->size - 1; shift_index++)
        vector->items[shift_index] = vector->items[shift_index + 1];

    vector->items[vector->size - 1] = -1;
    vector->size--;

    if (vector->size > 0 && vector->size == vector->capacity / 4)
        if (vector_resize(vector, vector->capacity / 2) != 1)
             return 0;

    return 1;
}

void vector_free(struct Vector *vector) {
    free(vector->items);
    free(vector);
}
