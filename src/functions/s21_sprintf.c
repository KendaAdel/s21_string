// #include <string.h>
#include "../s21_string.h"

typedef struct s21_sprintf {
  int precision;
  int width;
  short int is_width;
  short int is_precision;
  short int plus;
  short int minus;
  short int space;
  short int zero;
  short int error;
  char specificator;
  char longshort;
} state_of_speca;

int read_format(char *str, const char *format, state_of_speca *state,
                va_list *arg_list);
int handle_speca(char *str, char *speca, state_of_speca *state,
                 va_list *arg_list);
int what_is_type(char *speca, state_of_speca *state);
int what_is_flags(char *speca, state_of_speca *state);
int what_is_width(char *speca, state_of_speca *state, int i);
int what_is_precision(char *speca, state_of_speca *state, int i);
int what_is_speca(char *str, char *speca, state_of_speca *state,
                  va_list *arg_list);
int speca_is_s(char *str, state_of_speca *state,
               va_list *arg_list);
int speca_is_c(char *str, state_of_speca *state,
               va_list *arg_list);
int speca_is_d(char *str, state_of_speca *state,
               va_list *arg_list);
int speca_is_f(char *str, state_of_speca *state,
               va_list *arg_list);

short int handle_overflow(int x);
char *my_itoa(long n, char int_type);
char *handle_flags_d(state_of_speca *state, char *strnbr);
char *handle_flags_f(state_of_speca *state, char *strnbr);
char *float_to_string(double number, int precision, int is_precision);
int handle_speca_c(char *str, state_of_speca *state,
                   va_list *arg_list);
int handle_speca_lc(char *str, state_of_speca *state,
                    va_list *arg_list);
int handle_speca_s(char *str, state_of_speca *state, char *stroka);
int handle_speca_ls(char *str, state_of_speca *state,
                    va_list *arg_list);
char *s21_strdup(const char *s);

/************************************************************************************/

int s21_sprintf(char *str, const char *format, ...) {
  int result = 0;

  state_of_speca speca_state = {0};
  va_list arg_list;
  va_start(arg_list, format);
  result = read_format(str, format, &speca_state, &arg_list);
  va_end(arg_list);
  return result;
}

/***********************************************************************************/

int read_format(char *str, const char *format, state_of_speca *state,
                va_list *arg_list) {
  int is_alpha = 0, result = 0;
  s21_size_t flag = 0;
  char *speca = malloc(20 * sizeof(char));
  char *format_work = s21_strdup(format);

  if (!speca || !format_work) {
    free(speca);
    free(format_work);
    flag = 1;
  } else {
    char *temp_format = format_work;
    s21_memset(str, 0, s21_strlen(str));
    for (s21_size_t i = 0; temp_format[i] != '\0' && !result; i++) {
      if ((temp_format[i] == '%') && (temp_format[i + 1] != '%')) {

        s21_strncat(str, temp_format, i);

        while (!isalpha(temp_format[i + is_alpha]) && (temp_format[i + is_alpha] != '\0'))
          is_alpha++;

        if ((temp_format[i + is_alpha] == 'l') || (temp_format[i + is_alpha] == 'h'))
          is_alpha++;

        is_alpha++;
        s21_memset(speca, 0, 20);
        s21_strncat(speca, temp_format + i, is_alpha);
        temp_format += (i + is_alpha);
        i = -1;
        is_alpha = 0;
        result = handle_speca(str, speca, state, arg_list);

      } else if ((temp_format[i] == '%') && (temp_format[i + 1] == '%')) {
        s21_strncat(str, temp_format, i);  // Выводим то, что до % в str
        s21_strncat(str, "%", 1);              // Добавляем один символ % в конец str
        temp_format += (i + 2);        // Изменяем временный указатель
        i = -1;                        // Сбрасываем счетчик
      } else if (temp_format[i + 1] == '\0') {
        s21_strncat(str, temp_format, i + 1);
      }
    }
    free(format_work);  // Освобождаем исходную копию
    free(speca);        // Освобождаем память для speca
    flag =  s21_strlen(str);
  }
  return flag;
}

