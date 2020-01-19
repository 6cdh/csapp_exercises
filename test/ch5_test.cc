#include "ch5_test.hpp"

#include <chrono>

TEST(chapter5, memset) {
    const size_t n = 100000000;
    const char c = 'a';
    auto a = new char[n];
    auto start = std::chrono::high_resolution_clock::now();
    memset(a, c, n);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "My memset spend time: " << elapsed.count() << " s\n";
    for (size_t i = 0; i < n; ++i) {
        ASSERT_EQ(a[i], c) << "i = " << i;
    }
    char b[1];
    memset(b, c, 1);
    ASSERT_EQ(b[0], c) << "i = " << 0;
    b[0] = c + 1;
    memset(b, c, 0);
    ASSERT_EQ(b[0], c + 1) << "i = " << 0;
    delete[] a;
}

TEST(chapter5, memset_plus) {
    const size_t n = 100000000;
    const char c = 'a';
    auto a = new char[n];
    auto start = std::chrono::high_resolution_clock::now();
    memset_plus(a, c, n);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "My memset_plus spend time: " << elapsed.count() << " s\n";
    for (size_t i = 0; i < n; ++i) {
        ASSERT_EQ(a[i], c) << "i = " << i;
    }
    char b[1];
    memset_plus(b, c, 1);
    ASSERT_EQ(b[0], c) << "i = " << 0;
    b[0] = c + 1;
    memset_plus(b, c, 0);
    ASSERT_EQ(b[0], c + 1) << "i = " << 0;
    delete[] a;
}

TEST(chapter5, memset_glibc) {
    const size_t n = 100000000;
    const char c = 'a';
    auto a = new char[n];
    auto start = std::chrono::high_resolution_clock::now();
    memset_glibc(a, c, n);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "glibc memset spend time: " << elapsed.count() << " s\n";
    delete[] a;
}

TEST(chapter5, poly) {
    const size_t n = 1000000;
    double a[n];
    for (size_t i = 0; i < n; ++i) {
        a[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }
    const double x = 10;
    auto start = std::chrono::high_resolution_clock::now();
    const auto result = poly(a, x, n);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "poly spend time: " << elapsed.count() << " s\n";
    double true_result = a[0];
    double xpwr = x;
    for (auto v : a) {
        true_result += v * xpwr;
        xpwr *= x;
    }
    ASSERT_FLOAT_EQ(result, true_result);
    ASSERT_FLOAT_EQ(poly(a, x, 1), a[0]);
}

TEST(chapter5, psum) {
    const size_t n = 1000000;
    float a[n];
    float p[n];
    for (size_t i = 0; i < n; ++i) {
        a[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        p[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }
    psum(a, p, n);
    ASSERT_FLOAT_EQ(p[0], a[0]);
    for (size_t i = 1; i < n; ++i) {
        ASSERT_FLOAT_EQ(p[i], p[i-1] + a[i]) << "i = " << i;
    }
    const size_t nn = 1;
    float aa[nn];
    float pp[nn];
    aa[0] = 1;
    pp[0] = 10;
    psum(a, p, nn);
    ASSERT_FLOAT_EQ(p[0], a[0]);
}
