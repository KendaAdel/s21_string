#include "../s21_string.h"

//Находит первое вхождение всей строки needle (не включая завершающий нулевой символ), которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
    unsigned char *h = (unsigned char *)haystack;
    unsigned char *n = (unsigned char *)needle;

    if (*n == '\0') return (char *)h;
    s21_size_t len_h = s21_strlen((char *)h);
    s21_size_t len_n = s21_strlen((char *)n);
    if (len_h < len_n) return S21_NULL;
    for (s21_size_t i = 0; i <= len_h - len_n; i++) {
        s21_size_t j;
        for (j = 0; j < len_n; j++) {
            if (h[i + j] != n[j]) {
                break;
            }
        }
        if (j == len_n) {
            return (char *)&h[i];
        }
    }

    return S21_NULL;
}