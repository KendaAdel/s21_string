#include "../s21_string.h"

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на которую указывает аргумент str.
char *s21_strchr(const char *str, int c) {
    unsigned char *ptr = (unsigned char *)str;
    unsigned char *p = S21_NULL;
    for (int i = 0; ptr[i] != '\0'; ++i) {
        if (ptr[i] == (unsigned char)c) {
            p = (void *)&ptr[i];
            break;
        }
    }
    if ((unsigned char)c == '\0') {
        p = (void *)&ptr[s21_strlen((char *)ptr)];
    }
    return (void *)p;
}