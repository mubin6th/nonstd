#include <stdlib.h>
#include <string.h>
#include "../../include/nonstd/data_structs/arraylist.h"

/*
 * TODO: move swap to nonstd_math.
 * */
static void nonstd_math_swap(size_t type_size, void *a, void *b)
{
    char tmp[type_size];
    memcpy(tmp, a, type_size);
    memcpy(a, b, type_size);
    memcpy(b, tmp, type_size);
}

void *nonstd_arraylist_init(size_t type_size, size_t initial_capacity)
{
    nonstd_arraylist_header_t header = {
        .type_size = type_size,
        .capacity = initial_capacity,
        .length = 0
    };

    nonstd_arraylist_header_t *arraylist = (nonstd_arraylist_header_t *)malloc(
        sizeof(header) + initial_capacity * type_size
    );
    arraylist[0] = header;

    return &arraylist[1];
}

void nonstd_arraylist_deinit(void *self)
{
    nonstd_arraylist_header_t *header = nonstd_arraylist_header(self);
    free((char*)header);
}

nonstd_arraylist_header_t *nonstd_arraylist_header(void *self)
{
    return &((nonstd_arraylist_header_t*)self)[-1];
}

size_t nonstd_arraylist_length(void *self)
{
    return nonstd_arraylist_header(self)->length;
}

void *nonstd_arraylist_front(void *self)
{
    if (nonstd_arraylist_length(self) == 0) {
        return NULL;
    }
    return &((char*)self)[0];
}

void *nonstd_arraylist_back(void *self)
{
    nonstd_arraylist_header_t *header = nonstd_arraylist_header(self);
    if (header->length == 0) {
        return NULL;
    }
    return &((char*)self)[(header->length - 1) * header->type_size];
}

void nonstd_arraylist_reserve(void **self, size_t capacity)
{
    nonstd_arraylist_header_t *header = nonstd_arraylist_header(*self);
    if (header->capacity >= capacity) {
        return;
    }
    header = realloc(header, sizeof(*header) + capacity * header->type_size);
    header->capacity = capacity;
    *self = &header[1];
}

void nonstd_arraylist_pop(void *self)
{
    if (nonstd_arraylist_length(self) == 0) {
        return;
    }
    nonstd_arraylist_header(self)->length--;
}

void nonstd_arraylist_pop_array(void *self, size_t count)
{
    nonstd_arraylist_header_t *header = nonstd_arraylist_header(self);
    if (header->length <= count) {
        header->length = 0;
        return;
    }
    header->length -= count;
}

void nonstd_arraylist_erase_unorderd_at(void *self, size_t idx)
{
    nonstd_arraylist_header_t *header = nonstd_arraylist_header(self);
    if (idx + 1 > header->length) {
        return;
    }
    nonstd_math_swap(
        header->type_size,
        &((char*)self)[idx * header->type_size],
        nonstd_arraylist_back(self)
    );
    header->length--;
}

void nonstd_arraylist_erase_at(void *self, size_t idx)
{
    nonstd_arraylist_header_t *header = nonstd_arraylist_header(self);
    if (idx + 1 > header->length) {
        return;
    }
    if (idx + 1 == header->length) {
        nonstd_arraylist_pop(self);
        return;
    }
    for (size_t i = idx + 1; i < header->length; i++) {
        memcpy(
            &((char*)self)[(i - 1) * header->type_size],
            &((char*)self)[i * header->type_size],
            header->type_size
        );
    }
    header->length--;
}

void nonstd_arraylist_erase_subarray(void *self, size_t idx, size_t length);

void nonstd_arraylist_erase_all(void *self)
{
    nonstd_arraylist_header(self)->length = 0;
}
