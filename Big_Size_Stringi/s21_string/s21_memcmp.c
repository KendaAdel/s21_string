#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = (unsigned char *)str1;
  const unsigned char *s2 = (unsigned char *)str2;
  int st = 0;

  while ((st == 0) && n--) {
    if (*s1++ != *s2++) st = *--s1 - *--s2;
  }

  return st;
}

// Сравнивает первые n байтов str1 и str2.

// int s21_memcmp(const void* str1, const void* str2, size_t n) {
//   s21_size_t i = 0;
//   char* s1 = (char*)str1;
//   char* s2 = (char*)str2;
//   for (i < n; (s1[i] == s2[i]) && s1[i] && s2[i]; i++) {
//   }
//   return (s1[i] - s2[i]);
