#include "s21_test.h"
int main() {
  int number_failed = 0;
  Suite *s21func[] = {s21_strtok_suite(),
                        s21_strlen_suite(),
                        s21_memchr_suite(),
                        s21_memcmp_suite(),
                        s21_memcpy_suite(),
                        s21_memset_suite(),
                        s21_strcspn_suite(),
                        s21_strchr_suite(),
                        s21_strncpy_suite(),
                        s21_strncat_suite(),
                        s21_strncmp_suite(),
                        s21_strrchr_suite(),
                        s21_strstr_suite(),
                        s21_strpbrk_suite(),
                        s21_strerror_suite(),
                        s21_sprintf_suite(),
                        NULL};

  for (int i = 0; s21func[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21func[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_ENV);

    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= TOTAL FAILED: %d =========\n", number_failed);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;

  return 0;
}
