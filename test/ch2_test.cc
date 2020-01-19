#include "ch2_test.hpp"

TEST(chapter2, is_little_endian) { EXPECT_EQ(is_little_endian(), true); }

TEST(chapter2, any_bit_of_x_equal_1) {
    EXPECT_EQ(any_bit_of_x_equal_1(0), false);
    EXPECT_EQ(any_bit_of_x_equal_1(~0), true);
    EXPECT_EQ(any_bit_of_x_equal_1(0x1), false);
}

TEST(chapter2, any_bit_of_x_equal_0) {
    EXPECT_EQ(any_bit_of_x_equal_0(0), true);
    EXPECT_EQ(any_bit_of_x_equal_0(~0), false);
    EXPECT_EQ(any_bit_of_x_equal_0(0x1), false);
}

TEST(chapter2, allbit_in_lsb_of_x_equal_1) {
    EXPECT_EQ(any_bit_in_lsb_of_x_equal_1(0), false);
    EXPECT_EQ(any_bit_in_lsb_of_x_equal_1(0xFF), true);
    EXPECT_EQ(any_bit_in_lsb_of_x_equal_1(~0), true);
    EXPECT_EQ(any_bit_in_lsb_of_x_equal_1(0xF), false);
}

TEST(chapter2, any_bit_in_msb_of_x_equal_0) {
    EXPECT_EQ(any_bit_in_msb_of_x_equal_0(0), true);
    EXPECT_EQ(any_bit_in_msb_of_x_equal_0(~0), false);
    EXPECT_EQ(any_bit_in_msb_of_x_equal_0(~(0xFF << ((sizeof(int) - 1) << 3))),
              true);
}

TEST(chapter2, int_shifts_are_arithmetic) {
    EXPECT_EQ(int_shifts_are_arithmetic(), true);
}

TEST(chapter2, srl) {
    EXPECT_EQ(srl(0x10, 4), 1);
    EXPECT_EQ(srl(-1, sizeof(int) * 8 - 1), 1);
}

TEST(chapter2, sra) {
    EXPECT_EQ(sra(0x10, 4), 0x10 >> 4);
    EXPECT_EQ(sra(-1, 4), -1 >> 4);
    EXPECT_EQ(sra(INT_MIN, 4), INT_MIN >> 4);
    EXPECT_EQ(sra(0x10, 0), 0x10);
}

TEST(chapter2, odd_ones) {
    EXPECT_EQ(odd_ones(0x01), true);
    EXPECT_EQ(odd_ones(0), false);
    EXPECT_EQ(odd_ones(~0), false);
    EXPECT_EQ(odd_ones(0xAAAAAAAA), false);
    EXPECT_EQ(odd_ones(0xAAAAAAAB), true);
}

TEST(chapter2, leftmost_one) {
    EXPECT_EQ(leftmost_one(0), 0);
    EXPECT_EQ(leftmost_one(0x10), 0x10);
    EXPECT_EQ(leftmost_one(0xFF00), 0x8000);
    EXPECT_EQ(leftmost_one(0x6600), 0x4000);
    EXPECT_EQ(leftmost_one(~0), INT_MIN);
}

TEST(chapter2, rotate_left) {
    EXPECT_EQ(rotate_left(0x12345678, 4), 0x23456781);
    EXPECT_EQ(rotate_left(0x12345678, 20), 0x67812345);
    EXPECT_EQ(rotate_left(0x12345678, 0), 0x12345678);
}

TEST(chapter2, unsigned_high_prod) {
    auto i = (uint32_t)INT_MIN;
    uint64_t mul = i * i;
    auto *p = (uint32_t *)&mul;
    EXPECT_EQ(unsigned_high_prod(i, i), *(p + 1));
    uint32_t ii = (uint32_t)INT_MIN + (1 << 30);
    uint64_t mull = ii * ii;
    auto *pp = (uint32_t *)&mull;
    EXPECT_EQ(unsigned_high_prod(ii, ii), *(pp + 1));
}

