#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {
  if (src == s21_NULL || str == s21_NULL || s21_strlen(src) < start_index)
    return s21_NULL;
  s21_size_t len = s21_strlen(src);
  char *new_src = (char *)malloc(s21_strlen(src) + s21_strlen(str) + 1);
  if (!new_src) return s21_NULL;

  s21_strncpy(new_src, src, start_index);
  s21_strncpy(new_src + start_index, str, s21_strlen(str));
  s21_strncpy(new_src + start_index + s21_strlen(str), src + start_index,
              len - start_index + 1);
  return new_src;
}

// Возвращает новую строку, в которой указанная строка (str) вставлена
// ​​в указанную позицию индекса (start_index) в
// заданной строке (src). В случае любой ошибки вернуть NULL.
