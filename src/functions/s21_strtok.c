#include "../s21_string.h"

// Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim) {
    static char *last = S21_NULL;
    if (str) {
        last = str;
    }
    
    if (last == S21_NULL) {
        return S21_NULL;
    }

    while (*last && s21_strchr(delim, *last)) {
        last++;
    }

    if (*last == '\0') {
        last = S21_NULL;
        return S21_NULL;
    }

    char *token_start = last; 
    while (*last && !s21_strchr(delim, *last)) {
        last++;
    }

    if (*last) {
        *last = '\0';
        last++;
    } else {
        last = S21_NULL;
    }

    return token_start;
}