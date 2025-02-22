#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) return s21_NULL;
  char *up_str = s21_NULL;
  s21_size_t len = s21_strlen(str);
  up_str = calloc(s21_strlen(str), sizeof(char));
  s21_memcpy(up_str, str, len);

  int counter = 0;
  for (; (*up_str) != '\0'; up_str++, counter++) {
    if (*up_str >= 'a' && *up_str <= 'z') (*up_str) -= 32;
  }

  up_str -= counter;

  return up_str;
}

// Возвращает копию строки (str), преобразованную в верхний регистр. В случае
// любой ошибки возвращает NULL