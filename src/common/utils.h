#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#define BLOCK_SIZE  64

typedef struct treehash_node_t{
    uint8_t *node;
    uint32_t height;
    struct treehash_node_t* next;
} treehash_node_t;

void ui32_to_bytes (uint8_t* out, uint32_t x);
void ui64_to_bytes (uint8_t* out, uint64_t x, uint8_t y);
void BlockPad (uint8_t* out, uint8_t* PK_seed);
void stack_push(treehash_node_t** head, treehash_node_t* node);
treehash_node_t* stack_pop(treehash_node_t** head);

#endif // UTILS_H