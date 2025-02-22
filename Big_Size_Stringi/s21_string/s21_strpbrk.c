#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *p = s21_NULL;
  char *s = (char *)str1;

  while (*s && !p) {
    for (s21_size_t i = 0; i < s21_strlen(str2) && !p; i++) {
      if (*s == str2[i]) p = s;
    }
    s++;
  }
  return p;
}

// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2.

// char *s21_strpbrk(const char *str1, const char *str2) {
//   char *ptr = s21_NULL;

//   while (*str1 && !ptr) {
//     char *ptr2 = (char *)str2;

//     while (*ptr2 && !ptr)
//       if (*str1 == *ptr2++) ptr = (char *)str1;

//     str1++;
//   }
//   return ptr;
// }