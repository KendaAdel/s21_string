#include "../s21_string.h"

char* s21_strrchr(const char* str, int c) {
  if (!str) return s21_NULL;  // Проверяем NULL

  char* last_occurrence = s21_NULL;
  char ch = (char)c;  // Приведение к char, как в стандартной реализации

  while (*str) {
    if (*str == ch) {
      last_occurrence =
          (char*)str;  // Обновляем указатель на последнее вхождение
    }
    str++;
  }

  // Если искали '\0', то вернем указатель на конец строки
  if (ch == '\0') {
    return (char*)str;
  }

  return last_occurrence;
}

// Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.

// char *s21_strrchr(const char *str, int c) {
//   c = (unsigned char)c;

//   if (c == '\0') return s21_strchr(str, '\0');

//   const char *found_str = s21_NULL;
//   const char *p = s21_NULL;

//   while ((p = s21_strchr(str, c)) != s21_NULL) {
//     found_str = p;
//     str = p + 1;
//   }

//   return (char *)found_str;
// }