/***********************************************************************************/

char *s21_strdup(const char *s) {
  size_t len = s21_strlen(s) + 1; // +1 для нулевого символа
  char *copy = malloc(len);
  if (copy) {
    s21_memcpy(copy, s, len);
  }
  return copy;
}

/***********************************************************************************/

int handle_speca(char *str, char *speca, state_of_speca *state, va_list *arg_list) {
  *state = (state_of_speca){0};
  int result = 0;
  state->specificator = speca[s21_strlen(speca) - 1];  // Последний символ - спецификатор
  result = what_is_flags(speca, state);
  if (!result) result = what_is_speca(str, speca, state, arg_list);
  return result;
}

int what_is_flags(char *speca, state_of_speca *state) {
  int result = 0;
  s21_size_t len = s21_strlen(speca);
  for (s21_size_t i = 1; i < len - 1 && !result; i++) {
    if (speca[i] == '-')
      state->minus++;
    else if (speca[i] == '+')
      state->plus++;
    else if (speca[i] == ' ')
      state->space++;
    else if (speca[i] == 'l' && state->longshort != 'h')
      state->longshort = 'l';
    else if (speca[i] == 'h' && state->longshort != 'l')
      state->longshort = 'h';
    else if (isdigit(speca[i]) && !state->is_width && !state->is_precision)
      i = what_is_width(speca, state, i);
    else if (speca[i] == '.' && !state->is_precision) {
      i++;
      i = what_is_precision(speca, state, i);
    } else {
      state->error++;
      result = 1;
    }
  }
  return result;
}

int what_is_width(char *speca, state_of_speca *state, int i) {
  while (speca[i] && isdigit(speca[i])) {
    state->width = state->width * 10 + (speca[i] - '0');
    i++;
  }
  state->is_width++;
  return i - 1;
}

int what_is_precision(char *speca, state_of_speca *state, int i) {
  while (speca[i] && isdigit(speca[i])) {
    state->precision = state->precision * 10 + (speca[i] - '0');
    i++;
  }
  state->is_precision++;
  return i - 1;
}

int what_is_speca(char *str, char *speca, state_of_speca *state,
                  va_list *arg_list) {
  int result = 0;
  int len = s21_strlen(speca);
  switch (speca[len - 1]) {
    case 's':
      result = speca_is_s(str, state, arg_list);
      break;
    case 'c':
      result = speca_is_c(str, state, arg_list);
      break;
    case 'd':
      result = speca_is_d(str, state, arg_list);
      break;
    case 'i':
      result = speca_is_d(str, state, arg_list);
      break;
    case 'u':
      result = speca_is_d(str, state, arg_list);
      break;
    case 'f':
      result = speca_is_f(str, state, arg_list);
      break;
    default:
      result = 5;
      break;
  }
  return result;
}

int speca_is_s(char *str, state_of_speca *state,
               va_list *arg_list) {
  int result = 0;
  switch (state->longshort) {
    case 'l':
      handle_speca_ls(str, state, arg_list);
      break;
    case 0:
      char *stroka = va_arg(*arg_list, char *);
      handle_speca_s(str, state, stroka);
      break;
    default:
      break;
  }
  return result;
}

