#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdint.h>

void mgf1 (uint8_t* out, uint8_t* PK_seed, uint8_t* ADRS, uint32_t l);
void T_l (uint8_t* out, uint8_t* PK_seed, uint8_t* ADRS, uint8_t* M, uint8_t l);
void chain (uint8_t* out, uint8_t* X, uint32_t i, uint32_t s, uint8_t* PK_seed, uint8_t* ADRS);

// uint8_t* wots_PKgen (uint8_t* SK_seed, uint8_t* PK_seed, uint8_t* ADRS);
// uint8_t* xmss_PKgen (uint8_t* SK_seed, uint8_t* PK_seed, uint8_t* ADRS);
// uint8_t* ht_PKgen (uint8_t* SK_seed, uint8_t* PK_seed);
// uint8_t* spx_keygen (void);

#endif // CRYPTO_H