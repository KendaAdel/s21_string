#include "../s21_string.h"

// Сравнивает первые n байтов str1 и str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int flag = 0;
    const unsigned char *ptr1 = (const unsigned char *)str1;
    const unsigned char *ptr2 = (const unsigned char *)str2;
    for (s21_size_t i = 0; i < n; i++) {
        if (ptr1[i] != ptr2[i]) {
            flag = ptr1[i] - ptr2[i];
            break;
        }
    }
    return flag;
}