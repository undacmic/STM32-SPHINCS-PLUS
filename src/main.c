#include "lib/XKCP/armv6-m/libXKCP.a.headers/SimpleFIPS202.h"
#include "common/defines.h"
#include "drivers/io.h"
#include "drivers/rng.h"

#include <stdlib.h>


int main () {
    io_init();
    RNG_Module_Init();

    while (1) {
    }

    return 0;
} 
