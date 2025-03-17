#include "../s21_string.h"

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n байтах строки, на которую
// указывает аргумент str.
void *s21_memchr(const void *str, int c, s21_size_t n) {
    unsigned char *p = S21_NULL;
    const unsigned char *ptr = (const unsigned char *)str;
    for (s21_size_t i = 0; i < n; i++) {
        if (ptr[i] == (unsigned char)c) {
            p = (void *)&ptr[i];
            break;
        }
    }
    return p;
}