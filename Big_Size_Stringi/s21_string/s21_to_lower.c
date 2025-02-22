#include "../s21_string.h"

void *s21_to_lower(const char *str) {
  if (str == s21_NULL) return s21_NULL;
  char *lo_str = s21_NULL;
  s21_size_t len = s21_strlen(str);
  lo_str = calloc(s21_strlen(str), sizeof(char));
  s21_memcpy(lo_str, str, len);

  int counter = 0;
  for (; (*lo_str) != '\0'; lo_str++, counter++) {
    if (*lo_str >= 'A' && *lo_str <= 'Z') (*lo_str) += 32;
  }

  lo_str -= counter;

  return lo_str;
}

// Возвращает копию строки (str), преобразованную в нижний регистр. В случае
// любой ошибки возвращает NULL.