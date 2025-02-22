#include "../s21_string.h"

void* s21_memchr(const void* str, int c, size_t n) {
  unsigned char* ch = (unsigned char*)str;
  unsigned char symb = (unsigned char)c;

  void* p = s21_NULL;
  for (s21_size_t i = 0; i < n && !p; i++) {
    if (ch[i] == symb) {
      p = (void*)&ch[i];
    }
  }
  return p;
}

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str.

// void *s21_memchr(const void *str, int c, s21_size_t n) {
//   unsigned char *ch_ptr = (unsigned char *)str;
//   void *ptr = s21_NULL;

//   for (unsigned int i = 0; i < n && !ptr; i++) {
//     if (*(ch_ptr + i) == (unsigned char)c) ptr = ch_ptr + i;
//   }
//   return ptr;
// }