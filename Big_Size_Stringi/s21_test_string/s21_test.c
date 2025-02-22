#include "s21_test.h"

int main() {
  int number_failed = 0;
  Suite *s21sscanf[] = {
      // test_sscanf_c(),

      //                       test_sscanf_o(),
      //                       test_sscanf_x(),
      //                       test_sscanf_d(),
      //                       test_sscanf_i(),
      //                       test_sscanf_p(),
      //                       test_sscanf_s(),
      //                       test_sscanf_real(),
      //                       test_sscanf_n(),
      //                       test_sscanf_empty(),
      //                       s21_sscanf_suite(),
      s21_to_upper_suite(), s21_to_lower_suite(), s21_insert_suite(),
      s21_trim_suite(), s21_strlen_suite(), s21_memchr_suite(),
      s21_memcmp_suite(), s21_memcpy_suite(), s21_memset_suite(),
      s21_strtok_suite(), s21_strcspn_suite(), s21_strchr_suite(),
      s21_strncpy_suite(), s21_strncat_suite(), s21_strncmp_suite(),
      s21_strrchr_suite(), s21_strstr_suite(), s21_strpbrk_suite(),
      s21_strerror_suite(),
      // s21_all_2_suite(),
      s21_sprintf_suite(),

      NULL};

  for (int i = 0; s21sscanf[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21sscanf[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_ENV);
    // srunner_run_all(sr, CK_ENV);
    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= TOTAL FAILED: %d =========\n", number_failed);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;

  return 0;
}