int handle_speca_s(char *str, state_of_speca *state, char *stroka) {
  int result = 0;
  int len = (int)s21_strlen(stroka);
  int sym_to_add = state->is_precision ? (state->precision < len ? state->precision : len) : len;
  int spaces_to_add = 0;
  if (state->is_width && state->width > sym_to_add) {
      spaces_to_add = state->width - sym_to_add;
  }

  if (!state->minus && spaces_to_add > 0) {
      for (int i = 0; i < spaces_to_add; i++) {
          s21_strncat(str, " ", 1);
      }
  }

  s21_strncat(str, stroka, sym_to_add);

  if (state->minus && spaces_to_add > 0) {
      for (int i = 0; i < spaces_to_add; i++) {
          s21_strncat(str, " ", 1);
      }
  }

  return result;
}
/*int handle_speca_s(char *str, state_of_speca *state,
                   char *stroka) {
  int result = 0;

  int len = (int)s21_strlen(stroka);
  if (!state->minus && state->is_width)
    for (int i = 0; i < state->width - (len - state->precision); i++)
      s21_strncat(str, " ", 1);
  state->is_precision ? s21_strncat(str, stroka, state->precision)
                      : s21_strncat(str, stroka, len);
  if (state->minus && state->is_width)
    for (int i = 0; i < state->width - (len - state->precision); i++)
      s21_strncat(str, " ", 1);
  return result;
}*/

/*************************************************************/
int handle_speca_ls(char *str, state_of_speca *state,
                    va_list *arg_list) {
  int result = 0;
  wchar_t *wstroka = va_arg(*arg_list, wchar_t *);

  // Определяем размер буфера для многобайтовой строки
  s21_size_t bufferSize = wcstombs(S21_NULL, wstroka, 0) + 1;
  char *mnogobyte_str = (char *)malloc(bufferSize - state->precision);
  if (!mnogobyte_str) return 1;  // Ошибка выделения памяти

  // Преобразуем широкую строку в многобайтовую
  const wchar_t *src = wstroka;
  mbstate_t ps = {0};
  s21_size_t transformation = wcsrtombs(mnogobyte_str, &src, bufferSize - 1- state->precision, &ps);

  // Если преобразование не удалось, освобождаем память и возвращаем ошибку
  if (transformation == (s21_size_t)-1) {
    free(mnogobyte_str);
    return 1;
  }

  // Обрезаем строку по precision (в символах, а не в байтах)
  
  if (state->precision > 0 && state->precision < (int)wcslen(wstroka)) {
    wchar_t *wstr_cut =
        (wchar_t *)malloc((state->precision + 1) * sizeof(wchar_t));
    if (!wstr_cut) {
      free(mnogobyte_str);
      return 1;  // Ошибка выделения памяти
    }
    wcsncpy(wstr_cut, wstroka, state->precision);
    wstr_cut[state->precision] = L'\0';

    // Преобразуем обрезанную строку в многобайтовую
    transformation = wcstombs(mnogobyte_str, wstr_cut, bufferSize - 1- state->precision);
    free(wstr_cut);
  }
  
 /*if (state->precision > 0 && state->precision < (int)wcslen(wstroka)) {
    wchar_t *wstr_cut =
        (wchar_t *)malloc((state->precision + 1) * sizeof(wchar_t));
    if (!wstr_cut) {
      free(mnogobyte_str);
      return 1;  // Ошибка выделения памяти
    }
    
    // Безопасное копирование и добавление завершающего символа
    wcsncpy(wstr_cut, wstroka, state->precision);
    wstr_cut[state->precision] = L'\0';
    
    // Преобразуем обрезанную строку в многобайтовую
    transformation = wcstombs(mnogobyte_str, wstr_cut, bufferSize - 1);
    
    // Проверка на ошибки преобразования
    if (transformation == (s21_size_t)-1) {
      free(wstr_cut);
      free(mnogobyte_str);
      return 1;  // Ошибка преобразования
    }
    
    free(wstr_cut);
}*/

  // Длина строки в символах (не в байтах)
  int char_len = (int)wcslen(wstroka);

  // Если precision задана, ограничиваем длину
  if (state->precision > 0 && state->precision < char_len) {
    char_len = state->precision;
  }

  // Если ширина задана и строка короче, добавляем пробелы
  if (state->is_width && state->width > char_len) {
    int num_spaces = state->width - char_len * 2 - 5;

    if (!state->minus) {
      // Выравнивание по правому краю: добавляем пробелы перед строкой
      for (int i = 0; i < num_spaces; i++) {
        s21_strncat(str, " ", 1);
      }
    }

    // Добавляем строку
    s21_strncat(str, mnogobyte_str, (int)s21_strlen(mnogobyte_str));

    if (state->minus) {
      // Выравнивание по левому краю: добавляем пробелы после строки
      for (int i = 0; i < num_spaces; i++) {
        s21_strncat(str, " ", 1);
      }
    }
  } else {
    // Если ширина не задана или строка уже занимает всю ширину, просто
    // добавляем строку
    s21_strncat(str, mnogobyte_str, (int)s21_strlen(mnogobyte_str));
  }

  free(mnogobyte_str);
  return result;
}
/***************************************************/
int speca_is_c(char *str, state_of_speca *state,
               va_list *arg_list) {
  int result = 0;
  switch (state->longshort) {
    case 'l':
      handle_speca_lc(str, state, arg_list);
      break;
    case 0:
      handle_speca_c(str, state, arg_list);
      break;
    default:
      break;
  }
  return result;
}

