#include "../s21_string.h"

// Копирует n символов из src в dest.
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    for (s21_size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}