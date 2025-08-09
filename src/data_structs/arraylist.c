#include <stdlib.h>
#include <string.h>
#include <math.h>
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
    if (initial_capacity == 0) {
        initial_capacity = 1;
    }
    nonstd_arraylist_header_t header = {
        .type_size = type_size,
        .capacity = initial_capacity,
        .length = 0,
        .growth_rate = NONSTD_ARRAYLIST_GROWTH_HALF_DOUBLE
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

size_t nonstd_arraylist_next_growth_length(void *self, size_t append_length)
{
    nonstd_arraylist_header_t *header = nonstd_arraylist_header(self);
    switch(header->growth_rate) {
        case NONSTD_ARRAYLIST_GROWTH_LINEAR: {
            return header->length + append_length;
        }
        case NONSTD_ARRAYLIST_GROWTH_DOUBLE: {
            size_t out_length = (header->length << 1);
            while (out_length < header->length + append_length) {
                out_length <<= 1;
            }
            return out_length;
        }
        case NONSTD_ARRAYLIST_GROWTH_HALF_DOUBLE: {
            size_t out_length = header->length + ceil((double)header->length / 2);
            while (out_length < header->length + append_length) {
                out_length += ceil((double)out_length / 2);
            }
            return out_length;
        }
        default:
            return 0;
    }
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

void nonstd_arraylist_shrink_to_fit(void **self)
{
    nonstd_arraylist_header_t *header = nonstd_arraylist_header(*self);
    header->capacity = header->length;
    header = realloc(header, sizeof(*header) + header->capacity * header->type_size);
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
    if (count >= header->length) {
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
    nonstd_arraylist_erase_subarray(self, idx, 1);
}

void nonstd_arraylist_erase_subarray(void *self, size_t idx, size_t length)
{
    nonstd_arraylist_header_t *header = nonstd_arraylist_header(self);
    if (length == 0 || idx + 1 > header->length) {
        return;
    }
    if (idx + length >= header->length) {
        nonstd_arraylist_pop_array(self, header->length - idx);
        return;
    }
    for (size_t i = idx + length; i < header->length; i++) {
        memcpy(
            &((char*)self)[(i - length) * header->type_size],
            &((char*)self)[i * header->type_size],
            header->type_size
        );
    }
    header->length -= length;
}

void nonstd_arraylist_erase_all(void *self)
{
    nonstd_arraylist_header(self)->length = 0;
}
