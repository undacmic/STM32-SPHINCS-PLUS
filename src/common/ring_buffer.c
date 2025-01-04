#include "common/ring_buffer.h"

void put(ring_buffer *rb, uint8_t data) {
    rb->buffer[rb->head] = data;

    rb->head++;

    if (rb->head == rb->buffer_size) {
        rb->head = 0;
    }

    if (rb->head == rb->tail) {
        rb->full = true;
    }

}

uint8_t get(ring_buffer *rb) {
    uint8_t data = rb->buffer[rb->tail];

    rb->tail++;

    if (rb->tail == rb->buffer_size) {
        rb->tail = 0;
    }

    rb->full = false;

    return data;
}

bool is_full(const ring_buffer *rb) {
    return rb->full;
}

bool is_empty(const ring_buffer *rb) {
    return !rb->full && rb->head == rb->tail;
}