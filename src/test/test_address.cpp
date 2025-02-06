#include <gtest/gtest.h>
#include "common/address.h"

TEST(AddressTest, FieldSetters) {
    uint8_t ADRS[32] = { 0 };

    set_layer_addr(ADRS, 0x20);
    EXPECT_EQ(0x20, ADRS[0]);

    uint8_t tree_addr[8] = {
        0x00, 0x00, 0x00, 0x00,
        0xDE, 0xAD, 0xBE, 0xEF
    };
    set_tree_addr(ADRS, 0xDEADBEEF);
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(tree_addr[i], ADRS[1 + i]);
    }

    set_layer_type(ADRS, 0x20);
    EXPECT_EQ(0x20, ADRS[9]);

    uint8_t key_pair_addr[4] = {
        0xDE, 0xAD, 0xBE, 0xEF
    };
    set_key_pair_addr(ADRS, 0xDEADBEEF);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(key_pair_addr[i], ADRS[10 + i]);
    }

    uint8_t chain_addr[4] = {
        0xDE, 0xAD, 0xBE, 0xEF
    };
    set_chain_addr(ADRS, 0xDEADBEEF);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(chain_addr[i], ADRS[14 + i]);
    }

    uint8_t hash_addr[4] = {
        0xDE, 0xAD, 0xBE, 0xEF
    };
    set_hash_addr(ADRS, 0xDEADBEEF);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(hash_addr[i], ADRS[18 + i]);
    }

}
