#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (!dest || !src) return s21_NULL;  // Проверка на NULL

  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  // Заполняем оставшиеся байты нулями, если src короче n
  for (; i < n; i++) {
    dest[i] = '\0';
  }

  return dest;
}

// Копирует до n символов из строки,
// на которую указывает src, в dest.

// char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
//   if (!n) return dest;  // guard clause

//   char *dest_bck = dest;

//   do {
//     *dest++ = *src++;
//   } while (--n && *(src - 1));

//   return dest_bck;
// }