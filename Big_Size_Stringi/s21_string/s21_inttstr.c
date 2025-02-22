#include "../s21_string.h"

char* s21_inttstr(int num, char* str) {
  int shiftP = 0;
  int sign = 0;
  if (num < 0) {
    *str++ = '-';
    shiftP++;
    sign++;
    num = -num;
  }
  do {
    *str++ = num % 10 + '0';
    num /= 10;
    shiftP++;
  } while (num != 0);
  *str = '\0';
  s21_reversestr(str - shiftP + sign);
  return str;
}

// Переводит целое знаковое число в строку
// вспомогательная ф-ция для s21_strerror