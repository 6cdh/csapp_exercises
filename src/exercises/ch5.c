#include "ch5.h"

#define op_t unsigned long
#define byte unsigned char
#define OPSIZ (sizeof(op_t))

// 5.17
void *memset(void *s, int c, size_t n) {
    size_t repeat = n / OPSIZ;
    size_t other = n % OPSIZ;
    op_t sp = (op_t)s;
    while ((sp % OPSIZ != 0) && (other-- != 0)) {
        *(byte *)sp = (byte)c;
        sp++;
    }
    op_t pad = (byte)c;
    for (size_t i = 1; i < OPSIZ; i *= 2) {
        pad |= pad << i * 8;
    }
    while (repeat-- != 0) {
        *(op_t *)sp = pad;
        sp += OPSIZ;
    }
    while (other-- != 0) {
        *(byte *)sp = (byte)c;
        sp++;
    }
    return s;
}

// Learn from standard memset
void *memset_plus(void *s, int c, size_t n) {
    op_t sp = (op_t)s;
    if (n >= 8) {
        size_t unaligned = sp % OPSIZ;
        n -= unaligned;
        while (unaligned != 0) {
            *(byte *)sp = (byte)c;
            sp++;
            unaligned--;
        }
        op_t cccc = (byte)c;
        cccc |= cccc << 8;
        cccc |= cccc << 16;
        if (OPSIZ > 4) {
            cccc |= cccc << 32;
        }
        size_t repeat = n / OPSIZ;
        n %= OPSIZ;
        while (repeat >= 8) {
            ((op_t *)sp)[0] = cccc;
            ((op_t *)sp)[1] = cccc;
            ((op_t *)sp)[2] = cccc;
            ((op_t *)sp)[3] = cccc;
            ((op_t *)sp)[4] = cccc;
            ((op_t *)sp)[5] = cccc;
            ((op_t *)sp)[6] = cccc;
            ((op_t *)sp)[7] = cccc;
            sp += OPSIZ * 8;
            repeat -= 8;
        }
        while (repeat != 0) {
            *(op_t *)sp = cccc;
            sp += OPSIZ;
            repeat--;
        }
    }
    while (n != 0) {
        *(byte *)sp = (byte)c;
        sp++;
        n--;
    }
    return s;
}

// Copy from https://github.com/bminor/glibc/blob/master/string/memset.c
void *memset_glibc(void *dstpp, int c, size_t len) {
    long int dstp = (long int)dstpp;

    if (len >= 8) {
        size_t xlen;
        op_t cccc;

        cccc = (byte)c;
        cccc |= cccc << 8;
        cccc |= cccc << 16;
        if (OPSIZ > 4)
            /* Do the shift in two steps to avoid warning if long has 32 bits.
             */
            cccc |= (cccc << 16) << 16;

        /* There are at least some bytes to set.
           No need to test for LEN == 0 in this alignment loop.  */
        while (dstp % OPSIZ != 0) {
            ((byte *)dstp)[0] = c;
            dstp += 1;
            len -= 1;
        }

        /* Write 8 `op_t' per iteration until less than 8 `op_t' remain.  */
        xlen = len / (OPSIZ * 8);
        while (xlen > 0) {
            ((op_t *)dstp)[0] = cccc;
            ((op_t *)dstp)[1] = cccc;
            ((op_t *)dstp)[2] = cccc;
            ((op_t *)dstp)[3] = cccc;
            ((op_t *)dstp)[4] = cccc;
            ((op_t *)dstp)[5] = cccc;
            ((op_t *)dstp)[6] = cccc;
            ((op_t *)dstp)[7] = cccc;
            dstp += 8 * OPSIZ;
            xlen -= 1;
        }
        len %= OPSIZ * 8;

        /* Write 1 `op_t' per iteration until less than OPSIZ bytes remain.  */
        xlen = len / OPSIZ;
        while (xlen > 0) {
            ((op_t *)dstp)[0] = cccc;
            dstp += OPSIZ;
            xlen -= 1;
        }
        len %= OPSIZ;
    }

    /* Write the last few bytes.  */
    while (len > 0) {
        ((byte *)dstp)[0] = c;
        dstp += 1;
        len -= 1;
    }

    return dstpp;
}

// 5.18 CPE = 1.3358 degree = 1000000
double poly(const double a[], double x, size_t degree) {
    double r1 = 0;
    double r2 = 0;
    double r3 = 0;
    double r4 = 0;
    double r5 = 0;
    double r6 = 0;
    double r7 = 0;
    double r8 = 0;
    double xx = x * x;
    const size_t k = 16;
    size_t i = degree;
    while (i > k) {
        i -= k;
        r1 = a[i + 1] + x * a[i] + xx * r1;
        r2 = a[i + 3] + x * a[i + 2] + xx * r1;
        r3 = a[i + 5] + x * a[i + 4] + xx * r3;
        r4 = a[i + 7] + x * a[i + 6] + xx * r4;
        r5 = a[i + 9] + x * a[i + 8] + xx * r5;
        r6 = a[i + 11] + x * a[i + 10] + xx * r6;
        r7 = a[i + 13] + x * a[i + 12] + xx * r7;
        r8 = a[i + 15] + x * a[i + 14] + xx * r8;
    }
    while (i-- > 0) {
        r1 = a[i] + x * r1;
    }
    return r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8;
}

// 5.19 CPE = 1.8753, n = 1000000
void psum(const float a[], float p[], size_t n) {
    p[0] = a[0];
    float t = p[0];
    size_t i = 1;
    size_t k = 3;
    if (n > k) {
        size_t limit = n - k + 1;
        for (; i < limit; i += k) {
            p[i] = t + a[i];
            p[i + 1] = p[i] + a[i + 1];
            p[i + 2] = p[i + 1] + a[i + 2];
            t += a[i] + a[i + 1] + a[i + 2];
        }
    }
    for (; i < n; i++) {
        t += a[i];
        p[i] = t;
    }
}
