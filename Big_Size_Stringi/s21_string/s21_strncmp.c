#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
      return (unsigned char)str1[i] - (unsigned char)str2[i];
    }
  }
  return 0;
}

// Сравнивает не более первых n байтов str1 и str2.

// int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
//   int s = 0;

//   for (s21_size_t i = 0; i < n && s == 0; i++) s = str1[i] - str2[i];

//   return s;
// }
