#ifndef NONSTD_DATA_STRUCTS_ARRAY_H_INCLUDED
#define NONSTD_DATA_STRUCTS_ARRAY_H_INCLUDED

#include <stddef.h>

#define nonstd_array_init_M(type, size) \
    (nonstd_array_t){ \
        .ptr = (type[size]){}, \
        .size = size \
    }

#define nonstd_array_init_v_M(type, ...) \
    (nonstd_array_t){ \
        .ptr = (type[]){__VA_ARGS__}, \
        .size = sizeof((type[]){__VA_ARGS__}) / sizeof(type) \
    }

#define nonstd_array_init_sv_M(type, size, ...) \
    (nonstd_array_t){ \
        .ptr = (type[size]){__VA_ARGS__}, \
        .size = size \
    }

#define nonstd_array_at_M(array, type, idx) \
    ((type*)array.ptr)[idx]

typedef struct nonstd_array_t {
    void *ptr;
    size_t size;
} nonstd_array_t;

#endif
