#ifndef NONSTD_ARRAYLIST_INCLUDED
#define NONSTD_ARRAYLIST_INCLUDED

#include <stddef.h>

typedef struct nonstd_arraylist_header_t {
    size_t capacity;
    size_t length;
    size_t byte_size;
    size_t bytes;
    void *ptr;
} nonstd_arraylist_header_t;

void *nonstd_arraylist_init(size_t type_size, size_t initial_capacity);
nonstd_arraylist_header_t nonstd_arraylist_header(void *self);
void nonstd_arraylist_length(void *self);
void nonstd_arraylist_append(void *self, void *value);
void nonstd_arraylist_append_array(void *self, size_t values_length, void *values);
void nonstd_arraylist_pop(void *self);
void nonstd_arraylist_pop_array(void *self, size_t count);
void nonstd_arraylist_erase_unorderd_at(void *self, size_t idx);
void nonstd_arraylist_erase_at(void *self, size_t idx);
void nonstd_arraylist_erase_subarray(void *self, size_t idx, size_t length);
void nonstd_arraylist_erase_all(void *self);
void nonstd_arraylist_deinit(void *self);

#endif
