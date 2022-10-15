#include <math.h>

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  int n = 0;
  va_list ap;
  va_start(ap, format);
  struct forms p;
  int final_size = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    str[i] = '\0';
    if (i >= 100) {
      break;
    }
  }
  while (*format) {
    int shift = 0, len = 0;
    init(&p);
    if (*format != '%') {
      *str++ = *format++;
      n++;
      final_size++;
    } else if (*(format + 1) == 'n') {
      *va_arg(ap, int *) = n;
      format += 2;
    } else if (*++format == '%') {
      *str++ = '%';
      n++;
      final_size++;
      format++;
    } else {
      len = parse(&p, format, ap);
    }
    if (p.type != '\0') {
      shift = check_type(&p, str, ap, &shift);
      str += shift;
      final_size += shift;
      n += shift;
    }
    format += len;
  }
  va_end(ap);
  return final_size;
}

int check_type(struct forms *p, char *str, va_list ap, int *shift) {
  if (p->type == 'd' || p->type == 'i') {
    *shift = d_to_string(p, str, ap);
  }
  if (p->type == 'f') {
    *shift = f_to_string(p, str, ap);
  }
  if (p->type == 's') {
    *shift = s_to_string(p, str, ap);
  }
  if (p->type == 'c') {
    *shift = c_to_string(p, str, ap);
  }
  if (p->type == 'u' || p->type == 'o' || p->type == 'x' || p->type == 'X') {
    *shift = u_to_string(p, str, ap);
  }
  if (p->type == 'g' || p->type == 'G') {
    *shift = g_to_string(p, str, ap);
  }
  if (p->type == 'e' || p->type == 'E') {
    *shift = e_to_string(p, str, ap);
  }
  if (p->type == 'p') {
    *shift = p_to_string(str, ap, p);
  }
  return *shift;
}

int p_to_string(char *str, va_list ap, struct forms *p) {
  int len = 0, zeros = 0;
  char zero_and_x[510] = {'\0'};
  void *ptr = va_arg(ap, void *);
  unsigned long num = (unsigned long)ptr;
  char buffer[510];
  s21_xtoa(num, buffer, p);
  zero_and_x[0] = '0';
  zero_and_x[1] = 'x';
  s21_strcat(zero_and_x, buffer);
  len = s21_strlen(zero_and_x);
  if (p->precission > len) {
    zeros = 1;
    add_spaces_or_zeros_left(p, zero_and_x, zeros);
    zeros = 0;
  }
  if (len < p->width && p->minus != 1) {
    add_spaces_or_zeros_left(p, zero_and_x, zeros);
  } else if (len < p->width && p->minus == 1) {
    add_spaces_or_zeros_right(p, zero_and_x, zeros);
  }
  s21_strcat(str, zero_and_x);
  len = s21_strlen(zero_and_x);
  return len;
}

int e_to_string(struct forms *p, char *str, va_list ap) {
  int len = 0, zeros = 0;
  double num = 0;
  num = va_arg(ap, double);
  if (p->lenght == -2) {
    num = (long double)num;
  }
  char buffer[510] = {'\0'}, sign[2] = {'\0'};
  if (num < 0) {
    sign[0] = '-';
  } else if (p->plus == 1) {
    sign[0] = '+';
  } else if (p->space == 1) {
    sign[0] = ' ';
  }
  if (p->precission == 0) {
    num = round(num);
    s21_itoa(num, buffer);
  } else {
    s21_etoa(p, buffer, num);
  }
  s21_strcat(sign, buffer);
  len = s21_strlen(sign);
  if (len < p->width && p->minus != 1 && p->width > p->precission) {
    add_spaces_or_zeros_left(p, sign, zeros);
  } else if (len < p->width && p->minus == 1) {
    add_spaces_or_zeros_right(p, sign, zeros);
  }
  s21_strcat(str, sign);
  return s21_strlen(str);
}

