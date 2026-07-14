#include "s21_string.h"

// Выполняет поиск первого вхождения символа c (беззнаковый тип)
// в первых n байтах строки, на которую указывает аргумент str.
void* s21_memchr(const void* str, int c, s21_size_t n) {
  // c беззнаковый тип, тогда почему int
  // видимо нужно приводить к unsigned

  const unsigned char* u_str = (const unsigned char*)str;
  unsigned char u_c = (unsigned char)c;

  for (s21_size_t i = 0; i < n; i++) {
    if (u_str[i] == u_c) {
      return (void*)(u_str + i);
    }
  }

  return S21_NULL;
}

// Сравнивает первые n байтов str1 и str2.
// Функция сравнивает байты (unsigned char)
// < 0: Первый отличающийся байт в str1 меньше, чем в str2.
// 0: Все n байтов в обоих блоках памяти равны.
// > 0: Первый отличающийся байт в str1 больше, чем в str2.
int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  const unsigned char* u_str1 = (const unsigned char*)str1;
  const unsigned char* u_str2 = (const unsigned char*)str2;

  if (n == 0) {
    return 0;
  }

  for (s21_size_t i = 0; i < n; i++) {
    if (u_str1[i] != u_str2[i]) {
      return u_str1[i] - u_str2[i];
    }
  }

  return 0;
}

// Копирует n символов из src в dest.
void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
  char* u_dest = (char*)dest;
  const char* u_src = (const char*)src;

  for (s21_size_t i = 0; i < n; i++) {
    u_dest[i] = u_src[i];
  }

  return dest;
}

// Копирует символ c (беззнаковый тип) в первые n
// символов строки, на которую указывает аргумент str.
void* s21_memset(void* str, int c, s21_size_t n) {
  unsigned char u_c = (unsigned char)c;
  unsigned char* u_str = (unsigned char*)str;

  for (s21_size_t i = 0; i < n; i++) {
    u_str[i] = u_c;
  }

  return u_str;
}

// длина начального сегмента str1, который не содержит ни одного символа str2
s21_size_t s21_strcspn(const char* str1, const char* str2) {
  s21_size_t count = 0;
  while (str1[count] != '\0') {
    for (s21_size_t i = 0; str2[i] != '\0'; i++) {
      if (str1[count] == str2[i]) return count;
    }
    count++;
  }
  return count;
}

// первое вхождение подстроки needle в строке haystack
// возвращает указатель на начало вхождения, в ином случае null
char* s21_strstr(const char* haystack, const char* needle) {
  if (*needle == '\0') return (char*)haystack;
  while (*haystack != '\0') {
    const char* h = haystack;
    const char* n = needle;
    while (*h != '\0' && *n != '\0' && *h == *n) {
      h++;
      n++;
    }
    if (*n == '\0') return (char*)haystack;
    haystack++;
  }
  return S21_NULL;
}

// это вспомогательная функция тоже стринга, которой нет по заданию
//  возвращает длину начального сегмента str состоящего только из delim
static s21_size_t strspn_helper(const char* str, const char* delim) {
  s21_size_t count = 0;
  while (str[count] != '\0') {
    int found = 0;
    for (s21_size_t i = 0; delim[i] != '\0'; i++) {
      if (str[count] == delim[i]) {
        found = 1;
        break;
      }
    }
    if (!found) break;
    count++;
  }
  return count;
}

// разбивает строку на токены по delim (разделители).   Первый вызов - str,
// далее Null
char* s21_strtok(char* str, const char* delim) {
  static char* saved = S21_NULL;
  if (str != S21_NULL) saved = str;
  if (saved == S21_NULL || *saved == '\0') return S21_NULL;

  saved += strspn_helper(saved, delim);
  if (*saved == '\0') {
    saved = S21_NULL;
    return S21_NULL;
  }

  char* token = saved;
  saved += s21_strcspn(saved, delim);

  if (*saved != '\0') {
    *saved = '\0';
    saved++;
  } else
    saved = S21_NULL;

  return token;
}

// Находит первое вхождение символа c в строке str, включая нуль
char* s21_strchr(const char* str, int c) {
  char* res = S21_NULL;
  while (*str != '\0') {
    if (*str == (char)c) {
      res = (char*)str;
      break;
    }
    str++;
  }
  if (res == S21_NULL && (char)c == '\0') res = (char*)str;
  return res;
}

// Находит последнее вхождение символа c в строке str, включая нуль
char* s21_strrchr(const char* str, int c) {
  char* res = S21_NULL;
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == (char)c) res = (char*)str + i;
    i++;
  }
  if (res == S21_NULL && (char)c == '\0') res = (char*)str + i;
  return res;
}

// Сравнивает не более n байтов строк str1 и str2 по значению ASCII
int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  int res = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
      res = (unsigned char)str1[i] - (unsigned char)str2[i];
      break;
    }
  }
  return res;
}

// Находит первый символ в str1, который соответствует любому символу из str2
char* s21_strpbrk(const char* str1, const char* str2) {
  char* res = S21_NULL;
  while (*str1 != '\0') {
    if (s21_strchr(str2, *str1)) {
      res = (char*)str1;
      break;
    }
    str1++;
  }
  return res;
}

// strlen - Вычисляет длину строки str, не включая завершающий нулевой символ
s21_size_t s21_strlen(const char* str) {
  s21_size_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

// strncpy - Копирует до n символов из строки, на которую указывает src, в dest.
char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  s21_size_t i = 0;
  while (i < n && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  while (i < n) {
    dest[i] = '\0';
    i++;
  }
  return dest;
}

// strcat - Добавляет строку, на которую указывает src, в конец строки, на
// которую указывает dest, длиной до n символов.
char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  char* d = dest;
  while (*d != '\0') {  // идём до конца dest
    d++;
  }
  s21_size_t i = 0;
  while (i < n && src[i] != '\0') {
    d[i] = src[i];
    i++;
  }
  d[i] = '\0';
  return dest;
}

// strerror - Выполняет поиск во внутреннем массиве номера ошибки errnum и
// возвращает указатель на строку с сообщением об ошибке. Нужно объявить
// макросы, содержащие массивы сообщений об ошибке для операционных систем mac и
// linux. Описания ошибок есть в оригинальной библиотеке. Проверка текущей ОС
// осуществляется с помощью директив.
char* s21_strerror(int errnum) {
  static const char* errlist[] = S21_ERRLIST;
  static char unknown_err[64];
  int list_size = S21_ERRLIST_SIZE;

  if (errnum >= 0 && errnum < list_size) {  // если номер известный
    int i = 0;
    while (errlist[errnum][i] != '\0') {
      unknown_err[i] = errlist[errnum][i];
      i++;
    }
    unknown_err[i] = '\0';
  } else {  // если номер неизвестный
    s21_sprintf(unknown_err, "Unknown error: %d", errnum);
  }

  return unknown_err;
}