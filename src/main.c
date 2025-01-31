#include "external/XKCP/SimpleFIPS202.h"
#include "common/defines.h"
#include "drivers/io.h"
#include "drivers/rng.h"

#include <stdlib.h>


int main () {
    io_init();
    RNG_Module_Init();

    int i;
    uint8_t* seed = 0;

    for ( i = 0; i < 10; i++) {
        seed = GenerateBytes(32);
        free(seed);
    }

    unsigned char hash[32] = { 0 };
    unsigned char input[5] = "ceva";
    SHA3_256(hash, input, 4);

    while (1) {
    }

    return 0;
} 
