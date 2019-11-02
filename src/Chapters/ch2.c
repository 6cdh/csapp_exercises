#include "ch2.h"

bool is_little_endian() {
    const uint16_t a = 0x0102;
    byte_pointer bp = (byte_pointer)&a;
    return *bp == 0x02;
}

bool any_bit_of_x_equal_1(int x) { return !(x ^ (~0)); }

bool any_bit_of_x_equal_0(int x) { return !(x | 0); }

bool any_bit_in_lsb_of_x_equal_1(int x) { return !((x & 0xFF) ^ 0xFF); }

bool any_bit_in_msb_of_x_equal_0(int x) {
    return !((x >> ((sizeof(x) - 1) << 3)) | 0);
}

bool int_shifts_are_arithmetic() {
    return (-1 >> ((sizeof(int) << 3) - 1)) == -1;
}

// logical right shift
unsigned srl(unsigned x, int k) {
    unsigned xsra = (int)x >> k;
    unsigned mask = 1 << (sizeof(int) * 8 - k - 1);
    return xsra & (mask | (mask - 1));
}

// arithmetically right shift
int sra(int x, int k) {
    int xsrl = (unsigned)x >> k;
    int mask = (-(((1 << (sizeof(int) * 8 - 1)) & x) != 0))
               << (sizeof(int) * 8 - k - 1);
    return xsrl | mask;
}

bool odd_ones(unsigned x) {
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 1;
}

int leftmost_one(unsigned x) {
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x ^ (x >> 1);
}

unsigned rotate_left(unsigned x, int n) {
    return (x << n) | (x >> (sizeof(x) * 8 - n));
}

int signed_high_prod(int x, int y) {
    int64_t ret = (int64_t)x * y;
    int *p = (int *)&ret;
    return is_little_endian() ? *(p + 1) : *p;
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
    unsigned sx = x >> (sizeof(x) * 8 - 1);
    unsigned sy = x >> (sizeof(y) * 8 - 1);
    return 1 >> (~(sx | sy)) << (1 << (sx & sy));
}

#define _MUL_OVERFLOW(a, b) (((a) * (b) / (a)) != (b))

void *my_calloc(size_t nmemb, size_t size) {
    if ((nmemb == 0) || _MUL_OVERFLOW(nmemb, size)) {
        return NULL;
    }
    size_t n = nmemb * size;
    void *p = malloc(n);
    if (p != NULL) {
        memset(p, 0, n);
    }
    return p;
}

int threefourths(int x) {
    return x - (x >> 2) -
           ((((x & 0x3) + 3) >> 2) ^ (((x >> ((sizeof(int) << 3) - 1))) & 1));
}

float_bits float_twice(float_bits f) {
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp == 0) {
        frac <<= 1;
    } else if (exp < 0xFE) {
        exp += 1;
    } else if (exp == 0xFE) {
        exp = 0xFF;
        frac = 0;
    }
    return (f & 0x80000000) | (exp << 23) | frac;
}

float_bits float_half(float_bits f) {
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp <= 1) {
        frac >>= 1;
        if ((f & 0x3) == 0x3) {
            frac += 1;
        }
        if (exp == 1) {
            frac += 0x00400000;
            exp = 0;
        }
    } else if (exp < 0xFF) {
        exp -= 1;
    }
    return (f & 0x80000000) | (exp << 23) | frac;
}

int float_f2i(float_bits f) {
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    unsigned Bias = 127;
    int n;
    if (exp < 127) {
        n = 0;
    } else if (exp >= 31 + Bias) {
        n = INT_MIN;
    } else {
        unsigned E = exp - Bias;
        unsigned M = frac | 0x800000;
        if (E >= 23) {
            n = M << (E - 23);
        } else {
            n = M >> (23 - E);
        }
        if (f & 0x80000000) {
            n = -n;
        }
    }
    return n;
}

/* float_bits round(float_bits f) { */
/* unsigned exp = f >> 23 & 0xFF; */
/* unsigned frac = f & 0x7FFFFF; */
/* if  */
/* } */

float_bits float_i2f(int x) {
    if (x == 0) {
        return 0;
    }
    unsigned sign = 0;
    if (x < 0) {
        sign = 0x80000000;
        x = -x;
        if (x == INT_MIN) {
            return 0xCF000000;
        }
    }
    unsigned xx = x;
    unsigned i = 0;
    while (xx != 0) {
        i += 1;
        xx >>= 1;
    }
    xx = x;
    int dx = i - 24;
    if (dx > 0) {
        xx >>= dx;
    } else {
        xx <<= -dx;
    }
    unsigned exp = 150 + dx;
    unsigned frac = xx ^ 0x800000;
    // Round
    if (exp > 150) {
        unsigned a = (x & ((1 << dx) - 1));
        unsigned b = 1 << (dx - 1);
        if ((a > b) || ((a == b) && (frac & 1))) {
            frac += 1;
        }
    }
    return sign + (exp << 23) + frac;
}
