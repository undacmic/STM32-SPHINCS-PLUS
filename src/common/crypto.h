#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdint.h>

#define SPX_N           (16)                // Security Parameter
#define SPX_W           (16)                // Winternitz Parameter
#define SPX_H           (66)                // Hypertree Height
#define SPX_D           (22)                // Hypertree Layers
#define SPX_H_PRIME     (SPX_H / SPX_D)     // Tree height
#define hLen            (32)                // Hash Length

#define WOTS_LEN1       (32)
#define WOTS_LEN2       (3)
#define WOTS_LEN        (WOTS_LEN1 + WOTS_LEN2)

void mgf1 (uint8_t* out, uint8_t* PK_seed, uint8_t* ADRS, uint32_t l);

// Key Generation
void T_l (uint8_t* out, uint8_t* PK_seed, uint8_t* ADRS, uint8_t* M, uint8_t l);
void chain (uint8_t* out, uint8_t* X, uint32_t i, uint32_t s, uint8_t* PK_seed, uint8_t* ADRS);
void wots_PKgen (uint8_t* out, uint8_t* SK_seed, uint8_t* PK_seed, uint8_t* ADRS);
void treehash (uint8_t* out, uint8_t* SK_seed, uint8_t s, uint8_t z, uint8_t* PK_seed, uint8_t* ADRS);
void xmss_PKgen(uint8_t* out, uint8_t* SK_seed, uint8_t* PK_seed, uint8_t* ADRS);
void ht_PKgen(uint8_t* out, uint8_t* SK_seed, uint8_t* PK_seed);
void spx_keygen(uint8_t* public_key, uint8_t* secret_key);

// Signature
void wots_sign(uint8_t* out, uint8_t* M, uint8_t* SK_seed, uint8_t PK_seed, uint8_t* ADRS);

#endif // CRYPTO_H