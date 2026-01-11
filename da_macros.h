#pragma once

#include <stddef.h>
#include <string.h>

/*
    1. create a struct for array type - da_type(name, type), ex: da_type(string, char)
    2. append to an array - da_append(array_name, value), ex: da_append(message, 'J');
    3. initialise an array from an array: 
        da_f?set(cpy|ref)(_ex)?(dst_array, (src_arr)|(src_ptr, src_capacity, src_count))
        f - free previous content
        cpy - set to a copy of source
        ref - set to a reference of source (only data)
        _ex - manual array instead of struct
        args:
            source array struct | ptr, capacity, count

    4. free and reset struct - da_free(name)
    5. reset struct without free - da_reset(name)
*/

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
    xs.items[xs.count++] = x; \
    } while (0)
 
#define da_setref_ex(xs, ptr, size_, count_) \
    do { \
        xs.items = ptr; \
        xs.capacity = size_; \
        xs.count = count_; \
    } while (0)

#define da_setcpy_ex(xs, ptr, size_, count_) \
    do { \
        xs.items = malloc(size_); \
        xs.capacity = size_; \
        xs.count = count_; \
        memcpy(xs.items, ptr, size_); \
    } while (0)

#define da_setref(xs, ys) \
    do { \
        xs.items = ys.items; \
        xs.capacity = ys.capacity; \
        xs.count = ys.count; \
    } while (0)

#define da_setcpy(xs, ys) \
    do { \
        xs.items = realloc(xs.items, ys.capacity); \
        xs.capacity = ys.capacity; \
        xs.count = ys.count; \
        memcpy(xs.items, ys.items, ys.capacity); \
    } while (0)

#define da_fsetref_ex(xs, ptr, size_, count_) \
    do { \
        if (xs.items) free(xs.items); \
        xs.items = ptr; \
        xs.capacity = size_; \
        xs.count = count_; \
    } while (0)

#define da_fsetcpy_ex(xs, ptr, size_, count_) \
    do { \
        if (xs.items) free(xs.items); \
        xs.items = malloc(size_); \
        xs.capacity = size_; \
        xs.count = count_; \
        memcpy(xs.items, ptr, size_); \
    } while (0)

#define da_fsetref(xs, ys) \
    do { \
        if (xs.items) free(xs.items); \
        xs.items = ys.items; \
        xs.capacity = ys.capacity; \
        xs.count = ys.count; \
    } while (0)

#define da_fsetcpy(xs, ys) \
    do { \
        if (xs.items) free(xs.items); \
        xs.items = realloc(xs.items, ys.capacity); \
        xs.capacity = ys.capacity; \
        xs.count = ys.count; \
        memcpy(xs.items, ys.items, ys.capacity); \
    } while (0)

#define da_free(xs) \
    do { \
        if (xs.items) free(xs.items); \
        xs.capacity = 0; \
        xs.count = 0; \
    } while (0)

#define da_reset(xs) \
    do { \
        xs.items = NULL; \
        xs.capacity = 0; \
        xs.count = 0; \
    } while (0)
    
#define da_init { 0 }
#define da_autoinit(dec) dec = da_init