#include "ring_buffer.h"
#include <stdlib.h>
#include <assert.h>

bool ring_buffer_init(struct ring_buffer *buf, size_t capacity) {
    *buf = (struct ring_buffer) {
        .buffer = NULL,
        .head = 0,
        .tail = 0,
        .size = 0,
        .capacity = capacity
    };
    buf->buffer = (time_t*)malloc(capacity * sizeof(time_t));
    return buf->buffer != NULL;
}

void ring_buffer_push_back(struct ring_buffer *buf, time_t val) {
    assert(buf);
    assert(buf->buffer);
    assert(!ring_buffer_full(buf));
    buf->buffer[buf->tail] = val;
    buf->tail = (buf->tail + 1) % buf->capacity;
    buf->size++;
}

void ring_buffer_pop_front(struct ring_buffer *buf) {
    assert(buf);
    assert(buf->buffer);
    assert(!ring_buffer_empty(buf));
    buf->head = (buf->head + 1) % buf->capacity;
    buf->size--;
}

time_t* ring_buffer_at(struct ring_buffer *buf, size_t index) {
    assert(buf);
    assert(buf->buffer);
    assert(index < buf->size);
    const size_t transformed = (buf->head + index) % buf->capacity;
    return &buf->buffer[transformed];
}

size_t ring_buffer_size(const struct ring_buffer *buf) {
    assert(buf);
    return buf->size;
}

bool ring_buffer_empty(const struct ring_buffer *buf) {
    assert(buf);
    return buf->size == 0;
}
bool ring_buffer_full(const struct ring_buffer *buf) {
    assert(buf);
    return buf->size == buf->capacity;
}
void ring_buffer_destroy(struct ring_buffer *buf) {
    free(buf->buffer);
    buf->buffer = NULL;
    buf->head = buf->tail = buf->size = buf->capacity = 0;
}
void ring_buffer_clear(struct ring_buffer *buf){
    buf->head = buf->tail = buf->size = 0;
}
