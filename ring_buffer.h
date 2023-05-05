#ifndef RING_BUFFER_H__
#define RING_BUFFER_H__

#include <stdbool.h>
#include <time.h>
#include <stddef.h>

struct ring_buffer {
    time_t *buffer;
    size_t head;
    size_t tail;
    size_t size;
    size_t capacity;
};

bool ring_buffer_init(struct ring_buffer *buffer, size_t size);
void ring_buffer_push_back(struct ring_buffer *buffer, time_t val);
void ring_buffer_pop_front(struct ring_buffer *buffer);
time_t* ring_buffer_at(struct ring_buffer *buffer, size_t indx);
size_t ring_buffer_size(const struct ring_buffer *buffer);
bool ring_buffer_empty(const struct ring_buffer *buf);
bool ring_buffer_full(const struct ring_buffer *buf);
void ring_buffer_destroy(struct ring_buffer *buffer);
void ring_buffer_clear(struct ring_buffer *buffer);

#endif // RING_BUFFER_H__
