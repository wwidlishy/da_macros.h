#pragma once

#include <stddef.h>

#define da_type(name, type) \
    typedef struct name { \
        type* items; \
        size_t count; \
        size_t capacity; \
    } name;

#define da_append(xs, x) \
    do {if (xs.count >= xs.capacity) { \
        if (xs.capacity == 0) xs.capacity = 256; \
        else xs.capacity *= 2; \
        xs.items = realloc(xs.items, xs.capacity*sizeof(*xs.items)); \
    } \
    xs.items[xs.count++] = x;} while (0)

#define da_init { 0 }