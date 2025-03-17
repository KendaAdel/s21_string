#include "../s21_string.h"

// Сравнивает не более первых n байтов str1 и str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    unsigned char *s1 = (unsigned char *)str1;
    unsigned char *s2 = (unsigned char *)str2;
    int flag = 0;
    for (s21_size_t i = 0; i < n; i++) {
        if (s1[i] == '\0' && s2[i] == '\0') {
            flag = 0;
        } else if (s1[i] == '\0') {
            flag = -1;
        } else if (s2[i] == '\0') {
            flag = 1;
        }
        if (s1[i] < s2[i]) {
            flag = -1;
            break;
        } else if (s1[i] > s2[i]) {
            flag = 1;
            break;
        }
    }
    return flag;
}