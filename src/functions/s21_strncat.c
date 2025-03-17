#include "../s21_string.h"

// Добавляет строку, на которую указывает src, в конец строки, на которую указывает dest, длиной до n
// символов.
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    unsigned char *d = (unsigned char *)dest;
    unsigned char *s = (unsigned char *)src;
    int len_d = s21_strlen((char *)d);
    s21_size_t i;
    for (i = 0; i < n && s[i] != '\0'; i++) {
        d[len_d + i] = s[i];
    }
    d[len_d + i] = '\0';
    return dest;
}