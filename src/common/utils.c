#include "common/utils.h"
#include "common/crypto.h"

#include <string.h>

void ui32_to_bytes (uint8_t* out, uint32_t x) {
    out[0] = (x >> 24) & 0xFF;
    out[1] = (x >> 16) & 0xFF;
    out[2] = (x >> 8) & 0xFF;
    out[3] = x & 0xFF;
}

void ui64_to_bytes (uint8_t* out, uint64_t x, uint8_t y) {
    int i;
    for (i = y - 1; i >= 0; i--) {
        out[i] = x & 0xFF;
        x >>= 8;
    }
}

void BlockPad (uint8_t* out, uint8_t* PK_seed) {
    memcpy(out, PK_seed, SPX_N);
    ui64_to_bytes(out + SPX_N, 0, BLOCK_SIZE - SPX_N);
}

void stack_push(treehash_node_t** head, treehash_node_t* node) {
    node->next = *head;
    *head = node;
}

treehash_node_t* stack_pop(treehash_node_t** head) {
    treehash_node_t* top = *head;
    *head = (*head)->next;
    top->next = NULL;

    return top;
}