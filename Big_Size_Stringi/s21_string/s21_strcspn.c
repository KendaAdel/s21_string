#include "../s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t counter = 0;
  int t = 0;

  while (*str1 && !t) {
    for (s21_size_t i = 0; str2[i] != '\0'; i++) {
      if (*str1 == str2[i]) {
        t = 1;
        break;
      }
    }
    if (!t) {
      counter++;
      str1++;
    }
  }

  return counter;
}

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.

// s21_size_t s21_strcspn(const char *str1, const char *str2) {
//   s21_size_t n = 0;

//   while (*str1 && !(s21_strchr(str2, *str1))) {
//     str1++;
//     n++;
//   }

//   return n;
// }
