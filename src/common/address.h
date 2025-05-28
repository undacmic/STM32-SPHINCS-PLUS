#ifndef ADDRESS_H
#define ADDRESS_H

/*
* Hash Function Address Scheme (ADRS)
* +----------------------+-------------------------------------------------------------------+
* |    layer address     |                            tree address                           |
* +----------------------+----------------------+----------------------+---------------------+
* |        type = 0      |  key pair address    |    chain address     |    hash address     |
* +----------------------+----------------------+----------------------+---------------------+
*/

/**
 *  Layer Types:
 * - WOTS+ hash address (0)
 * - WOTS+ public key compression address (1)
 * - hash tree address (2)
 * - FORS tree address (3)
 * - FORS tree roots compression address (4)
 */

#ifdef HASH_SHA3
/**
 * Rather than storing the layer address and type field in a full 4-byte word each,
 *  we only include the least-significant byte of each.
 *  Similarly, we only include the least-significant 8 bytes of the 12-byte tree address.
 */
#define ADRS_SIZE               (22)
#define OFFSET_LAYER_ADDRESS    (0)
#define OFFSET_TREE_ADDRESS     (1)
#define OFFSET_LAYER_TYPE       (9)
#define OFFSET_KEY_PAIR_ADDRESS (10)
#define OFFSET_CHAIN_ADDRESS    (14)
#define OFFSET_TREE_HEIGHT      (14)
#define OFFSET_HASH_ADDRESS     (18)
#define OFFSET_TREE_INDEX       (18)
#else
#define ADRS_SIZE               (32)
#define OFFSET_LAYER_ADDRESS    (3)
#define OFFSET_TREE_ADDRESS     (8)
#define OFFSET_LAYER_TYPE       (19)
#define OFFSET_KEY_PAIR_ADDRESS (20)
#define OFFSET_CHAIN_ADDRESS    (27)
#define OFFSET_TREE_HEIGHT      (27)
#define OFFSET_HASH_ADDRESS     (31)
#define OFFSET_TREE_INDEX       (31)
#endif

#define WOTS_HASH_ADDRESS               (0)
#define WOTS_PK_COMP_ADDRESS            (1)
#define HASH_TREE_ADDRESS               (2)
#define FORS_TREE_ADDRESS               (3)
#define FORS_TREE_ROOTS_COMP_ADDRESS    (4)

#include <stdint.h>

#define set_tree_height(ADRS, tree_height)    set_chain_addr(ADRS, tree_height)
#define set_tree_index(ADRS, tree_index)      set_hash_addr(ADRS, tree_index)

void set_layer_addr(uint8_t* ADRS, uint32_t layer_address);
void set_tree_addr(uint8_t* ADRS, uint64_t tree_address);
void set_layer_type(uint8_t* ADRS, uint32_t layer_type);
void set_key_pair_addr(uint8_t* ADRS, uint32_t key_pair_address);
void set_chain_addr(uint8_t* ADRS, uint32_t chain_address);
void set_hash_addr(uint8_t* ADRS, uint32_t hash_address);

uint32_t get_key_pair_addr(uint8_t* ADRS);
uint32_t get_tree_height(uint8_t* ADRS);
uint32_t get_tree_index(uint8_t* ADRS);
#endif // ADDRESS_H