#include "../s21_string.h"

// Копирует до n символов из строки, на которую указывает src, в dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    unsigned char *d = (unsigned char *)dest;
    unsigned char *s = (unsigned char *)src;
    s21_size_t i = 0;
    for (i = 0; i < n && s[i] != '\0'; i++) {
        d[i] = s[i];
    }
    while (i < n) {
        d[i] = '\0';
        i++;
    }
    return dest;
}