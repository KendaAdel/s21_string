#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, size_t n) {
  if (n == 0 || dest == src) return dest;
  for (s21_size_t i = 0; i < n; i++) {
    ((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
  }
  return dest;
}

// Копирует n символов из src в dest.