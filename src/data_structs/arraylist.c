#include <stdlib.h>
#include "../../include/nonstd/data_structs/arraylist.h"

void *nonstd_arraylist_init(size_t type_size, size_t initial_capacity)
{
    nonstd_arraylist_header_t header = {
        .byte_size = type_size,
        .capacity = initial_capacity,
        .length = 0
    };

    nonstd_arraylist_header_t *arraylist = (nonstd_arraylist_header_t *)malloc(
        sizeof(header) + type_size * initial_capacity
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
