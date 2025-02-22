#include "s21_strerror.h"

#include "../s21_string.h"

char *s21_strerror(int errnum) {
  static char bufer[100] = "";
  char clean_bufer[100] = "";

  s21_memcpy(bufer, clean_bufer, 100);
  if ((errnum >= 0) && (errnum < ERRLIST_LEN))
    s21_strncpy(bufer, errlist[errnum], sizeof(bufer) + 1);
  else {
    s21_strncpy(bufer, ERR_MSG, sizeof(bufer) + 1);
    char number_err[] = "";
    s21_inttstr(errnum, number_err);
    s21_strncat(bufer, number_err, sizeof(bufer) + s21_strlen(number_err) - 1);
  }
  return bufer;
}

// Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
//  указатель на строку с сообщением об ошибке. Нужно объявить макросы,
//  содержащие массивы сообщений об ошибке для операционных систем mac и linux