#include "common/crypto.h"
#include "common/utils.h"
#include "common/address.h"

#include "drivers/rng.h"

#ifdef TEST_SETUP
#include "lib/XKCP/generic64/libXKCP.a.headers/SimpleFIPS202.h"
#else
#include "lib/XKCP/armv6-m/libXKCP.a.headers/SimpleFIPS202.h"
#endif

#include <stdlib.h>
#include <string.h>

#define F(out, PK_seed, ADRS, M)    T_l(out, PK_seed, ADRS, M, 1)
#define H(out, PK_seed, ADRS, M)    T_l(out, PK_seed, ADRS, M, 2)

/**
 * MGF1 as defined in RFC 2437
 */
void mgf1 (uint8_t* out, uint8_t* PK_seed, uint8_t* ADRS, uint32_t l) {
    uint8_t Z[SPX_N + ADRS_SIZE + 4];
    memset(Z, 0, SPX_N + ADRS_SIZE + 4);

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

void PRF (uint8_t* out, uint8_t* SEED, uint8_t* ADRS) {
    uint8_t temp[SPX_N + ADRS_SIZE];

    memcpy(temp, SEED, SPX_N);
    memcpy(temp + SPX_N, ADRS, ADRS_SIZE);

    uint8_t hash[hLen];
    SHA3_256(hash, temp, SPX_N + ADRS_SIZE);
    memcpy(out, hash, SPX_N);
}

void T_l (uint8_t* out, uint8_t* PK_seed_padded, uint8_t* ADRS, uint8_t* M, uint8_t l) {
    uint8_t temp[BLOCK_SIZE + ADRS_SIZE + l * SPX_N];

    memcpy(temp, PK_seed_padded, BLOCK_SIZE);
    memcpy(temp + BLOCK_SIZE, ADRS, ADRS_SIZE);

    if (l > 0) {
        // TODO: adapt to take into account the robust variant as well

        // uint8_t mask[SPX_N * l];
        // mgf1(mask, PK_seed_padded, ADRS, SPX_N * l);

        // int i;
        // for (i = 0; i < SPX_N * l; i++) {
        //     M[i] ^= mask[i];
        // }

        memcpy(temp + BLOCK_SIZE + ADRS_SIZE, M, SPX_N * l);
    }

    uint8_t hash[hLen];
    SHA3_256(hash, temp, BLOCK_SIZE + ADRS_SIZE + l * SPX_N);
    memcpy(out, hash, SPX_N);
}

void chain (uint8_t* out, uint8_t* X, uint32_t i, uint32_t s, uint8_t* PK_seed, uint8_t* ADRS) {
    memcpy(out, X, SPX_N);

    uint8_t PK_seed_padded[BLOCK_SIZE] = { 0 };
    BlockPad(PK_seed_padded, PK_seed);

    uint32_t j;
    for(j = i; j < (i + s) && j < SPX_W; j++) {
        set_hash_addr(ADRS, j);

        F(out, PK_seed_padded, ADRS, out);
    }
}


void wots_PKgen (uint8_t* out, uint8_t* SK_seed, uint8_t* PK_seed, uint8_t* ADRS) {
    uint8_t wotsADRS[ADRS_SIZE];
    memcpy(wotsADRS, ADRS, ADRS_SIZE);

    uint8_t tmp[WOTS_LEN * SPX_N];
    uint32_t i;
    for (i = 0; i < WOTS_LEN; i++) {
        set_chain_addr(ADRS, i);
        set_hash_addr(ADRS, 0);

        uint8_t sk[SPX_N];
        PRF(sk, SK_seed, ADRS);
        chain(tmp + i * SPX_N, sk, 0, SPX_W - 1, PK_seed, ADRS);
    }

    set_layer_type(wotsADRS, WOTS_PK_COMP_ADDRESS);
    set_key_pair_addr(wotsADRS, get_key_pair_addr(ADRS));

    uint8_t PK_seed_padded[BLOCK_SIZE] = { 0 };
    BlockPad(PK_seed_padded, PK_seed);
    T_l(out, PK_seed_padded, wotsADRS, tmp, WOTS_LEN);
}

/**
 * TODO: Adapt this function to work with FORS trees as well
 */
void treehash (uint8_t* out, uint8_t* SK_seed, uint8_t s, uint8_t z, uint8_t* PK_seed, uint8_t* ADRS) {
    if (s % (1 << z) != 0) return;

    treehash_node_t* stack = NULL;

    uint8_t ADRS_leaf[ADRS_SIZE], ADRS_tree[ADRS_SIZE];
    /**
     * TODO: Find a way to create a global ADRS context with the ability to switch
     * when hashing for different layer types
     */
    memcpy(ADRS_leaf, ADRS, ADRS_SIZE);
    memcpy(ADRS_tree, ADRS, ADRS_SIZE);

    for(int i = 0; i < (1 << z); i++) {
        set_layer_type(ADRS_leaf, WOTS_HASH_ADDRESS);
        set_key_pair_addr(ADRS_leaf, s + i);

        uint8_t node[SPX_N];
        wots_PKgen(node, SK_seed, PK_seed, ADRS_leaf);
        /**
         * TODO: Find a nicer solution for resetting the modifications made by WOTS 
         * public key generation function 
         */
        set_chain_addr(ADRS_leaf, 0);
        set_hash_addr(ADRS_leaf, 0);

        set_layer_type(ADRS_tree, HASH_TREE_ADDRESS);
        set_tree_height(ADRS_tree, 1);
        set_tree_index(ADRS_tree, s + i);

        
        while(stack->height == get_tree_height(ADRS_tree)) {
            set_tree_index(ADRS_tree, (get_tree_height(ADRS_tree) - 1) / 2);
            treehash_node_t* top = stack_pop(&stack);

            uint8_t M[2*SPX_N];
            memcpy(M, top->node, SPX_N);
            memcpy(M + SPX_N, node, SPX_N);

            free(top->node);
            free(top);
            
            H(node, PK_seed, ADRS_tree, M);

            set_tree_height(ADRS_tree, get_tree_height(ADRS_tree) + 1);
        }

        treehash_node_t* new_node = malloc(sizeof(treehash_node_t));
        new_node->node = malloc(SPX_N * sizeof(uint8_t));
        memcpy(new_node->node, node, SPX_N);
        new_node->height = get_tree_height(ADRS_tree);
        new_node->next = NULL;

        stack_push(&stack, new_node);
    }

    treehash_node_t* top = stack_pop(&stack);
    memcpy(out, top->node, SPX_N);

    free(top->node);
    free(top);
}

void xmss_PKgen(uint8_t* out, uint8_t* SK_seed, uint8_t* PK_seed, uint8_t* ADRS) {
    treehash(out, SK_seed, 0 , SPX_H_PRIME, PK_seed, ADRS);
}

void ht_PKgen(uint8_t* out, uint8_t* SK_seed, uint8_t* PK_seed) {
    uint8_t ADRS[ADRS_SIZE];
    memset(ADRS, 0 , ADRS_SIZE);

    set_layer_addr(ADRS, SPX_D - 1);
    set_tree_addr(ADRS, 0);

    xmss_PKgen(out, SK_seed, PK_seed, ADRS);
}

void spx_keygen(uint8_t* public_key, uint8_t* secret_key) {
    uint8_t* SK_seed = GenerateBytes(SPX_N);
    uint8_t* SK_prf = GenerateBytes(SPX_N);
    uint8_t* PK_seed = GenerateBytes(SPX_N);

    uint8_t* PK_root = malloc(SPX_N * sizeof(uint8_t));
    ht_PKgen(PK_root, SK_seed, PK_seed);

    // Encapsulate public key (PK_seed, PK_root)
    memcpy(public_key, PK_seed, SPX_N);
    memcpy(public_key + SPX_N, PK_root, SPX_N);

    // Encapsulate secret key (SK_seed, SK_prf, PK_seed, PK_root)
    memcpy(secret_key, SK_seed, SPX_N);
    memcpy(secret_key + SPX_N, SK_prf, SPX_N);
    memcpy(secret_key + 2 * SPX_N, public_key, 2 * SPX_N);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  SPHINCS SIGNATURE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void wots_sign(uint8_t* out, uint8_t* M, uint8_t* SK_seed, uint8_t PK_seed, uint8_t* ADRS) {
    
}