int g_to_string(struct forms *p, char *str, va_list ap) {
  int len = 0, zeros = 0;
  char buffer[510] = {'\0'}, sign[510] = {'\0'};
  double num = 0;
  num = va_arg(ap, double);
  if (p->lenght == -2) {
    num = (long double)num;
  }

  if (num < 0) {
    sign[0] = '-';
    p->negative = 1;
  } else if (p->plus == 1) {
    sign[0] = '+';
    p->negative = -1;
  } else if (p->space == 1) {
    sign[0] = ' ';
  }
  s21_gtoa(p, buffer, num);
  len = s21_strlen(buffer);

  if (p->zero == 1) {
    if (len < p->width && p->minus != 1 && p->width > p->precission) {
      add_spaces_or_zeros_left(p, buffer, zeros);
    } else if (len < p->width && p->minus == 1) {
      add_spaces_or_zeros_right(p, buffer, zeros);
    }
    s21_strcat(sign, buffer);
    len = s21_strlen(sign);
  } else {
    s21_strcat(sign, buffer);
    len = s21_strlen(sign);
    if (len < p->width && p->minus != 1 && p->width > p->precission) {
      add_spaces_or_zeros_left(p, sign, zeros);
    } else if (len < p->width && p->minus == 1) {
      add_spaces_or_zeros_right(p, sign, zeros);
    }
  }
  s21_strcat(str, sign);
  return s21_strlen(str);
}

int u_to_string(struct forms *p, char *str, va_list ap) {
  unsigned long int num;
  int len = 0, zeros = 0;
  char buffer[510] = {'\0'}, grid[510] = {'\0'};
  if (p->lenght == -1) {
    num = va_arg(ap, unsigned long int);
  } else if (p->lenght == 1) {
    num = va_arg(ap, unsigned int);
    num = (unsigned short int)num;
  } else {
    num = va_arg(ap, unsigned int);
    num = (unsigned int)num;
  }
  if (p->type == 'u') {
    s21_itoa(num, buffer);
  } else if (p->type == 'o') {
    s21_otoa(num, buffer, p);
  } else if (p->type == 'x' || p->type == 'X') {
    s21_xtoa(num, buffer, p);
  }
  len = s21_strlen(buffer);
  if (p->precission > len) {
    zeros = 1;
    add_spaces_or_zeros_left(p, buffer, zeros);
    zeros = 0;
  }
  if (p->grid == 1 && p->type == 'x' && p->precission != -1) {
    grid[0] = '0';
    grid[1] = 'x';
    s21_strcat(grid, buffer);
    buffer[0] = '\0';
    s21_strcat(buffer, grid);
  } else if (p->grid == 1 && p->type == 'X' && p->precission != -1) {
    grid[0] = '0';
    grid[1] = 'X';
    s21_strcat(grid, buffer);
    buffer[0] = '\0';
    s21_strcat(buffer, grid);
  }
  len = s21_strlen(buffer);
  if (len < p->width && p->minus != 1) {
    add_spaces_or_zeros_left(p, buffer, zeros);
  } else if (len < p->width && p->minus == 1) {
    add_spaces_or_zeros_right(p, buffer, zeros);
  }
  s21_strcat(str, buffer);
  return s21_strlen(str);
}

int c_to_string(struct forms *p, char *str, va_list ap) {
  int zeros = 0;
  char buffer[510] = {'\0'};
  if (p->lenght == -1) {
    wchar_t wch = va_arg(ap, wchar_t);
    buffer[0] = wch;
  } else {
    char ch = va_arg(ap, int);
    buffer[0] = ch;
  }
  if (p->width > 1 && p->minus != 1) {
    add_spaces_or_zeros_left(p, buffer, zeros);
  } else if (p->width > 1 && p->minus == 1) {
    add_spaces_or_zeros_right(p, buffer, zeros);
  }
  s21_strcat(str, buffer);
  return s21_strlen(str);
}

