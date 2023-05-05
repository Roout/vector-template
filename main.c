#include "ring_buffer.h"
#include <stdio.h>
#include <assert.h>

int main() {
    struct ring_buffer ring;
    ring_buffer_init(&ring, 5);
    assert(ring_buffer_empty(&ring));
    assert(ring_buffer_size(&ring) == 0);

    ring_buffer_push_back(&ring, (time_t)0);
    assert(ring_buffer_size(&ring) == 1);

    for (long long i = 1; i < 5; i++) {
        ring_buffer_push_back(&ring, (time_t)i);
    }
    assert(ring_buffer_size(&ring) == 5);
    assert(ring_buffer_full(&ring));
    
    for (long long i = 5; i < 10; i++) {
        ring_buffer_pop_front(&ring);
        assert(ring_buffer_size(&ring) == 4);
        ring_buffer_push_back(&ring, (time_t)i);
        assert(ring_buffer_size(&ring) == 5);
    }
    assert(ring_buffer_full(&ring));
    for (long long i = 0; i < 5; i++) {
        bool is_same = *ring_buffer_at(&ring, i) == (time_t)(i + 5);
        assert(is_same);
    }
    ring_buffer_pop_front(&ring);
    ring_buffer_pop_front(&ring);
    ring_buffer_pop_front(&ring);
    assert(!ring_buffer_empty(&ring));
    assert(!ring_buffer_full(&ring));
    assert(ring_buffer_size(&ring) == 2);
    for (size_t i = 0; i < ring_buffer_size(&ring); i++) {
        printf("%lld ", *ring_buffer_at(&ring, i));
    }
    ring_buffer_destroy(&ring);
    return 0;
}