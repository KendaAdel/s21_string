#include "../s21_string.h"

char *s21_trim(const char *src, const char *trim_chars) {
  if (!src) return s21_NULL;

  if (!trim_chars)
    trim_chars = " \t\n\r\f\v";  // Если `trim_chars` пустой, используем
                                 // стандартные пробелы

  // Оптимизация поиска: создаем массив-флаг для trim_chars
  int lookup[256] = {0};
  while (*trim_chars) {
    lookup[(unsigned char)*trim_chars] = 1;
    trim_chars++;
  }

  // Определяем начало обрезанной строки
  while (*src && lookup[(unsigned char)*src]) src++;

  // Определяем конец обрезанной строки
  const char *end = src + s21_strlen(src);
  while (end > src && lookup[(unsigned char)*(end - 1)]) end--;

  // Вычисляем длину результата
  s21_size_t new_length = end - src;

  // Выделяем память под новый обрезанный результат
  char *trimmed = (char *)malloc(new_length + 1);
  if (!trimmed) return s21_NULL;  // Проверка на выделение памяти

  s21_strncpy(trimmed, src, new_length);
  trimmed[new_length] = '\0';  // Завершаем строку

  return trimmed;
}
// Возвращает новую строку, в которой удалены все начальные и конечные вхождения
// набора указанных символов (trim_chars) из заданной строки (src). В случае
// любой ошибки вернуть NULL