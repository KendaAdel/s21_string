#include "../s21_string.h"

char* s21_strchr(const char* str, int c) {
  while (*str) {
    if (*str == (char)c) {
      return (char*)str;
    }
    str++;
  }

  // Обрабатываем случай поиска нулевого символа '\0'
  return (c == '\0') ? (char*)str : s21_NULL;
}

//  Выполняет поиск первого вхождения символа c (беззнаковый
//  тип) в строке, на которую указывает аргумент str.

// char *s21_strchr(const char *str, int c) {
//   unsigned char *s1 = (unsigned char *)str;
//   unsigned char *ptr = s21_NULL;
//   s21_size_t n = s21_strlen(str);
//   int check = 0;

//   for (s21_size_t i = 0; (i < (n + 1)) && !check; i++) {
//     if (s1[i] == (unsigned char)c) {
//       ptr = &s1[i];
//       check = 1;
//     }
//   }

//   return (char *)ptr;
// }
