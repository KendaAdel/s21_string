#include "../s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t i = 0;

  while (*str1 && s21_strchr(str2, *str1++)) {
    i++;
  }

  return i;
}

// Вычисляет длину начального сегмента str1,
//  который полностью состоит из символов str2
//  вспомогательная функция для strtok