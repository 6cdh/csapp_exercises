#ifndef EXER_H
#define EXER_H

#include <fenv.h>
#include <limits.h>
#include <math.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bytes.h"

typedef unsigned float_bits;

typedef union {
    float_bits binary;
    float f;
} Float;

bool is_little_endian();
bool any_bit_of_x_equal_1(int x);
bool any_bit_of_x_equal_0(int x);
bool any_bit_in_lsb_of_x_equal_1(int x);
bool any_bit_in_msb_of_x_equal_0(int x);
bool int_shifts_are_arithmetic();
unsigned srl(unsigned x, int k);
int sra(int x, int k);
bool odd_ones(unsigned x);
int leftmost_one(unsigned x);
unsigned rotate_left(unsigned x, int n);
unsigned unsigned_high_prod(unsigned x, unsigned y);
void *my_calloc(size_t nmemb, size_t size);
int threefourths(int x);
float_bits float_twice(float_bits f);
float_bits float_half(float_bits f);
int float_f2i(float_bits f);
float_bits float_i2f(int x);

#endif
