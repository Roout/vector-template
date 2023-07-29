#ifndef RING_BUFFER_H__
#define RING_BUFFER_H__

#include <stdbool.h>
#include <time.h>
#include <stddef.h>

typedef struct ring_buffer {
    time_t *buffer;
    size_t head;
    size_t size;
    size_t capacity;
} t_ring_buffer;

bool ring_buffer_init(t_ring_buffer *buffer, size_t size);
void ring_buffer_push_back(t_ring_buffer *buffer, time_t val);
void ring_buffer_pop_front(t_ring_buffer *buffer);
time_t* ring_buffer_at(t_ring_buffer *buffer, size_t indx);
size_t ring_buffer_size(const t_ring_buffer *buffer);
bool ring_buffer_empty(const t_ring_buffer *buf);
bool ring_buffer_full(const t_ring_buffer *buf);
void ring_buffer_destroy(t_ring_buffer *buffer);
void ring_buffer_clear(t_ring_buffer *buffer);

#endif // RING_BUFFER_H__
