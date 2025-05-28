#include "lib/XKCP/armv6-m/libXKCP.a.headers/SimpleFIPS202.h"
#include "common/defines.h"
#include "drivers/io.h"
#include "drivers/rng.h"
#include "common/crypto.h"
#include "common/utils.h"
#include "common/address.h"

#include <stdlib.h>


int main () {
    io_init();
    RNG_Module_Init();

    uint8_t public_key[2*SPX_N], secret_key[4*SPX_N];
    spx_keygen(public_key, secret_key);


    while (1) {
    }

    return 0;
} 
