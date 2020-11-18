#include "ch6.h"

void transpose(int *dst, int *src, int dim) {
    int i, ii, j;
    int bsize = 8;
    int en = bsize * (dim / bsize);
    for (ii = 0; ii < en; ii += bsize) {
        for (j = 0; j < dim; j++) {
            for (i = ii; i < ii + bsize; i++) {
                dst[j * dim + i] = src[i * dim + j];
            }
        }
    }
    for (j = 0; j < dim; j++) {
        for (i = ii; i < dim; i++) {
            dst[j * dim + i] = src[i * dim + j];
        }
    }
}

void col_convert(int *G, int dim) {
    int i, j;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < i; j++) {
            int t = G[i * dim + j] | G[j * dim + i];
            G[i * dim + j] = t;
            G[j * dim + i] = t;
        }
    }
}