int s_to_string(struct forms *p, char *str, va_list ap) {
  char buffer[510] = {'\0'};
  int len = 0, zeros = 0;
  if (p->lenght == -1) {
    wchar_t *wch = va_arg(ap, wchar_t *);
    len = s21_wstrlen(wch);
    if (p->precission == -1) p->precission = len;
    s21_wstrncat(buffer, wch, p->precission);
  } else {
    char *arr = va_arg(ap, char *);
    s21_strcat(buffer, arr);
  }
  len = s21_strlen(buffer);
  if (p->precission == -2) p->precission = 0;
  if (p->precission != -1) {
    buffer[p->precission] = '\0';
  }
  if (p->precission > len) {
    add_spaces_or_zeros_left(p, buffer, zeros);
  }
  len = s21_strlen(buffer);
  if (p->width > len && p->minus == 0) {
    add_spaces_or_zeros_left(p, buffer, zeros);
  } else if (p->width > len && p->minus == 1) {
    add_spaces_or_zeros_right(p, buffer, zeros);
  }
  s21_strcat(str, buffer);
  len = s21_strlen(str);
  return len;
}

s21_size_t s21_wstrlen(const wchar_t *str) {
  s21_size_t len = 0;
  for (; str[len]; len++) {
  }
  return len;
}

char *s21_wstrncat(char *dest, const wchar_t *src, s21_size_t n) {
  int last = s21_strlen(dest);
  for (s21_size_t i = 0; i < n; i++) {
    dest[last] = src[i];
    last++;
  }
  dest[last] = '\0';
  return dest;
}

int f_to_string(struct forms *p, char *str, va_list ap) {
  int len = 0, zeros = 0;
  double num = 0;
  num = va_arg(ap, double);
  if (p->lenght == -2) {
    num = (long double)num;
  }
  char buffer[510] = {'\0'}, sign[510] = {'\0'};
  if (num < 0) {
    sign[0] = '-';
  } else if (p->plus == 1) {
    sign[0] = '+';
  } else if (p->space == 1) {
    sign[0] = ' ';
  }
  if (p->precission == 0) {
    num = round(num);
    s21_itoa(num, buffer);
  } else {
    s21_ftoa(p, buffer, num);
  }
  s21_strcat(sign, buffer);
  len = s21_strlen(sign);
  if (len < p->width && p->minus != 1 && p->width > p->precission) {
    add_spaces_or_zeros_left(p, sign, zeros);
  } else if (len < p->width && p->minus == 1) {
    add_spaces_or_zeros_right(p, sign, zeros);
  }
  s21_strcat(str, sign);
  return s21_strlen(str);
}

int d_to_string(struct forms *p, char *str, va_list ap) {
  long int num = 0;
  int len = 0, zeros = 0;
  char buffer[510] = {'\0'}, sign[510] = {'\0'};
  if (p->lenght == -1) {
    num = va_arg(ap, long int);
  } else if (p->lenght == 1) {
    num = va_arg(ap, int);
    num = (short int)num;
  } else {
    num = va_arg(ap, int);
    num = (int)num;
  }
  if (num < 0) {
    sign[0] = '-';
  } else if (p->plus == 1) {
    sign[0] = '+';
  } else if (p->space == 1) {
    sign[0] = ' ';
  }
  s21_itoa(num, buffer);
  len = s21_strlen(buffer);
  if (p->precission > len) {
    zeros = 1;
    add_spaces_or_zeros_left(p, buffer, zeros);
    zeros = 0;
  }
  s21_strcat(sign, buffer);
  len = s21_strlen(sign);
  if (len < p->width && p->minus != 1) {
    add_spaces_or_zeros_left(p, sign, zeros);
  } else if (len < p->width && p->minus == 1) {
    add_spaces_or_zeros_right(p, sign, zeros);
  }
  s21_strcat(str, sign);
  return s21_strlen(str);
}

