#include "common/utils.h"

#include <stdlib.h>

void ui32_to_bytes (uint8_t* out, uint32_t x) {
    out[0] = (x >> 24) & 0xFF;
    out[1] = (x >> 16) & 0xFF;
    out[2] = (x >> 8) & 0xFF;
    out[3] = x & 0xFF;
}

void ui64_to_bytes (uint8_t* out, uint64_t x, uint8_t y) {
    int i;
    for (i = y - 1; i >= 0; y--) {
        out[i] = x & 0xFF;
        x >>= 8;
    }
}