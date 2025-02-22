#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  // создаем статическую переменную str_n что б сохронить указатель токена
  static char *str_n = s21_NULL;
  char *str1 = str;
  char *end;

  if (!str1) str1 = str_n;
  str1 += s21_strspn(str1, delim);
  // получаем длину последовательности разделителей и двигаем указатель
  if (*str1 == '\0') {
    str_n = str1;
    str1 = s21_NULL;
  } else {
    end = str1 + s21_strcspn(str1, delim);
    if (*end == '\0') {
      str_n = end;
    } else {
      *end = '\0';
      str_n = end + 1;
    }
  }
  return str1;
}

// Разбивает строку str на ряд токенов, разделенных delim.