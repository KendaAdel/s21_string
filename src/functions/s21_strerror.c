#include "../s21_string.h"

// Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает указатель на строку с сообщением об
// ошибке. Нужно объявить макросы, содержащие массивы сообщений об ошибке для операционных систем mac и linux.
// Описания ошибок есть в оригинальной библиотеке. Проверка текущей ОС осуществляется с помощью директив.
char *s21_strerror(int errnum) {
    static const char *messages[] = ERROR_MESSAGES;
    static char unknown_error[50];

    if (errnum < 0 || errnum > (int)(sizeof(messages) / sizeof(messages[0])) || errnum > 133) {
        snprintf(unknown_error, sizeof(unknown_error), "Unknown error %d", errnum);
        return unknown_error;
    }
    return (char *)messages[errnum];
}