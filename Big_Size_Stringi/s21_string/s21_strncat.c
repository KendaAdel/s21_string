#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t l = s21_strlen(dest);
  for (s21_size_t i = 0; i < n; i++) {
    dest[i + l] = src[i];
  }
  return dest;
}
// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длиной до n символов.