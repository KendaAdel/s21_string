#include "../s21_string.h"

void s21_reversestr(char *strstart) {
  char *strend = strstart + (s21_strlen(strstart) - 1);

  while (strend > strstart) {
    *strstart = *strstart ^ *strend;
    *strend = *strstart ^ *strend;
    *strstart = *strstart ^ *strend;
    strstart++;
    strend--;
  }
}

// Делает инверсию строки
// вспомогательная функция для s21_inttstr для s21_strerror