void add_spaces_or_zeros_left(struct forms *p, char *buffer, int zeros) {
  char spaces[510] = {'\0'};
  int dif = 0, len = 0;
  if (p->zero == 1) {
    zeros = 1;
  }
  if (p->negative == 0) {
    len = s21_strlen(buffer);
    if (p->precission > len) {
      dif = p->precission - len;
    } else {
      dif = p->width - len;
    }
    if (zeros == 0) {
      for (int i = 0; i < dif; i++) {
        spaces[i] = ' ';
      }
    } else if (zeros == 1) {
      for (int i = 0; i < dif; i++) {
        spaces[i] = '0';
      }
    }
    s21_strcat(spaces, buffer);
    buffer[0] = '\0';
    s21_strcat(buffer, spaces);
  } else if (p->negative == 1 || p->negative == -1) {
    len = s21_strlen(buffer);
    if (p->precission > len && p->type != 'g') {
      dif = p->precission - len;
    } else {
      dif = p->width - len;
    }
    if (zeros == 0) {
      for (int i = 0; i < dif; i++) {
        spaces[i] = ' ';
      }
    } else if (zeros == 1) {
      for (int i = 0; i < dif - 1; i++) {
        spaces[i] = '0';
      }
    }
    s21_strcat(spaces, buffer);
    buffer[0] = '\0';
    s21_strcat(buffer, spaces);
  }
}

void add_spaces_or_zeros_right(struct forms *p, char *buffer, int zeros) {
  // char *spaces = calloc((p->width + p->precission), sizeof(char));
  char spaces[510] = {'\0'};
  int dif = 0;
  if (p->zero == 1) {
    zeros = 1;
  }
  if (p->precission > p->width || zeros == 1) {
    dif = p->precission - s21_strlen(buffer) + 1;
  } else {
    dif = p->width - s21_strlen(buffer);
  }
  if (zeros == 0) {
    for (int i = 0; i < dif; i++) {
      spaces[i] = ' ';
    }
  } else if (zeros == 1) {
    for (int i = 0; i < dif; i++) {
      spaces[i] = '0';
    }
  }
  s21_strcat(buffer, spaces);
}

int parse(struct forms *p, const char *format, va_list ap) {
  int len = 0, temp = 0;
  if (!p->minus || !p->plus || !p->space || !p->zero || !p->space) {
    temp = 0;
    temp = parse_flags(p, format);
    format += temp;
    len += temp;
  }
  if (!p->width) {
    temp = 0;
    temp = parse_width(p, format, ap);
    format += temp;
    len += temp;
  }
  if (p->precission == -1) {
    temp = 0;
    temp = parse_precission(p, format, ap);
    format += temp;
    len += temp;
  }
  if (!p->lenght) {
    temp = 0;
    temp = parse_lenght(p, format);
    format += temp;
    len += temp;
  }
  if (!p->type) {
    temp = 0;
    temp = parse_type(p, format);
    format += temp;
    len += temp;
  }
  return len;
}

int parse_precission(struct forms *p, const char *format, va_list ap) {
  int len = 0, num, temp_num;
  if (*format == '.' && (*(format + 1) <= '9' && *(format + 1) >= '0')) {
    len++;
    format++;
    while (*format >= '0' && *format <= '9') {
      if (*format >= '0' && *format <= '9') {
        num = *format - '0';
        format++;
        len++;
        if (*format >= '0' && *format <= '9') {
          temp_num = *format - '0';
          format++;
          len++;
          num *= 10;
          num += temp_num;
          p->precission = num;
        } else {
          p->precission = num;
        }
      } else {
        p->precission = 0;
      }
    }
  } else if (*format == '.' && *(format + 1) == '*') {
    p->precission = va_arg(ap, int);
    len += 2;
    format += 2;
  } else if (*format == '.') {
    p->precission = -2;
    format++;
    len++;
  }
  return len;
}

int parse_width(struct forms *p, const char *format, va_list ap) {
  int num = 0, temp_num, len = 0;
  if (*format >= '1' && *format <= '9') {
    num = *format++ - '0';
    len++;
    if (*format >= '0' && *format <= '9') {
      temp_num = *format - '0';
      num *= 10;
      num += temp_num;
      len++;
      p->width = num;
    } else {
      p->width = num;
    }
  } else if (*format == '*') {
    p->width = va_arg(ap, int);
    len++;
    format++;
  }
  return len;
}

