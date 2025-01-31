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
#define OFFSET_CHAIN_ADDRESS    (17)
#define OFFSET_HASH_ADDRESS     (21)
#else
#define ADRS_SIZE               (32)
#define OFFSET_LAYER_ADDRESS    (3)
#define OFFSET_TREE_ADDRESS     (8)
#define OFFSET_LAYER_TYPE       (19)
#define OFFSET_KEY_PAIR_ADDRESS (20)
#define OFFSET_CHAIN_ADDRESS    (27)
#define OFFSET_HASH_ADDRESS     (31)
#endif

#include <stdint.h>

void set_layer_addr(uint8_t* ADRS, uint32_t layer_address);
void set_tree_addr(uint8_t* ADRS, uint64_t tree_address);
void set_layer_type(uint8_t* ADRS, uint32_t layer_type);
void set_key_pair_addr(uint8_t* ADRS, uint32_t key_pair_address);
void set_chain_addr(uint8_t* ADRS, uint32_t chain_address);
void set_hash_addr(uint8_t* ADRS, uint32_t hash_address);

#endif // ADDRESS_H