#include "s21_string.h"

// перевод строки в число, эта функция идёт по символам '1', '0' и тд. и
// собирает из них число. логика: берём текущий результат, умножаем на 10,
// прибавляем новую цифру
const char* get_number(const char* format, int* number) {
  *number = 0;
  while (*format >= '0' && *format <= '9') {
    *number = *number * 10 + (*format - '0');
    format++;
  }
  return format;
}

// Вспомогательная функция для флагов "-" и "+"
void apply_width(char** str, char* value_start, char* value_end, opt_t f) {
  int value_len = (int)(value_end - value_start);
  if (f.width > value_len) {
    int padding = f.width - value_len;
    if (f.minus) {
      // флаг '-' - значение слева, пробелы справа
      for (int i = 0; i < padding; i++) {
        *(*str)++ = ' ';
      }
    } else {
      // сдвигаем значение вправо
      for (int i = value_len - 1; i >= 0; i--) {
        value_start[i + padding] = value_start[i];
      }
      // добавляем пробелы слева
      for (int i = 0; i < padding; i++) {
        value_start[i] = ' ';
      }
      *str += padding;
    }
  }
}

// (Cythiada)

// разбирает всё между '%' и спецификатором, результат в opt_t
const char* parse_options(const char* format, opt_t* f, va_list args) {
  // флаги
  while (*format == '-' || *format == '+' || *format == ' ') {
    if (*format == '-') f->minus = 1;
    if (*format == '+') f->plus = 1;
    if (*format == ' ') f->space = 1;
    format++;
  }

  // ширина - число или '*' (тогда из va_arg)
  if (*format >= '0' && *format <= '9') {
    format = get_number(format, &(f->width));
  } else if (*format == '*') {
    f->width = va_arg(args, int);
    format++;
  }

  // точность - после '.'
  if (*format == '.') {
    f->is_precision = 1;
    format++;
    if (*format >= '0' && *format <= '9') {
      format = get_number(format, &(f->precision));
    } else if (*format == '*') {
      f->precision = va_arg(args, int);
      format++;
    }
  }

  // h / l
  if (*format == 'h' || *format == 'l') {
    f->length = *format;
    format++;
  }
  f->specifier = *format;
  return format;
}

char* s21_itoa(long long n, char* s) {
  char buffer[64];
  int i = 0;
  unsigned long long num = (n < 0) ? (unsigned long long)-(unsigned long long)n
                                   : (unsigned long long)n;
  if (num == 0) buffer[i++] = '0';
  while (num > 0) {
    buffer[i++] = (num % 10) + '0';
    num /= 10;
  }

  while (i > 0) *s++ = buffer[--i];
  *s = '\0';
  return s;
}

static char* apply_width_common(char* str, const char* tmp, int len, opt_t f) {
  int pad = f.width - len;
  if (pad > 0 && !f.minus)
    for (int i = 0; i < pad; i++) *str++ = ' ';
  for (int i = 0; i < len; i++) *str++ = tmp[i];
  if (pad > 0 && f.minus)
    for (int i = 0; i < pad; i++) *str++ = ' ';
  return str;
}

// обработка значений

char* process_value(char* str, opt_t f, va_list args) {
  // Обработка целых чисел %d (Oswycane)
  if (f.specifier == 'd' || f.specifier == 'i') {
    long long val = (f.length == 'l')   ? va_arg(args, long)
                    : (f.length == 'h') ? (short)va_arg(args, int)
                                        : va_arg(args, int);
    unsigned long long abs_val =
        (val < 0) ? (unsigned long long)(-val) : (unsigned long long)val;
    char buf[512] = {0}, num_str[64] = {0};
    int tp = 0;
    if (val < 0)
      buf[tp++] = '-';
    else if (f.plus)
      buf[tp++] = '+';
    else if (f.space)
      buf[tp++] = ' ';
    s21_itoa(abs_val, num_str);
    int num_len = 0;
    while (num_str[num_len]) num_len++;
    if (f.is_precision) {
      if (f.precision == 0 && val == 0) num_len = 0;
      int zeros = f.precision - num_len;
      for (int i = 0; i < zeros; i++) buf[tp++] = '0';
    }
    for (int i = 0; i < num_len; i++) buf[tp++] = num_str[i];
    buf[tp] = '\0';
    int total_len = tp;
    int pad_len = f.width - total_len;
    if (pad_len > 0 && !f.minus)
      for (int i = 0; i < pad_len; i++) *str++ = ' ';
    for (int i = 0; i < total_len; i++) *str++ = buf[i];
    if (pad_len > 0 && f.minus)
      for (int i = 0; i < pad_len; i++) *str++ = ' ';
  }

  // Обработка дробных чисел %f (Cythiada)
  else if (f.specifier == 'f') {
    char* value_start = str;
    double val = va_arg(args, double);
    if (!f.is_precision) f.precision = 6;  // стандартная точность

    if (val < 0) {
      *str++ = '-';
      val = -val;
    } else if (f.plus) {
      *str++ = '+';
    } else if (f.space) {
      *str++ = ' ';
    }  // флаг пробел

    // прибавляем 0.5 к последнему знаку
    double round_val = 0.5;
    for (int i = 0; i < f.precision; i++) round_val /= 10.0;
    val += round_val;

    long long ipart = (long long)val;
    str = s21_itoa(ipart, str);  // записываем целую часть

    if (f.precision > 0) {
      *str++ = '.';
      double fpart = val - (double)ipart;
      for (int i = 0; i < f.precision; i++) {
        fpart *= 10;
        int digit = (int)fpart;
        *str++ = digit + '0';
        fpart -= digit;
      }
    }
    apply_width(&str, value_start, str, f);
  }

  // Обработка строк %s (Brendado)
  else if (f.specifier == 's') {
    char* s = va_arg(args, char*);
    if (!s) s = "(null)";

    // считаем длину строки
    int len = 0;
    while (s[len]) len++;

    // если длиннее заданной точности — берём столько символов сколько указано в
    // точности

    if (f.is_precision && f.precision < len) len = f.precision;

    // копируем строку (не больше len символов)
    for (int k = 0; k < len; k++) *str++ = s[k];
  }
  // Обработка символов %c (Julenema)
  else if (f.specifier == 'c') {
    char* value_start = str;
    char c = (char)va_arg(args, int);
    *str++ = c;
    apply_width(&str, value_start, str, f);
  }
  // Обработка беззнаковых чисел %u (Sabelshi)
  else if (f.specifier == 'u') {
    char* value_start = str;
    unsigned long long val = (f.length == 'l') ? va_arg(args, unsigned long)
                             : (f.length == 'h')
                                 ? (unsigned short)va_arg(args, int)
                                 : va_arg(args, unsigned int);
    str = s21_itoa(val, str);
    apply_width(&str, value_start, str, f);
  }
  // Обработка самого знака процента %%
  else if (f.specifier == '%') {
    char* value_start = str;
    *str++ = '%';
    apply_width(&str, value_start, str, f);
  }
  return str;
}

int s21_sprintf(char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);
  char* start_ptr = str;
  while (*format) {
    if (*format == '%') {
      format++;
      opt_t f = {0};
      format = parse_options(format, &f, args);
      char tmp[1024] = {0};
      char* end = process_value(tmp, f, args);
      int len = (int)(end - tmp);
      str = apply_width_common(str, tmp, len, f);
    } else {
      *str++ = *format;
    }
    format++;
  }
  *str = '\0';
  va_end(args);
  return (int)(str - start_ptr);
}