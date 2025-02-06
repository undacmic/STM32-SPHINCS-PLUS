#include <gtest/gtest.h>
#include "common/utils.h"

TEST(UtilsTest, U32ToBytes) {
    uint8_t actual[4];
    uint8_t expected[][4] = {
        {0x00, 0x00, 0x00, 0x00},
        {0x49, 0x96, 0x02, 0xD2},
        {0xFF, 0xFF, 0xFF, 0xFF}
    };

    ui32_to_bytes(actual, 0);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(expected[0][i], actual[i]);
    }

    ui32_to_bytes(actual, 1234567890);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(expected[1][i], actual[i]);
    }

    ui32_to_bytes(actual, -1);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(expected[2][i], actual[i]);
    }
}

TEST(UtilsTest, U64ToBytes) {
    uint8_t actual[32];

    uint8_t expected1[32] = { 0 };
    ui64_to_bytes(actual, 0, 32);
    for (int i = 0; i < 32; i++) {
        EXPECT_EQ(expected1[i], actual[i]);
    }

    uint8_t expected2[16] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x01, 0xB6, 0x9B, 0x4B,
        0xAC, 0xD0, 0x5F, 0x15
    };
    ui64_to_bytes(actual, 123456789123456789, 16);
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(expected2[i], actual[i]);
    }

    uint8_t expected3[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    ui64_to_bytes(actual, -1, 8);
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(expected3[i], actual[i]);
    }

}