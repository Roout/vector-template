#ifndef VECTOR_TEMPLATE_H__
#define VECTOR_TEMPLATE_H__

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define VECTOR_NPOS ((size_t)-1)

#if defined(DEFINE_VECTOR)
# error "macro definition conflict"
#endif

#define DEFINE_VECTOR(NAME, TYPE)   \
    struct NAME {                   \
        TYPE *elements;             \
        size_t capacity;            \
        size_t size;                \
    };

#if defined(DEFINE_VECTOR_CREATE)
# error "macro definition conflict"
#endif

#define DEFINE_VECTOR_CREATE(NAME, TYPE)                    \
    inline bool NAME ## _init(struct NAME *arr, size_t cap) {      \
        assert(arr);                                        \
        assert(cap > 0);                                    \
        arr->elements = (TYPE*)malloc(cap * sizeof(TYPE));  \
        if (!arr->elements) {                               \
            return false;                                   \
        }                                                   \
        arr->capacity = cap;                                \
        arr->size = 0;                                      \
        return true;                                        \
    }

#if defined(DEFINE_VECTOR_DESTROY)
# error "macro definition conflict"
#endif

#define DEFINE_VECTOR_DESTROY(NAME, TYPE)                   \
    inline void NAME ## _destroy(struct NAME *arr) {        \
        assert(arr);                                        \
        free(arr->elements);                                \
        arr->elements = NULL;                               \
        arr->capacity = 0;                                  \
        arr->size = 0;                                      \
    }

#if defined(DEFINE_VECTOR_PUSH_BACK)
# error "macro definition conflict"
#endif

#define DEFINE_VECTOR_PUSH_BACK(NAME, TYPE)                                     \
    inline bool NAME ## _push_back(struct NAME *arr, TYPE value) {              \
        assert(arr);                                                            \
        assert(arr->elements);                                                  \
        if (arr->size + 1 > arr->capacity) {                                    \
            struct NAME copy;                                                   \
            copy.size = arr->size;                                              \
            copy.capacity = arr->capacity * 2 + 1;                              \
            copy.elements = (TYPE*) malloc(sizeof(struct TYPE) * copy.capacity);   \
            if (copy.elements == NULL) return false;                               \
            memcpy(copy.elements, arr->elements, arr->size * sizeof(struct NAME)); \
            free(arr->elements);                                                \
            *arr = copy;                                                        \
        }                                                                       \
        arr->elements[arr->size] = value;                                       \
        arr->size++;                                                            \
        return true;                                                            \
    }

#if defined(DEFINE_VECTOR_POP_BACK)
# error "macro definition conflict"
#endif

#define DEFINE_VECTOR_POP_BACK(NAME, TYPE)                                      \
    inline void NAME ## _pop_back(struct NAME *arr) {                           \
        assert(arr);                                                            \
        assert(arr->elements);                                                  \
        assert(arr->size > 0);                                                  \
        arr->size--;                                                            \
    }

#if defined(DEFINE_VECTOR_AT) || defined(DEFINE_VECTOR_CLEAR) || defined(DEFINE_VECTOR_BACK) || defined(DEFINE_VECTOR_FRONT)
# error "macro definition conflict"
#endif

#define DEFINE_VECTOR_AT(NAME, TYPE)                                        \
    inline TYPE* NAME ## _at(struct NAME* arr, size_t index) {              \
        assert(arr);                                                        \
        assert(arr->elements);                                              \
        assert(arr->size > index);                                          \
        return &arr->elements[index];                                       \
    }

#define DEFINE_VECTOR_CLEAR(NAME, TYPE)                         \
    inline void NAME ## _clear(struct NAME* arr) {              \
        assert(arr);                                            \
        assert(arr->elements);                                  \
        arr->size = 0;                                          \
    }

#define DEFINE_VECTOR_BACK(NAME, TYPE)                          \
    inline TYPE* NAME ## _back(struct NAME* arr) {              \
        assert(arr);                                            \
        assert(arr->elements);                                  \
        assert(arr->size > 0);                                  \
        return &arr->elements[arr->size - 1];                   \
    }

#define DEFINE_VECTOR_FRONT(NAME, TYPE)                         \
    inline TYPE* NAME ## _front(struct NAME* arr) {             \
        assert(arr);                                            \
        assert(arr->elements);                                  \
        assert(arr->size > 0);                                  \
        return &arr->elements[0];                               \
    }

#define DEFINE_VECTOR_INTERFACE(NAME, TYPE)   \
    DEFINE_VECTOR_CREATE(NAME, TYPE)          \
    DEFINE_VECTOR_DESTROY(NAME, TYPE)         \
    DEFINE_VECTOR_PUSH_BACK(NAME, TYPE)       \
    DEFINE_VECTOR_POP_BACK(NAME, TYPE)        \
    DEFINE_VECTOR_CLEAR(NAME, TYPE)           \
    DEFINE_VECTOR_BACK(NAME, TYPE)            \
    DEFINE_VECTOR_FRONT(NAME, TYPE)           \
    DEFINE_VECTOR_AT(NAME, TYPE)

#endif // VECTOR_TEMPLATE_H__
