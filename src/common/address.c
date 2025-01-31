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
    ADRS[OFFSET_CHAIN_ADDRESS] = chain_address & 0xFF;
}
void set_hash_addr(uint8_t* ADRS, uint32_t hash_address) {
    ADRS[OFFSET_HASH_ADDRESS] = hash_address & 0xFF;
}