int handle_speca_c(char *str, state_of_speca *state,
                   va_list *arg_list) {
  int result = 0;
  char ch = (char)va_arg(*arg_list, int);
  if (!state->minus && state->is_width)
    for (int i = 1; i < state->width; i++) s21_strncat(str, " ", 1);
  s21_size_t len = s21_strlen(str);
  str[len] = ch;        // Добавляем символ в строку
  str[len + 1] = '\0';  // Завершаем строку
  if (state->minus && state->is_width)
    for (int i = 1; i < state->width; i++) s21_strncat(str, " ", 1);
  return result;
}

int handle_speca_lc(char *str, state_of_speca *state,
                    va_list *arg_list) {
  int result = 0;
  char buffch[MB_CUR_MAX];
  wchar_t wch = va_arg(*arg_list, wchar_t);

  // Преобразуем широкий символ в многобайтовый
  result = wctomb(buffch, wch);
  if (result <= 0) {
    return 1;  // Ошибка преобразования
  }

  // Длина символа в байтах
  int char_len = result;

  // Если ширина задана и символ короче, добавляем пробелы
  if (state->is_width && state->width > char_len) {
    int num_spaces = state->width - char_len;

    if (!state->minus) {
      // Выравнивание по правому краю: добавляем пробелы перед символом
      for (int i = 0; i < num_spaces; i++) {
        s21_strncat(str, " ", 1);
      }
    }

    // Добавляем символ
    buffch[char_len] = '\0';  // Добавляем нулевой терминатор
    s21_strncat(str, buffch, (int)s21_strlen(buffch));

    if (state->minus) {
      // Выравнивание по левому краю: добавляем пробелы после символа
      for (int i = 0; i < num_spaces; i++) {
        s21_strncat(str, " ", 1);
      }
    }
  } else {
    // Если ширина не задана или символ уже занимает всю ширину, просто
    // добавляем символ
    buffch[char_len] = '\0';  // Добавляем нулевой терминатор
    s21_strncat(str, buffch, (int)s21_strlen(buffch));
  }

  return 0;  // Успешное выполнение
}
int speca_is_d(char *str, state_of_speca *state,
               va_list *arg_list) {
  int result = 0;
  char *strnbr = S21_NULL;
  char *str_for_print = S21_NULL;

  switch (state->longshort) {
    case 'l': {
      if (state->specificator == 'u') {
        unsigned long lngnbr = va_arg(*arg_list, unsigned long);
        strnbr =
            my_itoa((unsigned long)lngnbr, 'u');  // Обработка unsigned long
      } else {
        long lngnbr = va_arg(*arg_list, long);
        strnbr = my_itoa((long)lngnbr, 'l');  // Обработка long
      }
      break;
    }
    case 'h': {
      if (state->specificator == 'u') {
        unsigned short shrtnbr =
            (unsigned short)va_arg(*arg_list, unsigned int);
        strnbr =
            my_itoa((unsigned short)shrtnbr, 'u');  // Обработка unsigned short
      } else {
        int makeshort = (int)va_arg(*arg_list, int);
        int shrtnbr = handle_overflow(makeshort);
        strnbr = my_itoa((int)shrtnbr, 'h');  // Обработка short
      }
      break;
    }
    case 0: {
      if (state->specificator == 'u') {
        unsigned int nbr = va_arg(*arg_list, unsigned int);
        strnbr = my_itoa((unsigned int)nbr, 'u');  // Обработка unsigned int
      } else {
        int nbr = va_arg(*arg_list, int);
        strnbr = my_itoa(nbr, 'i');  // Обработка int
      }
      break;
    }
    default:
      result = 5;
      break;
  }

  if (strnbr) {
    str_for_print = handle_flags_d(state, strnbr);
    s21_strncat(str, str_for_print, (int)s21_strlen(str_for_print));
    free(strnbr);
    free(str_for_print);
  }
  return result;
}