int parse_flags(struct forms *p, const char *format) {
  int len = 0;
  while (*format == '#' || *format == '+' || *format == '-' || *format == '0' ||
         *format == ' ') {
    if (*format == '#') {
      p->grid = 1;
      len++;
      format++;
    }
    if (*format == '+') {
      p->plus = 1;
      len++;
      format++;
    }
    if (*format == '-') {
      p->minus = 1;
      len++;
      format++;
    }
    if (*format == '0') {
      p->zero = 1;
      len++;
      format++;
    }
    if (*format == ' ') {
      p->space = 1;
      len++;
      format++;
    }
  }
  return len;
}

int parse_lenght(struct forms *p, const char *format) {
  int len = 0;
  if (*format == 'h') {
    p->lenght = 1;
    len++;
  } else if (*format == 'l') {
    p->lenght = -1;
    len++;
  } else if (*format == 'L') {
    p->lenght = -2;
    len++;
  }
  return len;
}

int parse_type(struct forms *p, const char *format) {
  int len = 0;
  if (*format == 'd' || *format == 'i' || *format == 'u' || *format == 'o' ||
      *format == 'x' || *format == 'X' || *format == 'f' || *format == 'e' ||
      *format == 'E' || *format == 'g' || *format == 'G' || *format == 'c' ||
      *format == 's' || *format == 'p' || *format == 'n') {
    p->type = *format;
    len += 1;
  }
  return len;
}

void init(struct forms *p) {
  p->minus = 0;
  p->plus = 0;
  p->space = 0;
  p->zero = 0;
  p->grid = 0;
  p->width = 0;
  p->precission = -1;
  p->lenght = 0;
  p->negative = 0;
  p->type = '\0';
}

void s21_itoa(long int num, char *buffer) {
  if (num < 0) num = -num;
  long int place_holder = 0, num_holder = num;
  for (place_holder = 1; num_holder >= 10; num_holder /= 10) {
    place_holder *= 10;
  }
  for (; place_holder > 0; place_holder /= 10) {
    *buffer = num / place_holder + '0';
    num %= place_holder;
    buffer++;
  }
}

void s21_otoa(unsigned long int num, char *buffer, struct forms *p) {
  unsigned long int temp, i = 0, k = 0, len = 0;
  char temp_arr[510] = {'\0'}, grid[510] = {'\0'};
  temp = num;
  while (temp != 0) {
    temp_arr[i++] = temp % 8 + '0';
    temp /= 8;
  }
  if (p->grid == 1) {
    grid[0] = '0';
    s21_strcat(temp_arr, grid);
  }
  len = s21_strlen(temp_arr);
  for (int j = len - 1; j >= 0; j--) {
    buffer[k++] = temp_arr[j];
  }
  buffer[k] = '\0';
}

void s21_ftoa(struct forms *p, char *buffer, long double num) {
  if (num < 0) num = -num;
  int point_position = 10, a, b, decimal = 0, sign = 0, flag = 0, flag1 = 0;
  long double num_duble;
  char numbers[510] = {'\0'}, zeros_str[510] = {'\0'};
  if (p->precission == -1 || p->precission == -2) {
    if (p->precission == -2) flag = 1;
    flag1 = 2;
    p->precission = 6;
  }
  num_duble = num;
  s21_fcvt(num, p->precission, &decimal, &sign, numbers);
  if (num_duble < 1) {
    for (int j = 0; j < (-decimal + 1); j++) {
      zeros_str[j] = '0';
    }
    s21_strcat(zeros_str, numbers);
    numbers[0] = '\0';
    s21_strcat(numbers, zeros_str);
  }
  for (; point_position > 0; point_position--) {
    a = pow(10, point_position);
    b = num / a;
    if (b > 0) {
      break;
    }
  }
  s21_strcat(buffer, numbers);
  point_position++;
  long unsigned int n2 = 10, n3 = 1;
  double n1 = 9.9999999;
  while (n2 < 10000000000) {
    if ((num >= n1 && num < n2)) {
      point_position++;
      break;
    }
    n3 *= 10;
    n2 *= 10;
    n1 += 9 * n3;
  }
  char firstpart[510] = {'\0'};
  char secpart[510] = {'\0'};
  s21_strncpy(firstpart, buffer, point_position);
  int j = 0;
  for (int i = point_position; buffer[i] != '\0'; i++) {
    secpart[j] = buffer[i];
    j++;
  }
  if (flag != 1 || p->grid == 1) {
    firstpart[point_position] = '.';
  }
  if (flag == 0) {
    s21_strcat(firstpart, secpart);
    for (int i = 0; firstpart[i] != '\0'; i++) {
      buffer[i] = firstpart[i];
    }
  } else {
    buffer[0] = '\0';
    s21_strcat(buffer, firstpart);
  }
  if (flag == 1 || flag1 == 2) {
    p->precission = 0;
  }
}

