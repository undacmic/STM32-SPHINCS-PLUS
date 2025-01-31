#include "common/crypto.h"
#include "common/utils.h"
#include "common/address.h"
#include "drivers/rng.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "external/XKCP/SimpleFIPS202.h"

#define SPX_N           (16)                // Security Parameter
#define SPX_W           (16)                // Winternitz Parameter
#define SPX_H           (66)                // Hypertree Height
#define SPX_D           (22)                // Hypertree Layers
#define SPX_H_PRIME     (SPX_H / SPX_D)     // Tree height
#define hLen            (32)                // Hash Length

#define WOTS_LEN1       (32)
#define WOTS_LEN2       (3)
#define WOTS_LEN        (WOTS_LEN1 + WOTS_LEN2)

#define PRF(out, PK_seed, ADRS)     T_l(out, PK_seed, ADRS, 0, 0)
#define F(out, PK_seed, ADRS, M)    T_l(out, PK_seed, ADRS, M, 1)
#define H(out, PK_seed, ADRS, M)    T_l(out, PK_seed, ADRS, M, 2)

/**
 * MGF1 as defined in RFC 2437
 */
void mgf1 (uint8_t* out, uint8_t* PK_seed, uint8_t* ADRS, uint32_t l) {
    uint8_t Z[SPX_N + ADRS_SIZE + 4] = { 0 };
    uint8_t temp[hLen];
    uint32_t counter = 0;
    uint32_t no_iterations = (l + hLen - 1) / hLen;

    memcpy(Z, PK_seed, SPX_N);
    memcpy(Z + SPX_N, ADRS, ADRS_SIZE);
    
    while (counter < no_iterations) {
        SHA3_256(temp, Z, SPX_N + ADRS_SIZE + 4);

        uint32_t copy_size = (l - counter * hLen >= hLen) ? hLen : (l - counter * hLen);
        memcpy(out + counter * hLen, temp, copy_size);
        
        counter++;

        Z[SPX_N + ADRS_SIZE] = (counter >> 24) & 0xFF;
        Z[SPX_N + ADRS_SIZE + 1] = (counter >> 16) & 0xFF;
        Z[SPX_N + ADRS_SIZE + 2] = (counter >> 8) & 0xFF;
        Z[SPX_N + ADRS_SIZE + 3] = counter & 0xFF;
    }
}

void T_l (uint8_t* out, uint8_t* PK_seed, uint8_t* ADRS, uint8_t* M, uint8_t l) {
    uint8_t temp[(l + 1) * SPX_N + ADRS_SIZE];

    memcpy(temp, PK_seed, SPX_N);
    memcpy(temp + SPX_N, ADRS, ADRS_SIZE);

    if (l > 0) {
        uint8_t mask[SPX_N * l];
        mgf1(mask, PK_seed, ADRS, SPX_N * l);

        int i;
        for (i = 0; i < SPX_N * l; i++) {
            M[i] ^= mask[i];
        }

        memcpy(temp + SPX_N + ADRS_SIZE, M, SPX_N * l);
    }

    uint8_t hash[hLen];
    SHA3_256(hash, temp, (l + 1) * SPX_N + ADRS_SIZE);
    memcpy(out, hash, SPX_N);
}

void chain (uint8_t* out, uint8_t* X, uint32_t i, uint32_t s, uint8_t* PK_seed, uint8_t* ADRS) {
    memcpy(out, X, SPX_N);

    uint32_t j;
    for(j = i; j < (i + s) && j < SPX_W; j++) {
        set_hash_addr(ADRS, j);
        F(out, PK_seed, ADRS, out);
    }
}

// uint8_t* ht_PKgen (uint8_t* SK_seed, uint8_t* PK_seed) {
//     return 0;
// }

// uint8_t* spx_keygen (void) {
//     uint8_t* key_pair = malloc(4 * N * sizeof(uint8_t));

//     uint8_t* SK_seed = GenerateBytes(N);
//     uint8_t* SK_prf = GenerateBytes(N);
//     uint8_t* PK_seed = GenerateBytes(N);

// }