#include "common/address.h"
#include "common/utils.h"

void set_layer_addr(uint8_t* ADRS, uint32_t layer_address) {
    ADRS[OFFSET_LAYER_ADDRESS] = layer_address & 0xFF;
}

void set_tree_addr(uint8_t* ADRS, uint64_t tree_address) {
    ui64_to_bytes(&ADRS[OFFSET_TREE_ADDRESS], tree_address, 8);
}

void set_layer_type(uint8_t* ADRS, uint32_t layer_type) {
    ADRS[OFFSET_LAYER_TYPE] = layer_type & 0xFF;
}

void set_key_pair_addr(uint8_t* ADRS, uint32_t key_pair_address) {
    ui32_to_bytes(&ADRS[OFFSET_KEY_PAIR_ADDRESS], key_pair_address);
}

void set_chain_addr(uint8_t* ADRS, uint32_t chain_address) {
    ui32_to_bytes(&ADRS[OFFSET_CHAIN_ADDRESS], chain_address);
}
void set_hash_addr(uint8_t* ADRS, uint32_t hash_address) {
    ui32_to_bytes(&ADRS[OFFSET_HASH_ADDRESS], hash_address);
}
uint32_t get_key_pair_addr(uint8_t* ADRS) {
    return ((uint32_t) ADRS[OFFSET_KEY_PAIR_ADDRESS] << 24) |
           ((uint32_t) ADRS[OFFSET_KEY_PAIR_ADDRESS + 1] << 16) |
           ((uint32_t) ADRS[OFFSET_KEY_PAIR_ADDRESS + 2] << 8) |
           ((uint32_t) ADRS[OFFSET_KEY_PAIR_ADDRESS + 3]);
}

uint32_t get_tree_height(uint8_t* ADRS) {
    return ((uint32_t) ADRS[OFFSET_TREE_HEIGHT] << 24) |
           ((uint32_t) ADRS[OFFSET_TREE_HEIGHT + 1] << 16) |
           ((uint32_t) ADRS[OFFSET_TREE_HEIGHT + 2] << 8) |
           ((uint32_t) ADRS[OFFSET_TREE_HEIGHT + 3]);
}

uint32_t get_tree_index(uint8_t* ADRS) {
    return ((uint32_t) ADRS[OFFSET_TREE_INDEX] << 24) |
           ((uint32_t) ADRS[OFFSET_TREE_INDEX + 1] << 16) |
           ((uint32_t) ADRS[OFFSET_TREE_INDEX + 2] << 8) |
           ((uint32_t) ADRS[OFFSET_TREE_INDEX + 3]);
}