void s21_gtoa(struct forms *p, char *buffer, long double num) {
  if (num < 0) num = -num;
  int point_position = 10, a, b, decimal = 0, sign = 0;
  long double holder_float_part = 0;
  double holder_int_part = 0;
  char numbers[510] = {'\0'}, zeros_str[510] = {'\0'};
  holder_float_part = modf(num, &holder_int_part);
  if (p->precission == -1) p->precission = 6;
  s21_fcvt(num, p->precission, &decimal, &sign, numbers);
  zeros_cutter(numbers, num, p);
  if (num < 1e-4 || num > 999999) check_for_e(num, numbers, decimal, p);
  if (num < 1 && num >= 0.0001) {
    for (int j = 0; j < (-decimal + 1); j++) {
      zeros_str[j] = '0';
    }
    s21_strcat(zeros_str, numbers);
    numbers[0] = '\0';
    s21_strcat(numbers, zeros_str);
  }
  for (; point_position > 0; point_position--) {
    a = pow(10, point_position);
    b = num / a;
    if (b > 0) {
      break;
    }
  }
  s21_strcat(buffer, numbers);
  point_position++;
  long unsigned int n2 = 10, n3 = 1;
  double n1 = 9.9999999;
  while (n2 < 10000000000) {
    if ((num >= n1 && num < n2)) {
      point_position++;
      break;
    }
    n3 *= 10;
    n2 *= 10;
    n1 += 9 * n3;
  }
  char firstpart[510] = {'\0'};
  char secpart[510] = {'\0'};
  s21_strncpy(firstpart, buffer, point_position);
  int j = 0;
  for (int i = point_position; buffer[i] != '\0'; i++) {
    secpart[j] = buffer[i];
    j++;
  }
  if ((num >= 0.0001 && holder_float_part != 0 && p->precission >= 6) ||
      p->grid == 1) {
    firstpart[point_position] = '.';
  }
  if (p->type == 'g') {
    firstpart[point_position] = '.';
  }
  if (p->type == 'G') {
    firstpart[point_position] = '.';
  }
  s21_strcat(firstpart, secpart);
  for (int i = 0; firstpart[i] != '\0'; i++) {
    buffer[i] = firstpart[i];
  }
  if (point_position >= 6 && p->grid == 0 &&
      (p->precission <= point_position)) {
    buffer[p->precission] = '\0';

  } else {
    buffer[p->precission + 1] = '\0';
  }
}

void zeros_cutter(char *buffer, int num, struct forms *p) {
  int len, dub_num = 0, j;
  len = s21_strlen(buffer);
  dub_num = num;
  if (num >= 10 && num <= 999999) {
    for (j = 0; dub_num >= 1; j += 1) dub_num /= 10;
  }
  if (p->precission != 6) j = p->precission;
  if (p->grid == 0) j = 6;
  if (p->type == 'g' && p->zero != 1 && p->grid != 1) j = 0;
  if (p->type == 'G' && p->zero != 1 && p->grid != 1) j = 0;
  for (int i = len - 1; i > j - 1; i--) {
    if (buffer[i] == '0') {
      buffer[i] = '\0';
    } else {
      break;
    }
  }
}

