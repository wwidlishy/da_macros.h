#pragma once

#include <stddef.h>
#include <string.h>

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

#define da_setref_ex(xs, ptr, size_, count_) \
    do { \
        if (xs.items) free(xs.items); \
        xs.items = ptr; \
        xs.capacity = size_; \
        xs.count = count_; \
    } while (0)

#define da_setcpy_ex(xs, ptr, size_, count_) \
    do { \
        if (xs.items) free(xs.items); \
        xs.items = realloc(xs.items, size_); \
        xs.capacity = size_; \
        xs.count = count_; \
        memcpy(xs.items, ptr, size_); \
    } while (0)

#define da_setref(xs, ys) \
    do { \
        if (xs.items) free(xs.items); \
        xs.items = ys.items; \
        xs.capacity = ys.capacity; \
        xs.count = ys.count; \
    } while (0)

#define da_setcpy(xs, ys) \
    do { \
        if (xs.items) free(xs.items); \
        xs.items = realloc(xs.items, ys.capacity); \
        xs.capacity = ys.capacity; \
        xs.count = ys.count; \
        memcpy(xs.items, ys.items, ys.capacity); \
    } while (0)

#define da_init { 0 }
#define da_autoinit(dec) dec = da_init