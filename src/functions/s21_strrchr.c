#include "../s21_string.h"

//Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на которую указывает аргумент str.
char *s21_strrchr(const char *str, int c) {
    unsigned char *ptr = (unsigned char *)str;
    unsigned char * p =S21_NULL;
    for (int i = s21_strlen((char *)ptr); i >= 0; i--) {
        if (ptr[i] == (unsigned char)c) {
            p = (unsigned char *)&ptr[i];
            break;
        }
    }
    if ((unsigned char)c == '\0') {
        p = (unsigned char *)&ptr[s21_strlen((char *)ptr)];
    }
    return (void *)p;
}