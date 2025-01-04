#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t *buffer;
    uint8_t buffer_size;
    uint8_t head;
    uint8_t tail;
    bool full;
} ring_buffer;


#define RING_BUFFER(name, size, storage)                                         \
    storage uint8_t name##_buffer[size] = { 0 };                                 \
    storage ring_buffer name##_ring_buffer = { .buffer = name##_buffer,          \
                                               .buffer_size = size };


void put(ring_buffer *rb, uint8_t data);
uint8_t get(ring_buffer *rb);
bool is_full(const ring_buffer *rb);
bool is_empty(const ring_buffer *rb);

#endif // RING_BUFFER_H

