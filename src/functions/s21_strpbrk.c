#include "../s21_string.h"

// Находит первый символ в строке str1, который соответствует любому символу, указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
    unsigned char *s1 = (unsigned char *)str1;
    unsigned char *s2 = (unsigned char *)str2;
    s21_size_t i = 0, j = 0, flag = 0;
    for (i = 0; s1[i] != '\0' && flag == 0; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                flag = 1;
                break;
            }
        }
        if (flag) break;
    }
    if (flag) return (char *)&s1[i];
    else return S21_NULL;
}