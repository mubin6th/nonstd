#ifndef NONSTD_ARRAYLIST_INCLUDED
#define NONSTD_ARRAYLIST_INCLUDED

#include <stddef.h>

// TODO: Implement these.
#define nonstd_arraylist_append_M(self, value) \
    do { \
        nonstd_arraylist_header_t *nonstd_arraylist_header__ = \
            nonstd_arraylist_header(*self); \
        if (nonstd_arraylist_header__->length >= nonstd_arraylist_header__->capacity) { \
            size_t nonstd_arraylist_new_capacity__ = \
                nonstd_arraylist_next_growth_capacity(self); \
            nonstd_arraylist_header__ = \
                realloc( \
                    nonstd_arraylist_header__, \
                    sizeof(nonstd_arraylist_header_t) + \
                    nonstd_arraylist_new_capacity__ * \
                    nonstd_arraylist_header__->type_size \
                ); \
            self = &nonstd_arraylist_header__[1]; \
        } \
        self[nonstd_arraylist_header__->length++] = value; \
    } while (0)

#define nonstd_arraylist_insert_subarray_M 1
#define nonstd_arraylist_insert_at_M 1

typedef enum nonstd_arraylist_growth_t {
    NONSTD_ARRAYLIST_GROWTH_LINEAR,
    NONSTD_ARRAYLIST_GROWTH_DOUBLE,
    NONSTD_ARRAYLIST_GROWTH_HALF_DOUBLE,
} nonstd_arraylist_growth_t;

typedef struct nonstd_arraylist_header_t {
    size_t capacity;
    size_t length;
    size_t type_size;
    nonstd_arraylist_growth_t growth_rate;
} nonstd_arraylist_header_t;

void *nonstd_arraylist_init(size_t type_size, size_t initial_capacity);
void nonstd_arraylist_deinit(void *self);
nonstd_arraylist_header_t *nonstd_arraylist_header(void *self);
size_t nonstd_arraylist_length(void *self);
void nonstd_arraylist_set_growth_rate(void *self, nonstd_arraylist_growth_t growth_rate);
size_t nonstd_arraylist_next_growth_capacity(void *self);
void *nonstd_arraylist_front(void *self);
void *nonstd_arraylist_back(void *self);
void nonstd_arraylist_reserve(void **self, size_t capacity);
void nonstd_arraylist_shrink_to_fit(void **self);
void nonstd_arraylist_pop(void *self);
void nonstd_arraylist_pop_array(void *self, size_t count);
void nonstd_arraylist_erase_unorderd_at(void *self, size_t idx);
void nonstd_arraylist_erase_at(void *self, size_t idx);
void nonstd_arraylist_erase_subarray(void *self, size_t idx, size_t length);
void nonstd_arraylist_erase_all(void *self);

#endif
