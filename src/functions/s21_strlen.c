#include "../s21_string.h"

//Вычисляет длину строки str, не включая завершающий нулевой символ.
s21_size_t s21_strlen(const char *str) {
    if (str == S21_NULL) {
        return 0;
    }
    const char *ch = str;
    s21_size_t lenght = 0;
    while (*ch != '\0'){
        lenght++;
        ch++;
    }
    return lenght;
}