char *check_for_e_type(struct forms *p, double num, char *e_str) {
  if (p->type == 'g') {
    if (num < 999999) {
      if (num < 0.000000001) {
        e_str = "e-";
      } else {
        e_str = "e-0";
      }
    } else {
      if (num >= 1e+10) {
        e_str = "e+";
      } else {
        e_str = "e+0";
      }
    }
  } else if (p->type == 'G') {
    if (num < 999999) {
      if (num < 0.000000001) {
        e_str = "E-";
      } else {
        e_str = "E-0";
      }
    } else {
      if (num >= 1e+10) {
        e_str = "E+";
      } else {
        e_str = "E+0";
      }
    }
  }
  if (p->type == 'e') {
    if (num < 1) {
      if (num < 0.000000001) {
        e_str = "e-";
      } else {
        e_str = "e-0";
      }
    } else {
      if (num >= 1e+10) {
        e_str = "e+";
      } else {
        e_str = "e+0";
      }
    }
  } else if (p->type == 'E') {
    if (num < 1) {
      if (num < 0.000000001) {
        e_str = "E-";
      } else {
        e_str = "E-0";
      }
    } else {
      if (num >= 1e+10) {
        e_str = "E+";
      } else {
        e_str = "E+0";
      }
    }
  }
  return e_str;
}

void check_for_e(double num, char *numbers, int decimal, struct forms *p) {
  int e_int = 0, j;
  char *e_str = s21_NULL, abc[510] = {'\0'};
  e_str = check_for_e_type(p, num, e_str);
  if (num > 0 && num < 0.0001 && (p->type == 'g' || p->type == 'G')) {
    s21_strcat(numbers, e_str);
    e_int = -decimal + 1;
    s21_itoa(e_int, abc);
  }
  if (num > 999999 && (p->type == 'g' || p->type == 'G')) {
    for (j = 0; num >= 1; j += 1) num /= 10;
    s21_strcat(numbers, e_str);
    e_int = j - 1;
    s21_itoa(e_int, abc);
  }
  if (p->type == 'e' || p->type == 'E') {
    s21_strcat(numbers, e_str);
    e_int = -decimal + 1;
    s21_itoa(e_int, abc);
  }
  s21_strcat(numbers, abc);
}

void s21_etoa(struct forms *p, char *buffer, long double num) {
  if (num < 0) num = -num;
  int point_position = 1, decimal = 0, sign = 0, len = 0, zeros = 0, flag = 0,
      eenum = 0;
  char numbers[510] = {'\0'};
  if (p->precission == -1) {
    p->precission = 6;
    // flag = 2;
  } else if (p->precission == 0 || (p->precission == -2)) {
    p->precission = 1;
    flag = 1;
  }
  if (num <= 1e-6) {
    eenum = 1;
  }
  s21_ecvt(num, p->precission, &decimal, &sign, numbers, eenum);
  if (flag == 1) {
    p->precission = 0;
    // } else if (flag == 2) {
    //   p->precission = 6;
  }
  if (numbers[p->precission + 1] >= '5' && numbers[p->precission + 1] <= '9') {
    numbers[p->precission] = numbers[p->precission] + 1;
  }
  numbers[p->precission + 1] = '\0';
  len = s21_strlen(numbers);
  if (len <= p->precission) {
    zeros = 1;
    add_spaces_or_zeros_right(p, numbers, zeros);
  }
  check_for_e(num, numbers, decimal, p);
  s21_strcat(buffer, numbers);
  char firstpart[510] = {'\0'};
  char secpart[510] = {'\0'};
  s21_strncpy(firstpart, buffer, point_position);
  int j = 0;
  for (int i = point_position; buffer[i] != '\0'; i++) {
    secpart[j] = buffer[i];
    j++;
  }
  if (p->precission != 0 || p->grid != 0) {
    firstpart[point_position] = '.';
  }
  s21_strcat(firstpart, secpart);
  for (int i = 0; firstpart[i] != '\0'; i++) {
    buffer[i] = firstpart[i];
  }
  buffer[p->precission + 6] = '\0';
}

