#include "bytes.h"

void show_bytes(byte_pointer start, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}