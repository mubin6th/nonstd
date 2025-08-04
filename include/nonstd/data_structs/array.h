#ifndef NONSTD_DATA_STRUCTS_ARRAY_H_INCLUDED
#define NONSTD_DATA_STRUCTS_ARRAY_H_INCLUDED

#include <stddef.h>

#define nonstd_array_init_with_values_M(type, ...) \
    (nonstd_array_t){ \
        .ptr = (type[]){__VA_ARGS__}, \
        .size = sizeof((type[]){__VA_ARGS__}) / sizeof(type) \
    }

#define nonstd_array_init_M(type, size) \
    (nonstd_array_t){ \
        .ptr = (type[size]){}, \
        .size = size \
    }

typedef struct nonstd_array_t {
    void *ptr;
    size_t size;
} nonstd_array_t;

#endif
