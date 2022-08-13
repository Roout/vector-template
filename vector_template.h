#ifndef VECTOR_TEMPLATE_H__
#define VECTOR_TEMPLATE_H__

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#if defined(DEFINE_VECTOR)
# error "macro definition conflict"
#endif

#define DEFINE_VECTOR(TYPE)  \
    struct TYPE ## _vector { \
        TYPE *elements;      \
        size_t capacity;     \
        size_t size;         \
    };

#if defined(DEFINE_VECTOR_CREATE)
# error "macro definition conflict"
#endif

#define DEFINE_VECTOR_CREATE(TYPE)                                  \
    struct TYPE ## _vector * TYPE ## _vector_create(size_t cap) {   \
        assert(cap > 0);                                            \
        struct TYPE ## _vector *array = malloc(sizeof(struct TYPE ## _vector)); \
        if (!array) {                                               \
            return NULL;                                            \
        }                                                           \
        array->elements = malloc(cap * sizeof(TYPE));               \
        if (!array->elements) {                                     \
            free(array);                                            \
            return NULL;                                            \
        }                                                           \
        array->capacity = cap;                                      \
        array->size = 0;                                            \
        return array;                                               \
    }

#if defined(DEFINE_VECTOR_DESTROY)
# error "macro definition conflict"
#endif

#define DEFINE_VECTOR_DESTROY(TYPE)                              \
    void TYPE ## _vector_destroy(struct TYPE ## _vector **arr) { \
        assert(arr && *arr);                                     \
        assert((*arr)->elements);                                \
        free((*arr)->elements);                                  \
        free(*arr);                                              \
        *arr = NULL;                                             \
    }

#if defined(DEFINE_VECTOR_PUSH_BACK)
# error "macro definition conflict"
#endif

#define DEFINE_VECTOR_PUSH_BACK(TYPE) \
    void TYPE ## _vector_push_back(struct TYPE ## _vector *arr, TYPE value) {   \
        assert(arr);                                                            \
        assert(arr->elements);                                                  \
        if (arr->size + 1 > arr->capacity) {                                    \
            struct TYPE ## _vector copy;                                        \
            copy.size = arr->size;                                              \
            copy.capacity = arr->capacity * 2 + 1;                              \
            copy.elements = (TYPE*) malloc(sizeof(struct TYPE ## _vector) * copy.capacity);   \
            memcpy(copy.elements, arr->elements, arr->size * sizeof(struct TYPE ## _vector)); \
            free(arr->elements);                                                \
            *arr = copy;                                                        \
        }                                                                       \
        arr->elements[arr->size] = value;                                       \
        arr->size++;                                                            \
    }

#if defined(DEFINE_VECTOR_AT) || defined(DEFINE_VECTOR_CLEAR) || defined(DEFINE_VECTOR_BACK) || defined(DEFINE_VECTOR_FRONT)
# error "macro definition conflict"
#endif

#define DEFINE_VECTOR_AT(TYPE)                                              \
    TYPE TYPE ## _vector_at(struct TYPE ## _vector* arr, size_t index) {    \
        assert(arr);                                                        \
        assert(arr->elements);                                              \
        assert(arr->size > index);                                          \
        return arr->elements[index];                                        \
    }

#define DEFINE_VECTOR_CLEAR(TYPE)                               \
    void TYPE ## _vector_clear(struct TYPE ## _vector* arr) {   \
        assert(arr);                                            \
        assert(arr->elements);                                  \
        arr->size = 0;                                          \
    }

#define DEFINE_VECTOR_BACK(TYPE)                                \
    TYPE TYPE ## _vector_back(struct TYPE ## _vector* arr) {    \
        assert(arr);                                            \
        assert(arr->elements);                                  \
        assert(arr->size > 0);                                  \
        return arr->elements[arr->size - 1];                    \
    }

#define DEFINE_VECTOR_FRONT(TYPE)                               \
    TYPE TYPE ## _vector_front(struct TYPE ## _vector* arr) {   \
        assert(arr);                                            \
        assert(arr->elements);                                  \
        assert(arr->size > 0);                                  \
        return arr->elements[0];                                \
    }

#define DEFINE_VECTOR_INTERFACE(TYPE)   \
    DEFINE_VECTOR_CREATE(TYPE)          \
    DEFINE_VECTOR_DESTROY(TYPE)         \
    DEFINE_VECTOR_PUSH_BACK(TYPE)       \
    DEFINE_VECTOR_CLEAR(TYPE)           \
    DEFINE_VECTOR_BACK(TYPE)            \
    DEFINE_VECTOR_FRONT(TYPE)           \
    DEFINE_VECTOR_AT(TYPE)

#endif // VECTOR_TEMPLATE_H__