char *my_itoa(long n, char int_type) {
  unsigned long un = (unsigned long)n;  // Для беззнаковых чисел
  int is_negative = 0;

  // Обработка знаковых чисел
  if (int_type != 'u' && n < 0) {
    is_negative = 1;
    n = -n;
  }

  // Обработка беззнаковых чисел
  if (int_type == 'u') {
    is_negative = 0;  // Беззнаковые числа всегда положительные
    un = (unsigned long)n;
  }

  int length = is_negative ? 2 : 1;
  long temp = (int_type == 'u') ? (long)un : n;
  while (temp /= 10) {length++;}
  length++;

  char *str = (char *)malloc(length * sizeof(char));
  if (!str) return S21_NULL;

  str[--length] = '\0';
  do {
    str[--length] = ((int_type == 'u') ? (long)(un % 10) : (n % 10)) + '0';
    if (int_type == 'u')
      un /= 10;
    else
      n /= 10;
  } while ((int_type == 'u') ? un > 0 : n > 0);

  if (is_negative) str[0] = '-';

  return str;
}

char *handle_flags_d(state_of_speca *state, char *strnbr) {
  int len = s21_strlen(strnbr);
  int result_len = len;
  char *work_strnbr = strnbr;

  // Если число равно 0 и precision == 0, обнуляем строку
  if (s21_strncmp(work_strnbr, "0", 1) == 0 && state->precision == 0 &&
      state->is_precision) {
    work_strnbr[0] = '\0';
    len = 0;
  }

  // Учитываем знак (+ или -)
  if (state->plus && work_strnbr[0] != '-' && state->specificator != 'u')
    result_len++;  // Добавляем место для знака '+'

  // Учитываем пробел, если требуется
  if (state->space && work_strnbr[0] != '-' && !state->plus &&
      state->specificator != 'u')
    result_len++;

  // Учитываем точность (добавляем нули, если precision > len)
  if (state->precision > len) result_len += (state->precision - len);

  // Учитываем ширину (добавляем пробелы, если width > result_len)
  if (state->width > result_len) result_len = state->width;

  // Выделяем память для результирующей строки
  char *result = (char *)malloc((result_len) * sizeof(char));
  if (!result) return S21_NULL;
  result[result_len] = '\0';

  // Заполняем строку пробелами (по умолчанию)
  s21_memset(result, ' ', result_len);

  // Позиция, с которой начинаем заполнять число
  int start_pos = 0;
  if (state->minus) {
    // Выравнивание по левому краю
    start_pos = 0;
  } else {
    // Выравнивание по правому краю
    start_pos = result_len - (state->precision > len ? state->precision : len);
    if (state->plus && work_strnbr[0] != '-' && state->specificator != 'u') {
      start_pos--;  // Учитываем знак '+'
    } else if (state->space && work_strnbr[0] != '-' && !state->plus &&
               state->specificator != 'u') {
      start_pos--;  // Учитываем пробел
    }
  }

  // Добавляем знак '+' или '-'
  if (state->plus && work_strnbr[0] != '-' && state->specificator != 'u') {
    result[start_pos] = '+';
    start_pos++;
  } else if (work_strnbr[0] == '-') {
    result[start_pos] = '-';
    start_pos++;
    work_strnbr += 1;  // Пропускаем знак '-' в исходной строке
    len -= 1;
  } else if (state->space && work_strnbr[0] != '-' && !state->plus &&
             state->specificator != 'u') {
    result[start_pos] = ' ';
    start_pos++;
  }

  // Добавляем нули для точности
  if (state->precision > len) {
    int zeros_to_add = state->precision - len;
    s21_memset(result + start_pos, '0', zeros_to_add);
    start_pos += zeros_to_add;
  }

  // Копируем число в результирующую строку
  s21_memcpy(result + start_pos, work_strnbr, len);

  return result;
}

