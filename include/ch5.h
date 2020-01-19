typedef unsigned long size_t;

void *memset(void *s, int c, size_t n);
void *memset_plus(void *s, int c, size_t n);
void *memset_glibc(void *dstpp, int c, size_t len);
double poly(const double a[], double x, size_t degree);
void psum(const float a[], float p[], size_t n);
