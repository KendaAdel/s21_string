#include "../s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t counter = 0;
  while (*(str++)) {
    counter++;
  }
  return counter;
}

// Вычисляет длину строки str, не включая завершающий нулевой символ.

// s21_size_t s21_strlen(const char *str) {
//   return str ? (*str) ? s21_strlen(++str) + 1 : 0 : 0;
// }