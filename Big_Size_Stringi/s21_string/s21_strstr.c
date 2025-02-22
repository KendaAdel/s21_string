#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  if (!(*needle)) return (char *)haystack;  // Пустая строка всегда найдена

  s21_size_t h = s21_strlen(haystack);
  s21_size_t n = s21_strlen(needle);
  if (h < n) return s21_NULL;  // Если needle длиннее haystack, выхода нет

  for (s21_size_t i = 0; i <= h - n;
       i++) {                        // <= вместо < для корректного прохода
    if (haystack[i] == needle[0]) {  // Потенциальное совпадение
      s21_size_t j = 0;
      while (j < n && haystack[i + j] == needle[j]) j++;
      if (j == n) return (char *)(haystack + i);  // Нашли подстроку
    }
  }
  return s21_NULL;  // Не нашли
}

// Находит первое вхождение всей строки needle (не включая завершающий нулевой
// символ), которая появляется в строке haystack.