short int handle_overflow(int x) {
  short int result = (short int)(x % 65536);
  if (result < 0) {
    result += 65536; // Преобразуем негативные значения в положительные
  }
  return result;
}

int speca_is_f(char *str, state_of_speca *state,
               va_list *arg_list) {
  int result = 0;
  char *str_for_print = S21_NULL;
  double fltnbr = (double)va_arg(*arg_list, double);
  if (state->is_precision == 0) state->precision = 6;
  char *strnbr = float_to_string(fltnbr, state->precision, state->is_precision);
  if (strnbr) {
    str_for_print = handle_flags_f(state, strnbr);
    s21_strncat(str, str_for_print, (int)s21_strlen(str_for_print));
    free(strnbr);
    free(str_for_print);
  }
  return result;
}

char *float_to_string(double number, int precision, int is_precision) {
  // Определяем размер буфера для строки
  int buffer_size = 50;  // Достаточно для большинства случаев
  char *result = malloc(buffer_size * sizeof(char));
  if (!result) return S21_NULL;

  // Форматируем число с плавающей точкой в строку
  if (is_precision) {
    snprintf(result, buffer_size, "%.*f", precision, number);
  } else {
    snprintf(result, buffer_size, "%f", number);
  }

  return result;
}

char *handle_flags_f(state_of_speca *state, char *strnbr) {
  int len = s21_strlen(strnbr);
  int result_len = len;
  char *work_strnbr = strnbr;

  // Учитываем знак (+ или -)
  if (state->plus && work_strnbr[0] != '-') {
    result_len++;  // Добавляем место для знака '+'
  }

  // Учитываем пробел, если требуется
  if (state->space && work_strnbr[0] != '-' && !state->plus) {
    result_len++;
  }

  // Учитываем ширину (добавляем пробелы, если width > result_len)
  if (state->width > result_len) {
    result_len = state->width;
  }

  // Выделяем память для результирующей строки
  char *result = (char *)malloc((result_len + 1) * sizeof(char));
  if (!result) return S21_NULL;
  result[result_len] = '\0';

  // Заполняем строку пробелами (по умолчанию)
  s21_memset(result, ' ', result_len);

  // Позиция, с которой начинаем заполнять число
  int start_pos = 0;
  if (state->minus) {
    // Выравнивание по левому краю
    start_pos = 0;
  } else {
    // Выравнивание по правому краю
    start_pos = result_len - len;
    if (state->plus && work_strnbr[0] != '-') {
      start_pos--;  // Учитываем знак '+'
    } else if (state->space && work_strnbr[0] != '-' && !state->plus) {
      start_pos--;  // Учитываем пробел
    }
  }

  // Добавляем знак '+' или '-'
  if (state->plus && work_strnbr[0] != '-') {
    result[start_pos] = '+';
    start_pos++;
  } else if (work_strnbr[0] == '-') {
    result[start_pos] = '-';
    start_pos++;
    work_strnbr += 1;  // Пропускаем знак '-' в исходной строке
    len -= 1;
  } else if (state->space && work_strnbr[0] != '-' && !state->plus) {
    result[start_pos] = ' ';
    start_pos++;
  }

  // Копируем число в результирующую строку
  s21_memcpy(result + start_pos, work_strnbr, len);

  return result;
}