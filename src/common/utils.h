#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

void ui32_to_bytes (uint8_t* out, uint32_t x);
void ui64_to_bytes (uint8_t* out, uint64_t x, uint8_t y);

#endif // UTILS_H