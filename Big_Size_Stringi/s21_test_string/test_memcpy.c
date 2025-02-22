#include "s21_test.h"

START_TEST(test_s21_memcpy_1) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  char s3[] = "Good";
  s21_size_t n = 4;
  s21_memcpy(s2, s3, n);
  memcpy(s1, s3, n);
  ck_assert_mem_eq(s1, s2, sizeof(s1));
}
END_TEST

START_TEST(test_s21_memcpy_2) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  char s3[] = "\0";
  s21_size_t n = 1;
  s21_memcpy(s2, s3, n);
  memcpy(s1, s3, n);
  ck_assert_mem_eq(s1, s2, sizeof(s1));
}
END_TEST

START_TEST(test_s21_memcpy_3) {
  char s1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  char s3[] = "f";
  s21_size_t n = 0;
  s21_memcpy(s2, s3, n);
  memcpy(s1, s3, n);
  ck_assert_mem_eq(s1, s2, sizeof(s1));
}
END_TEST

// Тесты с `memcpy`
START_TEST(test_s21_memcpy_11) {
  char src[] = "i hate memcmp";
  s21_size_t kByte = 12;
  char res[kByte + 1];
  char expected[kByte + 1];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_s21_memcpy_23) {
  char src[71] = {0};  // Создаём массив с нулями размером 71 байт
  s21_size_t kByte = 71;
  char res[kByte + 8];
  char expected[kByte + 8];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(test_s21_memcpy_24) {
  char src[1] = {0};  // Исправлено с `char *src = ""`
  s21_size_t kByte = 0;
  char res[kByte + 1];
  char expected[kByte + 1];

  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);

  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

Suite *s21_memcpy_suite() {
  Suite *s;
  TCase *tc_s21_memcpy;
  s = suite_create("s21_memcpy");
  tc_s21_memcpy = tcase_create("s21_memcpy");

  tcase_add_test(tc_s21_memcpy, test_s21_memcpy_1);
  tcase_add_test(tc_s21_memcpy, test_s21_memcpy_2);
  tcase_add_test(tc_s21_memcpy, test_s21_memcpy_3);
  tcase_add_test(tc_s21_memcpy, test_s21_memcpy_11);
  tcase_add_test(tc_s21_memcpy, test_s21_memcpy_23);
  tcase_add_test(tc_s21_memcpy, test_s21_memcpy_24);

  suite_add_tcase(s, tc_s21_memcpy);
  return s;
}