TEST(chapter2, my_calloc) {
    size_t x = 10;
    void *p = my_calloc(sizeof(size_t), x);
    EXPECT_NE((size_t)p, NULL);
    free(p);
}
TEST(chapter2, threefourths) {
    EXPECT_EQ(threefourths(4), 3);
    EXPECT_EQ(threefourths(8), 6);
    EXPECT_EQ(threefourths(9), 9 * 3 / 4);
    EXPECT_EQ(threefourths(-9), -6);
}

/* TEST(chapter2, float_twice) { */
// for (float_bits i = 0; i <= 0x7F800000; ++i) {
//     auto ret = float_twice(i);
//     auto expect_value = (2 * (*((float *)&i)));
//     ASSERT_EQ(ret, (*((float_bits *)&expect_value)))
//         << "Argument: " << (*((float *)&i)) << " == 0x" << std::hex << i
//         << "\nValue: " << (*((float *)&ret)) << " == 0x" << std::hex << ret
//         << "\nExpect: " << expect_value << " == 0x" << std::hex
//         << (*((float_bits *)&expect_value));
// }
// for (float_bits i = 0x80000000; i <= 0x8F800000; ++i) {
//     auto ret = float_twice(i);
//     auto expect_value = (2 * (*((float *)&i)));
//     ASSERT_EQ(ret, (*((float_bits *)&expect_value)))
//         << "Argument: " << (*((float *)&i)) << " == 0x" << std::hex << i
//         << "\nValue: " << (*((float *)&ret)) << " == 0x" << std::hex << ret
//         << "\nExpect: " << expect_value << " == 0x" << std::hex
//         << (*((float_bits *)&expect_value));
// }
/* } */

/* TEST(chapter2, float_half) { */
// for (float_bits i = 0; i <= 0x7F800000; ++i) {
//     auto ret = float_half(i);
//     auto expect_value = ((*((float *)&i)) * 0.5F);
//     ASSERT_EQ(*((float *)&ret), expect_value)
//         << "Argument: " << (*((float *)&i)) << " == 0x" << std::hex << i
//         << "\nValue: " << (*((float *)&ret)) << " == 0x" << std::hex << ret
//         << "\nExpect: " << expect_value << " == 0x" << std::hex
//         << (*((float_bits *)&expect_value));
// }
// for (float_bits i = 0x80000000; i <= 0x8F800000; ++i) {
//     auto ret = float_half(i);
//     auto expect_value = ((*((float *)&i)) * 0.5F);
//     ASSERT_FLOAT_EQ(*((float *)&ret), expect_value)
//         << "Argument: " << (*((float *)&i)) << " == 0x" << std::hex << i
//         << "\nValue: " << (*((float *)&ret)) << " == 0x" << std::hex << ret
//         << "\nExpect: " << expect_value << " == 0x" << std::hex
//         << (*((float_bits *)&expect_value));
// }
/* } */

/* TEST(chapter2, float_f2i) { */
// for (float_bits i = 0; i != 0xFFFFFFFF; ++i) {
//     auto ret = Float{.binary = i};
//     ASSERT_EQ(float_f2i(i), (int)ret.f) << "i: " << std::hex << i;
// }
/* } */

// TEST(chapter2, float_i2f) {
//     for (int i = INT_MIN; i != INT_MAX; ++i) {
//         auto res = Float{.binary = float_i2f(i)};
//         auto ret = Float{.f = (float)i};
//         ASSERT_EQ(res.binary, ret.binary)
//             << "i: " << std::hex << "0x" << i << " = " << std::dec << i
//             << "\nReturn: " << std::hex << "0x" << res.binary << " = " << res.f
//             << "\nExpect: " << std::hex << "0x" << ret.binary << " = " << ret.f;
//     }
//     auto ret = Float{.f = (float)INT_MAX};
//     ASSERT_EQ(float_i2f(INT_MAX), ret.binary);
/* } */