void s21_xtoa(unsigned long int num, char *buffer, struct forms *p) {
  long unsigned int temp, i = 0, k = 0, len = 0;
  char temp_arr[510] = {'\0'}, grid[510] = {'\0'};
  temp = num;
  while (temp != 0) {
    num = temp % 16;
    if (num < 10) {
      temp_arr[i++] = num + '0';
    } else {
      if (p->type == 'X') {
        temp_arr[i++] = num + 55;
      } else {
        temp_arr[i++] = num + 87;
      }
    }
    temp /= 16;
  }
  if (p->grid == 1 && p->type == 'x' && p->precission == -1) {
    grid[0] = 'x';
    grid[1] = '0';
    s21_strcat(temp_arr, grid);
  } else if (p->grid == 1 && p->type == 'X' && p->precission == -1) {
    grid[0] = 'X';
    grid[1] = '0';
    s21_strcat(temp_arr, grid);
  }
  len = s21_strlen(temp_arr);
  for (int j = len - 1; j >= 0; j--) {
    buffer[k++] = temp_arr[j];
  }
  buffer[k] = '\0';
}

static char *toa(double num, int ndigits, int *decpt, int *sign, char *temp,
                 int eflag) {
  int r2;
  double fi, fj;
  char *p, *p1;
  int size = 500;

  if (ndigits < 0) ndigits = 0;
  if (ndigits >= size - 1) ndigits = size - 2;
  r2 = 0;
  *sign = 0;
  p = &temp[0];
  if (num < 0) {
    *sign = 1;
    num = -num;
  }
  num = modf(num, &fi);

  if (fi != 0) {
    p1 = &temp[size];
    while (fi != 0) {
      fj = modf(fi / 10, &fi);
      *--p1 = (int)((fj + .03) * 10) + '0';
      r2++;
    }
    while (p1 < &temp[size]) *p++ = *p1++;
  } else if (num > 0) {
    while ((fj = num * 10) < 1) {
      num = fj;
      r2--;
    }
  }
  p1 = &temp[ndigits];
  if (eflag == 0) {
    p1 += r2;
  }
  *decpt = r2;
  if (p1 < &temp[0]) {
    temp[0] = '\0';
    return temp;
  }
  while (p <= p1 && p < &temp[size]) {
    num *= 10;
    num = modf(num, &fj);
    *p++ = (int)fj + '0';
  }
  if (p1 >= &temp[size]) {
    temp[size - 1] = '\0';
    return temp;
  }
  p = p1;
  *p1 += 5;
  if (ndigits >= 12) {
    char *p2;
    p2 = &temp[ndigits - 1];
    *--p2 += 5;
    if (*p2 <= '9') *p2 -= 5;
    while (*p1 > '9' || *p2 > '9') {
      *p1 = '0';
      if (p1 > temp) {
        ++*--p1;
      } else {
        *p1 = '1';
        (*decpt)++;
        if (eflag == 0) {
          if (p > temp) *p = '0';
          p++;
        }
      }
    }
    *p = '\0';
  } else {
    while (*p1 > '9') {
      *p1 = '0';
      if (p1 > temp) {
        ++*--p1;
      } else {
        *p1 = '1';
        (*decpt)++;
        if (eflag == 0) {
          if (p > temp) *p = '0';
          p++;
        }
      }
    }
    *p = '\0';
  }
  return temp;
}

char *s21_fcvt(double num, int ndigits, int *decpt, int *sign, char *buffer) {
  return toa(num, ndigits, decpt, sign, buffer, 0);
}

char *s21_ecvt(double num, int ndigits, int *decpt, int *sign, char *buffer,
               int eenum) {
  return toa(num, ndigits, decpt, sign, buffer, eenum);
}
