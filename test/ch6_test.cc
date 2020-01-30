#include "ch6_test.hpp"

void transpose_true(int *dst, int *src, int dim) {
    int i;
    int j;
    for (i = 0; i < dim; ++i) {
        for (j = 0; j < dim; ++j) {
            dst[j * dim + i] = src[i * dim + j];
        }
    }
}

TEST(chapter6, transpose) {
    const int dim = 100;
    int dst1[dim * dim];
    int src[dim * dim];
    int dst2[dim * dim];

    for (int i = 0; i < dim * dim; ++i) {
        src[i] = rand();
        dst1[i] = rand();
        dst2[i] = rand();
    }
    transpose(dst1, src, dim);
    transpose_true(dst2, src, dim);
    for (int i = 0; i < dim * dim; ++i) {
        ASSERT_EQ(dst1[i], dst2[i]);
    }
}

void col_convert_true(int *G, int dim) {
    int i, j;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            G[i * dim + j] = G[i * dim + j] || G[j * dim + i];
        }
    }
}

TEST(chapter6, col_convert) {
    const size_t dim = 100;
    int G1[dim * dim];
    int G[dim * dim];
    int G2[dim * dim];
    for (size_t i = 0; i < dim * dim; ++i) {
        G[i] = static_cast<int>(rand()) % 2;
        G1[i] =G[i];
        G2[i] = G[i];
    }
    col_convert(G1, dim);
    col_convert_true(G2, dim);
    for (size_t i = 0; i < dim * dim; ++i) {
        ASSERT_EQ(G1[i], G2[i]);
    }
}
