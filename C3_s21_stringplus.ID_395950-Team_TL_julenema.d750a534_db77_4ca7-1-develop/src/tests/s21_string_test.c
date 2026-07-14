#include "../s21_string.h"

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// нужен для работы функций, вывод которых проверяется по знаку
static int sign(int x) { return (x > 0) - (x < 0); }

#pragma region s21_memchr

// len - целиком. Символ - начало
START_TEST(test_s21_memchr_beginning) {
  const char str[] = "Simple!";

  void* expected = memchr(str, 'S', 7);
  void* actual = s21_memchr(str, 'S', 7);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// len - целиком. Символ - середина
START_TEST(test_s21_memchr_middle) {
  const char str[] = "Simple!";

  void* expected = memchr(str, 'p', 7);
  void* actual = s21_memchr(str, 'p', 7);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// len - целиком. Символ - конец
START_TEST(test_s21_memchr_end) {
  const char str[] = "Simple!";

  void* expected = memchr(str, '!', 7);
  void* actual = s21_memchr(str, '!', 7);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// символ не существует
START_TEST(test_s21_memchr_not_found) {
  const char str[] = "Simple!";

  void* expected = memchr(str, 'z', 7);
  void* actual = s21_memchr(str, 'z', 7);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// n = 0
START_TEST(test_s21_memchr_n_zero) {
  const char str[] = "Simple!";

  void* expected = memchr(str, 'S', 0);
  void* actual = s21_memchr(str, 'S', 0);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// n < позиции символа
START_TEST(test_s21_memchr_n_less_than_position) {
  const char str[] = "Simple!";

  void* expected = memchr(str, 'e', 3);
  void* actual = s21_memchr(str, 'e', 3);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// n >  позиции символа
START_TEST(test_s21_memchr_n_greater_than_position) {
  const char str[] = "Simple!";

  void* expected = memchr(str, 'S', 3);
  void* actual = s21_memchr(str, 'S', 3);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// крайний в начале
START_TEST(test_s21_memchr_n_equal_one) {
  const char str[] = "Simple!";

  void* expected = memchr(str, 'S', 1);
  void* actual = s21_memchr(str, 'S', 1);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// пустая строка
START_TEST(test_s21_memchr_empty_string) {
  const char empty[] = "";

  void* expected = memchr(empty, 'e', 1);
  void* actual = s21_memchr(empty, 'e', 1);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// символ \0
START_TEST(test_s21_memchr_null_character) {
  const char zero_str[] = "Simple!\0fff";

  void* expected = memchr(zero_str, '\0', 10);
  void* actual = s21_memchr(zero_str, '\0', 10);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// множественное вхождение
START_TEST(test_s21_memchr_multiple_occurrences) {
  const char multiple[] = "iLikeeePankaceeeeees_heeeelll_yeeeah!";

  void* expected = memchr(multiple, 'e', 37);
  void* actual = s21_memchr(multiple, 'e', 37);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// проверка с символами вне ASCII
START_TEST(test_s21_memchr_non_ascii) {
  const unsigned char no_ascii[] = {0x80, 0x82, 0x83, 0x84, 0x84};

  void* expected = memchr(no_ascii, 0x82, 5);
  void* actual = s21_memchr(no_ascii, 0x82, 5);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// проверка приведения int к unsigned char
START_TEST(test_s21_memchr_int_conversion_positive) {
  const char str[] = "Simple!";

  // ищем m - 109
  void* expected = memchr(str, 109, 7);
  void* actual = s21_memchr(str, 109, 7);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// отрицательный int
START_TEST(test_s21_memchr_int_conversion_negative) {
  const char str[] = "Simple!";

  void* expected = memchr(str, -109, 7);
  void* actual = s21_memchr(str, -109, 7);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// выход за пределы unsigned char
START_TEST(test_s21_memchr_int_conversion_overflow) {
  const char str[] = "Simple!";

  void* expected = memchr(str, 300, 7);
  void* actual = s21_memchr(str, 300, 7);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// проверка с очень длинной строкой
START_TEST(test_s21_memchr_large_string) {
  size_t len = 10000;
  char* long_str = (char*)malloc(len);
  for (size_t i = 0; i < len - 1; i++) {
    if (i % 2 == 0) {
      long_str[i] = 'a';
    } else {
      long_str[i] = 'b';
    }
  }
  long_str[len - 1] = '\0';

  void* expected = memchr(long_str, 'a', len);
  void* actual = s21_memchr(long_str, 'a', len);
  ck_assert_ptr_eq(expected, actual);

  free(long_str);
}
END_TEST

// бинарные данные
START_TEST(test_s21_memchr_binary_data) {
  unsigned char binary[] = {0x00, 0x01, 0xFF, 0x02};

  void* expected = memchr(binary, 0x01, 4);
  void* actual = s21_memchr(binary, 0x01, 4);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

// бинарные данные (не находит)
START_TEST(test_s21_memchr_binary_data_not_found) {
  unsigned char binary[] = {0x00, 0x01, 0xFF, 0x02};

  void* expected = memchr(binary, 0x03, 4);
  void* actual = s21_memchr(binary, 0x03, 4);
  ck_assert_ptr_eq(expected, actual);
}
END_TEST

#pragma endregion

#pragma region s21_memcmp

// n = 0
START_TEST(test_s21_memcmp_n_zero) {
  const char str1[] = "Simple";
  const char str2[] = "Bash";

  int expected = memcmp(str1, str2, 0);
  int actual = s21_memcmp(str1, str2, 0);
  ck_assert_int_eq(sign(expected), sign(actual));
}
END_TEST

// строки равны
START_TEST(test_s21_memcmp_equal_strings) {
  const char eq1[] = "Simple";
  const char eq2[] = "Simple";

  int expected = memcmp(eq1, eq2, 7);
  int actual = s21_memcmp(eq1, eq2, 7);
  ck_assert_int_eq(sign(expected), sign(actual));
}
END_TEST

// разные строки в середине
START_TEST(test_s21_memcmp_different_middle) {
  const char dif_mid1[] = "Simple";
  const char dif_mid2[] = "SimPle";

  int expected = memcmp(dif_mid1, dif_mid2, 7);
  int actual = s21_memcmp(dif_mid1, dif_mid2, 7);
  ck_assert_int_eq(sign(expected), sign(actual));
}
END_TEST

// выход на первой итерации
START_TEST(test_s21_memcmp_different_start) {
  const char first1[] = "Ximple";
  const char first2[] = "Simple";

  int expected = memcmp(first1, first2, 7);
  int actual = s21_memcmp(first1, first2, 7);
  ck_assert_int_eq(sign(expected), sign(actual));
}
END_TEST

// выход за пределы unsigned char
START_TEST(test_s21_memcmp_binary_data) {
  unsigned char data1[] = {0x00, 0xFF, 0x80, 0x7F};
  unsigned char data2[] = {0x00, 0xFF, 0x81, 0x7F};

  int expected = memcmp(data1, data2, 4);
  int actual = s21_memcmp(data1, data2, 4);
  ck_assert_int_eq(sign(expected), sign(actual));
}
END_TEST

// строки разного размера
START_TEST(test_s21_memcmp_different_size) {
  const char diff_size1[] = "SimpleBash";
  const char diff_size2[] = "Bash";

  int expected = memcmp(diff_size1, diff_size2, 4);
  int actual = s21_memcmp(diff_size1, diff_size2, 4);
  ck_assert_int_eq(sign(expected), sign(actual));
}
END_TEST

// строки очень большого размера
START_TEST(test_s21_memcmp_large_equal) {
  size_t large_size = 100000;
  char* large_str1 = (char*)malloc(large_size + 1);
  char* large_str2 = (char*)malloc(large_size + 1);

  for (size_t i = 0; i < large_size; i++) {
    large_str1[i] = 'a' + (i % 22);
    large_str2[i] = 'a' + (i % 22);
  }
  large_str1[large_size] = '\0';
  large_str2[large_size] = '\0';

  int expected = memcmp(large_str1, large_str2, large_size);
  int actual = s21_memcmp(large_str1, large_str2, large_size);
  ck_assert_int_eq(sign(expected), sign(actual));

  free(large_str1);
  free(large_str2);
}
END_TEST

// большие строки
START_TEST(test_s21_memcmp_large_different) {
  size_t large_size = 100000;
  char* large_str1 = (char*)malloc(large_size + 1);
  char* large_str2 = (char*)malloc(large_size + 1);

  for (size_t i = 0; i < large_size; i++) {
    large_str1[i] = 'a' + (i % 22);
    large_str2[i] = 'a' + (i % 22);
  }
  large_str1[large_size] = '\0';
  large_str2[large_size] = '\0';

  // изменяем один символ в середине
  large_str2[large_size / 2] = 'z';

  int expected = memcmp(large_str1, large_str2, large_size);
  int actual = s21_memcmp(large_str1, large_str2, large_size);
  ck_assert_int_eq(sign(expected), sign(actual));

  free(large_str1);
  free(large_str2);
}
END_TEST

// строки единичного размера
START_TEST(test_s21_memcmp_single_equal) {
  const char single1[] = "a";
  const char single2[] = "a";

  int expected = memcmp(single1, single2, 1);
  int actual = s21_memcmp(single1, single2, 1);
  ck_assert_int_eq(sign(expected), sign(actual));
}
END_TEST

// разные строки единичного размера
START_TEST(test_s21_memcmp_single_different) {
  const char single1[] = "a";
  const char single3[] = "d";

  int expected = memcmp(single1, single3, 1);
  int actual = s21_memcmp(single1, single3, 1);
  ck_assert_int_eq(sign(expected), sign(actual));
}
END_TEST

// проверка с символом \0
START_TEST(test_s21_memcmp_null_byte) {
  const char zero1[] = "a\0b";
  const char zero2[] = "a\0c";

  int expected = memcmp(zero1, zero2, 3);
  int actual = s21_memcmp(zero1, zero2, 3);
  ck_assert_int_eq(sign(expected), sign(actual));
}
END_TEST

#pragma endregion

#pragma region s21_memcpy

// просто копирование
START_TEST(test_s21_memcpy_basic) {
  char src[] = "Simple, Bash!";
  char dest1[20] = {0};
  char dest2[20] = {0};
  size_t n = 14;

  memcpy(dest1, src, n);  // Не сохраняем результат
  s21_memcpy(dest2, src, n);

  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

// n = 0
START_TEST(test_s21_memcpy_zero_bytes) {
  char src[] = "Bash!";
  char dest1[10] = {0};
  char dest2[10] = {0};

  memcpy(dest1, src, 0);
  s21_memcpy(dest2, src, 0);

  ck_assert_mem_eq(dest1, dest2, 10);
}
END_TEST

// копируем только часть
START_TEST(test_s21_memcpy_partial_copy) {
  char src[] = "Simple, Bash!";
  char dest1[20] = {0};
  char dest2[20] = {0};
  size_t n = 6;

  memcpy(dest1, src, n);
  s21_memcpy(dest2, src, n);

  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

// проверяем возвращаемое значение
START_TEST(test_s21_memcpy_return_pointer) {
  char src[] = "Test";
  char dest[10] = {0};

  void* result = s21_memcpy(dest, src, 4);

  ck_assert_ptr_eq(result, dest);
}
END_TEST

// проверяем бинарное значение
START_TEST(test_s21_memcpy_binary_data) {
  unsigned char src[] = {0x00, 0x01, 0x02, 0xFF, 0xFE, 0xFD};
  unsigned char dest1[10] = {0};
  unsigned char dest2[10] = {0};
  size_t n = 6;

  memcpy(dest1, src, n);
  s21_memcpy(dest2, src, n);

  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

// проверяем знак \0
START_TEST(test_s21_memcpy_with_null_bytes) {
  char src[] = "Hello\0World\0Test";
  char dest1[20] = {0};
  char dest2[20] = {0};
  size_t n = sizeof(src);

  memcpy(dest1, src, n);
  s21_memcpy(dest2, src, n);

  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

// пустая строка
START_TEST(test_s21_memcpy_empty_string) {
  char src[] = "";
  char dest1[10] = {0};
  char dest2[10] = {0};

  memcpy(dest1, src, 1);  // копируем \0
  s21_memcpy(dest2, src, 1);

  ck_assert_mem_eq(dest1, dest2, 10);
}
END_TEST

// очень большая строка
START_TEST(test_s21_memcpy_large_data) {
  size_t size = 10000;
  char* src = (char*)malloc(size);
  char* dest1 = (char*)malloc(size);
  char* dest2 = (char*)malloc(size);

  for (size_t i = 0; i < size; i++) {
    src[i] = (i % 256);
  }

  memcpy(dest1, src, size);
  s21_memcpy(dest2, src, size);

  ck_assert_mem_eq(dest1, dest2, size);

  free(src);
  free(dest1);
  free(dest2);
}
END_TEST

#pragma endregion

#pragma region s21_memset

// заполнение 10 байт символом '@'
START_TEST(test_s21_memset_ten_bytes) {
  char str1[] = "Simple, Bash!";
  char str2[] = "Simple, Bash!";
  size_t n = 10;
  int c = '@';

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_mem_eq(str1, str2, sizeof(str2));
}
END_TEST

// меняем 1 символ
START_TEST(test_s21_memset_single_byte) {
  char str1[] = "Simple, Bash!";
  char str2[] = "Simple, Bash!";
  size_t n = 1;
  int c = '0';

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_mem_eq(str1, str2, sizeof(str2));
}
END_TEST

// заполнение всей строки символом ')'
START_TEST(test_s21_memset_full_string) {
  char str1[] = "Simple, Bash!";
  char str2[] = "Simple, Bash!";
  size_t n = sizeof(str2) - 1;  // без \0
  int c = ')';

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_mem_eq(str1, str2, sizeof(str2));
}
END_TEST

// заполненяем 40 байт цифрой 4
START_TEST(test_s21_memset_int_array_full) {
  int arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int arr2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  size_t n = 40;
  int c = 4;

  s21_memset(arr1, c, n);
  memset(arr2, c, n);

  ck_assert_mem_eq(arr1, arr2, sizeof(arr2));
}
END_TEST

// заполняем 20 байт цифрой 5
START_TEST(test_s21_memset_int_array_half) {
  int arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int arr2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  size_t n = 20;
  int c = 5;

  s21_memset(arr1, c, n);
  memset(arr2, c, n);

  ck_assert_mem_eq(arr1, arr2, sizeof(arr2));
}
END_TEST

// заполненяем 1 байт цифрой 1
START_TEST(test_s21_memset_int_array_single_byte) {
  int arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int arr2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  size_t n = 1;
  int c = 1;

  s21_memset(arr1, c, n);
  memset(arr2, c, n);

  ck_assert_mem_eq(arr1, arr2, sizeof(arr2));
}
END_TEST

// заполнение нулевого количества байт
START_TEST(test_s21_memset_zero_bytes) {
  char str1[] = "Simple, Bash!";
  char str2[] = "Simple, Bash!";
  size_t n = 0;
  int c = 'x';

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_mem_eq(str1, str2, sizeof(str2));
}
END_TEST

// проверка возвращаемого указателя
START_TEST(test_s21_memset_return_pointer) {
  char str[20] = "Simple, Bash!";
  int c = '*';
  size_t n = 5;

  void* result = s21_memset(str, c, n);

  ck_assert_ptr_eq(result, str);
}
END_TEST

#pragma endregion

#pragma region s21_strcspn

// символы из str2 встречаются в середине и конце
START_TEST(test_s21_strcspn_basic) {
  const char str1[] = "Simple, Bash!";
  const char str2[] = ",!";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// символы из str2 вообще не встречаются в str1
START_TEST(test_s21_strcspn_no_match) {
  const char str1[] = "Simple";
  const char str2[] = "xyz";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// совпадение на первом символе - должен вернуть 0
START_TEST(test_s21_strcspn_match_at_start) {
  const char str1[] = "Simple";
  const char str2[] = "S";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// совпадение только на последнем символе
START_TEST(test_s21_strcspn_match_at_end) {
  const char str1[] = "Simple";
  const char str2[] = "e";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// пустой str1 - 0
START_TEST(test_s21_strcspn_empty_str1) {
  const char str1[] = "";
  const char str2[] = "abc";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// пустой str2 - должен вернуть длину str1
START_TEST(test_s21_strcspn_empty_str2) {
  const char str1[] = "Simple";
  const char str2[] = "";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// обе строки пустые - 0
START_TEST(test_s21_strcspn_both_empty) {
  const char str1[] = "";
  const char str2[] = "";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// все символы str1 совпадают с str2 - 0
START_TEST(test_s21_strcspn_all_match) {
  const char str1[] = "aaa";
  const char str2[] = "a";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// несколько символов-разделителей, поиск до первой гласной
START_TEST(test_s21_strcspn_multiple_reject_chars) {
  const char str1[] = "hello world";
  const char str2[] = "aeiou";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// однобуквенная строка, символ совпадает - 0
START_TEST(test_s21_strcspn_single_char_match) {
  const char str1[] = "a";
  const char str2[] = "a";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

// однобуквенная строка, символ не совпадает
START_TEST(test_s21_strcspn_single_char_no_match) {
  const char str1[] = "a";
  const char str2[] = "b";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

#pragma endregion

#pragma region s21_strstr

// подстрока в середине
START_TEST(test_s21_strstr_basic) {
  const char haystack[] = "Simple, Bash!";
  const char needle[] = "Bash";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

// подстрока не найдена - NULL
START_TEST(test_s21_strstr_not_found) {
  const char haystack[] = "Simple, Bash!";
  const char needle[] = "xyz";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

// пустой needle - должен вернуть указатель на начало haystack
START_TEST(test_s21_strstr_empty_needle) {
  const char haystack[] = "Simple";
  const char needle[] = "";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

// пустой haystack - NULL
START_TEST(test_s21_strstr_empty_haystack) {
  const char haystack[] = "";
  const char needle[] = "abc";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

// обе строки пустые - должен вернуть указатель на haystack
START_TEST(test_s21_strstr_both_empty) {
  const char haystack[] = "";
  const char needle[] = "";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

// подстрока в начале haystack
START_TEST(test_s21_strstr_at_start) {
  const char haystack[] = "Simple";
  const char needle[] = "Sim";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

// подстрока в конце haystack
START_TEST(test_s21_strstr_at_end) {
  const char haystack[] = "Simple";
  const char needle[] = "ple";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

// needle равен haystack полностью
START_TEST(test_s21_strstr_full_match) {
  const char haystack[] = "Simple";
  const char needle[] = "Simple";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

// needle длиннее haystack - NULL
START_TEST(test_s21_strstr_needle_longer) {
  const char haystack[] = "Hi";
  const char needle[] = "Hello";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

// несколько вхождений
START_TEST(test_s21_strstr_multiple_occurrences) {
  const char haystack[] = "abababab";
  const char needle[] = "ab";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

// однобуквенный needle (найден)
START_TEST(test_s21_strstr_single_char_found) {
  const char haystack[] = "Simple";
  const char needle[] = "m";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

// однобуквенный needle (не найден)
START_TEST(test_s21_strstr_single_char_not_found) {
  const char haystack[] = "Simple";
  const char needle[] = "z";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

#pragma endregion

#pragma region s21_strtok

// 3 токена через запятую
START_TEST(test_s21_strtok_basic) {
  char str1[] = "one,two,three";
  char str2[] = "one,two,three";
  const char delim[] = ",";

  char* t1 = s21_strtok(str1, delim);
  char* t2 = strtok(str2, delim);
  while (t1 != NULL && t2 != NULL) {
    ck_assert_str_eq(t1, t2);
    t1 = s21_strtok(NULL, delim);
    t2 = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(t1, t2);
}
END_TEST

// без разделителя
START_TEST(test_s21_strtok_no_delim) {
  char str1[] = "Simple";
  char str2[] = "Simple";
  const char delim[] = ",";

  char* t1 = s21_strtok(str1, delim);
  char* t2 = strtok(str2, delim);
  ck_assert_str_eq(t1, t2);

  t1 = s21_strtok(NULL, delim);
  t2 = strtok(NULL, delim);
  ck_assert_ptr_eq(t1, t2);
}
END_TEST

// несколько разных разделителей
START_TEST(test_s21_strtok_multiple_delimiters) {
  char str1[] = "one:two;three";
  char str2[] = "one:two;three";
  const char delim[] = ":;";

  char* t1 = s21_strtok(str1, delim);
  char* t2 = strtok(str2, delim);
  while (t1 != NULL && t2 != NULL) {
    ck_assert_str_eq(t1, t2);
    t1 = s21_strtok(NULL, delim);
    t2 = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(t1, t2);
}
END_TEST

// разделители в начале строки
START_TEST(test_s21_strtok_leading_delimiters) {
  char str1[] = ",,one,two";
  char str2[] = ",,one,two";
  const char delim[] = ",";

  char* t1 = s21_strtok(str1, delim);
  char* t2 = strtok(str2, delim);
  while (t1 != NULL && t2 != NULL) {
    ck_assert_str_eq(t1, t2);
    t1 = s21_strtok(NULL, delim);
    t2 = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(t1, t2);
}
END_TEST

// разделители в конце строки
START_TEST(test_s21_strtok_trailing_delimiters) {
  char str1[] = "one,two,,";
  char str2[] = "one,two,,";
  const char delim[] = ",";

  char* t1 = s21_strtok(str1, delim);
  char* t2 = strtok(str2, delim);
  while (t1 != NULL && t2 != NULL) {
    ck_assert_str_eq(t1, t2);
    t1 = s21_strtok(NULL, delim);
    t2 = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(t1, t2);
}
END_TEST

// строка только из разделителей - NULL
START_TEST(test_s21_strtok_only_delimiters) {
  char str1[] = ",,,";
  char str2[] = ",,,";
  const char delim[] = ",";

  char* t1 = s21_strtok(str1, delim);
  char* t2 = strtok(str2, delim);
  ck_assert_ptr_eq(t1, t2);
}
END_TEST

// один токен без разделителей после него
START_TEST(test_s21_strtok_single_token) {
  char str1[] = "hello";
  char str2[] = "hello";
  const char delim[] = ",";

  char* t1 = s21_strtok(str1, delim);
  char* t2 = strtok(str2, delim);
  ck_assert_str_eq(t1, t2);

  t1 = s21_strtok(NULL, delim);
  t2 = strtok(NULL, delim);
  ck_assert_ptr_eq(t1, t2);
}
END_TEST

#pragma endregion

#pragma region s21_strchr
// поиск_в_середине
START_TEST(test_s21_strchr_basic) {
  const char str[] = "Learning C is fun!";
  ck_assert_ptr_eq(s21_strchr(str, 'f'), strchr(str, 'f'));
}
END_TEST

// поиск_в_начале
START_TEST(test_s21_strchr_start) {
  const char str[] = "0123456789";
  ck_assert_ptr_eq(s21_strchr(str, '0'), strchr(str, '0'));
}
END_TEST

// поиск_в_конце
START_TEST(test_s21_strchr_end) {
  const char str[] = "Look at the star*";
  ck_assert_ptr_eq(s21_strchr(str, '*'), strchr(str, '*'));
}
END_TEST

// отсутствие_совпадения
START_TEST(test_s21_strchr_not_found) {
  const char str[] = "Only letters here";
  ck_assert_ptr_eq(s21_strchr(str, '7'), strchr(str, '7'));
}
END_TEST

// пустая_строка
START_TEST(test_s21_strchr_empty_string) {
  const char str[] = "";
  ck_assert_ptr_eq(s21_strchr(str, '?'), strchr(str, '?'));
}
END_TEST

// поиск_терминатора
START_TEST(test_s21_strchr_null_char) {
  const char str[] = "Hidden\0End";
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

// первое_вхождение
START_TEST(test_s21_strchr_multiple) {
  const char str[] = "banana";
  ck_assert_ptr_eq(s21_strchr(str, 'a'), strchr(str, 'a'));
}
END_TEST
#pragma endregion

#pragma region s21_strrchr
// последнее_вхождение
START_TEST(test_s21_strrchr_basic) {
  const char str[] = "Path/to/my/file.txt";
  ck_assert_ptr_eq(s21_strrchr(str, '/'), strrchr(str, '/'));
}
END_TEST

// несколько_совпадений
START_TEST(test_s21_strrchr_multiple) {
  const char str[] = "mississippi";
  ck_assert_ptr_eq(s21_strrchr(str, 'i'), strrchr(str, 'i'));
}
END_TEST

// поиск_начала
START_TEST(test_s21_strrchr_start) {
  const char str[] = "Alpha Beta Gamma";
  ck_assert_ptr_eq(s21_strrchr(str, 'A'), strrchr(str, 'A'));
}
END_TEST

// символ_отсутствует
START_TEST(test_s21_strrchr_not_found) {
  const char str[] = "No underscores here";
  ck_assert_ptr_eq(s21_strrchr(str, '_'), strrchr(str, '_'));
}
END_TEST

// пустой_вход
START_TEST(test_s21_strrchr_empty) {
  const char str[] = "";
  ck_assert_ptr_eq(s21_strrchr(str, ' '), strrchr(str, ' '));
}
END_TEST

// поиск_конца
START_TEST(test_s21_strrchr_null_char) {
  const char str[] = "Final destination";
  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST
#pragma endregion

#pragma region s21_strncmp
// полное_совпадение
START_TEST(test_s21_strncmp_equal) {
  const char s1[] = "Identical";
  const char s2[] = "Identical";
  ck_assert_int_eq(sign(s21_strncmp(s1, s2, 9)), sign(strncmp(s1, s2, 9)));
}
END_TEST

// частичное_совпадение
START_TEST(test_s21_strncmp_different_n) {
  const char s1[] = "Apple Pie";
  const char s2[] = "Apple Pen";
  ck_assert_int_eq(sign(s21_strncmp(s1, s2, 7)), sign(strncmp(s1, s2, 7)));
  ck_assert_int_eq(sign(s21_strncmp(s1, s2, 8)), sign(strncmp(s1, s2, 8)));
}
END_TEST

// нулевая_длина
START_TEST(test_s21_strncmp_n_zero) {
  ck_assert_int_eq(s21_strncmp("Same", "Different", 0),
                   strncmp("Same", "Different", 0));
}
END_TEST

// сравнение_пустой
START_TEST(test_s21_strncmp_one_empty) {
  ck_assert_int_eq(sign(s21_strncmp("", "Full", 1)),
                   sign(strncmp("", "Full", 1)));
}
END_TEST

// длина_больше_строки
START_TEST(test_s21_strncmp_short_n) {
  ck_assert_int_eq(sign(s21_strncmp("Short", "Shorter", 15)),
                   sign(strncmp("Short", "Shorter", 15)));
}
END_TEST
#pragma endregion

#pragma region s21_strpbrk
// набор_символов
START_TEST(test_s21_strpbrk_basic) {
  const char s1[] = "Hello world!";
  const char s2[] = "aeiou";
  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

// нет_вхождений
START_TEST(test_s21_strpbrk_not_found) {
  const char s1[] = "1234567890";
  const char s2[] = "ABC";
  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

// пустой_набор
START_TEST(test_s21_strpbrk_empty_accept) {
  const char s1[] = "Waiting for nothing";
  ck_assert_ptr_eq(s21_strpbrk(s1, ""), strpbrk(s1, ""));
}
END_TEST

// вхождение_в_начале
START_TEST(test_s21_strpbrk_match_at_start) {
  const char s1[] = "#hashtag";
  const char s2[] = "!@#$%";
  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

// вхождение_в_конце
START_TEST(test_s21_strpbrk_match_at_end) {
  const char s1[] = "Finish line.";
  const char s2[] = ".,?";
  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

#pragma endregion

#pragma region s21_strlen

START_TEST(test_s21_strlen_basic) {
  ck_assert_uint_eq(s21_strlen("Hello"), strlen("Hello"));
}
END_TEST

START_TEST(test_s21_strlen_empty) {
  ck_assert_uint_eq(s21_strlen(""), strlen(""));
}
END_TEST

START_TEST(test_s21_strlen_single_char) {
  ck_assert_uint_eq(s21_strlen("a"), strlen("a"));
}
END_TEST

START_TEST(test_s21_strlen_long) {
  const char* s = "abcdefghijklmnopqrstuvwxyz";
  ck_assert_uint_eq(s21_strlen(s), strlen(s));
}
END_TEST

START_TEST(test_s21_strlen_spaces) {
  ck_assert_uint_eq(s21_strlen("   "), strlen("   "));
}
END_TEST

#pragma endregion

#pragma region s21_strncpy

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-truncation"

START_TEST(test_s21_strncpy_basic) {
  char d1[20] = {0}, d2[20] = {0};
  s21_strncpy(d1, "Hello", 5);
  strncpy(d2, "Hello", 5);
  ck_assert_mem_eq(d1, d2, 20);
}
END_TEST

START_TEST(test_s21_strncpy_truncate) {
  char d1[10] = {0}, d2[10] = {0};
  s21_strncpy(d1, "Hello, World!", 5);
  strncpy(d2, "Hello, World!", 5);
  ck_assert_mem_eq(d1, d2, 10);
}
END_TEST

START_TEST(test_s21_strncpy_pad_nulls) {
  char d1[10], d2[10];
  memset(d1, 'X', 10);
  memset(d2, 'X', 10);
  s21_strncpy(d1, "Hi", 10);
  strncpy(d2, "Hi", 10);
  ck_assert_mem_eq(d1, d2, 10);
}
END_TEST

START_TEST(test_s21_strncpy_zero_n) {
  char d1[] = "AAAA", d2[] = "AAAA";
  s21_strncpy(d1, "Hello", 0);
  strncpy(d2, "Hello", 0);
  ck_assert_str_eq(d1, d2);
}
END_TEST

#pragma GCC diagnostic pop

START_TEST(test_s21_strncpy_return_ptr) {
  char d1[20] = {0};
  char* ret = s21_strncpy(d1, "Test", 4);
  ck_assert_ptr_eq(ret, d1);
}
END_TEST

#pragma endregion

#pragma region s21_strncat

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-overflow"

START_TEST(test_s21_strncat_basic) {
  char d1[30] = "Hello", d2[30] = "Hello";
  s21_strncat(d1, ", World!", 8);
  strncat(d2, ", World!", 8);
  ck_assert_str_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_strncat_truncate) {
  char d1[30] = "Hello", d2[30] = "Hello";
  s21_strncat(d1, ", World!", 3);
  strncat(d2, ", World!", 3);
  ck_assert_str_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_strncat_zero_n) {
  char d1[30] = "Hello", d2[30] = "Hello";
  s21_strncat(d1, "World", 0);
  strncat(d2, "World", 0);
  ck_assert_str_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_strncat_empty_dest) {
  char d1[30] = "", d2[30] = "";
  s21_strncat(d1, "Hello", 5);
  strncat(d2, "Hello", 5);
  ck_assert_str_eq(d1, d2);
}
END_TEST

#pragma GCC diagnostic pop

START_TEST(test_s21_strncat_return_ptr) {
  char d1[30] = "Hi";
  char* ret = s21_strncat(d1, " there", 6);
  ck_assert_ptr_eq(ret, d1);
}
END_TEST

#pragma endregion

#pragma region s21_strerror

START_TEST(test_s21_strerror_zero) {
  ck_assert_str_eq(s21_strerror(0), strerror(0));
}
END_TEST

START_TEST(test_s21_strerror_one) {
  ck_assert_str_eq(s21_strerror(1), strerror(1));
}
END_TEST

START_TEST(test_s21_strerror_two) {
  ck_assert_str_eq(s21_strerror(2), strerror(2));
}
END_TEST

START_TEST(test_s21_strerror_five) {
  ck_assert_str_eq(s21_strerror(5), strerror(5));
}
END_TEST

START_TEST(test_s21_strerror_unknown) {
  char* res = s21_strerror(9999);
  ck_assert_ptr_ne(res, S21_NULL);
  ck_assert_int_ne(s21_strlen(res), 0);
}
END_TEST

START_TEST(test_s21_strerror_negative) {
  char* res = s21_strerror(-1);
  ck_assert_ptr_ne(res, S21_NULL);
  ck_assert_int_ne(s21_strlen(res), 0);
}
END_TEST

#pragma endregion

#pragma region s21_sprintf

START_TEST(test_s21_sprintf_f) {
  char buf1[500];
  char buf2[500];

  // обычный float
  ck_assert_int_eq(s21_sprintf(buf1, "%f", 123.456),
                   sprintf(buf2, "%f", 123.456));
  ck_assert_str_eq(buf1, buf2);

  // на точность
  ck_assert_int_eq(s21_sprintf(buf1, "%.2f", 0.123),
                   sprintf(buf2, "%.2f", 0.123));
  ck_assert_str_eq(buf1, buf2);

  // на отрицательные числа
  ck_assert_int_eq(s21_sprintf(buf1, "%f", -10.99),
                   sprintf(buf2, "%f", -10.99));
  ck_assert_str_eq(buf1, buf2);

  // на целые числа (если Oswycane уже закончил)
  ck_assert_int_eq(s21_sprintf(buf1, "%d", 21), sprintf(buf2, "%d", 21));
  ck_assert_str_eq(buf1, buf2);
}

END_TEST

START_TEST(test_s21_sprintf_space) {
  char buf1[500];
  char buf2[500];

  // пробел перед положительным %d
  ck_assert_int_eq(s21_sprintf(buf1, "% d", 5), sprintf(buf2, "% d", 5));
  ck_assert_str_eq(buf1, buf2);

  // отрицательный %d — пробела не должно быть
  ck_assert_int_eq(s21_sprintf(buf1, "% d", -5), sprintf(buf2, "% d", -5));
  ck_assert_str_eq(buf1, buf2);

  // ноль с флагом пробела %d
  ck_assert_int_eq(s21_sprintf(buf1, "% d", 0), sprintf(buf2, "% d", 0));
  ck_assert_str_eq(buf1, buf2);

  // пробел перед положительным %f
  ck_assert_int_eq(s21_sprintf(buf1, "% f", 3.14), sprintf(buf2, "% f", 3.14));
  ck_assert_str_eq(buf1, buf2);

  // отрицательный %f — пробела не должно быть
  ck_assert_int_eq(s21_sprintf(buf1, "% f", -3.14),
                   sprintf(buf2, "% f", -3.14));
  ck_assert_str_eq(buf1, buf2);

  // ноль с флагом пробела %f
  ck_assert_int_eq(s21_sprintf(buf1, "% f", 0.0), sprintf(buf2, "% f", 0.0));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_u) {
  char buf1[500];
  char buf2[500];

  // обычное беззнаковое число
  ck_assert_int_eq(s21_sprintf(buf1, "%u", 42u), sprintf(buf2, "%u", 42u));
  ck_assert_str_eq(buf1, buf2);

  // максимальное беззнаковое
  ck_assert_int_eq(s21_sprintf(buf1, "%u", 4294967295u),
                   sprintf(buf2, "%u", 4294967295u));
  ck_assert_str_eq(buf1, buf2);

  // ноль
  ck_assert_int_eq(s21_sprintf(buf1, "%u", 0u), sprintf(buf2, "%u", 0u));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_percent) {
  char buf1[500];
  char buf2[500];

  // просто знак процента
  ck_assert_int_eq(s21_sprintf(buf1, "%%"), sprintf(buf2, "%%"));
  ck_assert_str_eq(buf1, buf2);

  // процент в строке с другими символами
  ck_assert_int_eq(s21_sprintf(buf1, "100%%"), sprintf(buf2, "100%%"));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_d_signs) {
  char buf1[500];
  char buf2[500];

  // Обычный вывод
  ck_assert_int_eq(s21_sprintf(buf1, "%d", 123), sprintf(buf2, "%d", 123));
  ck_assert_str_eq(buf1, buf2);

  // Флаг +
  ck_assert_int_eq(s21_sprintf(buf1, "%+d", 5), sprintf(buf2, "%+d", 5));
  ck_assert_str_eq(buf1, buf2);

  // Флаг пробел
  ck_assert_int_eq(s21_sprintf(buf1, "% d", 10), sprintf(buf2, "% d", 10));
  ck_assert_str_eq(buf1, buf2);

  // Отрицательное число (пробел должен игнорироваться)
  ck_assert_int_eq(s21_sprintf(buf1, "% d", -10), sprintf(buf2, "% d", -10));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_d_precision) {
  char buf1[500];
  char buf2[500];

  // Простая точность
  ck_assert_int_eq(s21_sprintf(buf1, "%.5d", 42), sprintf(buf2, "%.5d", 42));
  ck_assert_str_eq(buf1, buf2);

  // Точность больше самого числа с минусом
  ck_assert_int_eq(s21_sprintf(buf1, "%.5d", -42), sprintf(buf2, "%.5d", -42));
  ck_assert_str_eq(buf1, buf2);

  // Граничный случай: точность 0 для числа 0 (должна быть пустая строка)
  ck_assert_int_eq(s21_sprintf(buf1, "%.0d", 0), sprintf(buf2, "%.0d", 0));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_d_lengths_complex) {
  char buf1[500];
  char buf2[500];

  // Длина l (long)
  long l_val = 1234567890123L;
  ck_assert_int_eq(s21_sprintf(buf1, "%ld", l_val),
                   sprintf(buf2, "%ld", l_val));
  ck_assert_str_eq(buf1, buf2);

  // Длина h (short)
  short h_val = -32768;
  ck_assert_int_eq(s21_sprintf(buf1, "%hd", h_val),
                   sprintf(buf2, "%hd", h_val));
  ck_assert_str_eq(buf1, buf2);

  // Комплекс: Плюс + Точность + Длина l
  long complex_val = 987654321L;
  ck_assert_int_eq(s21_sprintf(buf1, "%+.12ld", complex_val),
                   sprintf(buf2, "%+.12ld", complex_val));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

#pragma region s21_sprintf_s

START_TEST(test_s21_sprintf_s_basic) {
  char b1[100], b2[100];
  ck_assert_int_eq(s21_sprintf(b1, "%s", "hello"), sprintf(b2, "%s", "hello"));
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sprintf_s_width_right) {
  char b1[100], b2[100];
  ck_assert_int_eq(s21_sprintf(b1, "%10s", "hello"),
                   sprintf(b2, "%10s", "hello"));
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sprintf_s_width_left) {
  char b1[100], b2[100];
  ck_assert_int_eq(s21_sprintf(b1, "%-10s", "hello"),
                   sprintf(b2, "%-10s", "hello"));
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sprintf_s_width_smaller) {
  char b1[100], b2[100];
  ck_assert_int_eq(s21_sprintf(b1, "%3s", "hello"),
                   sprintf(b2, "%3s", "hello"));
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sprintf_s_precision) {
  char b1[100], b2[100];
  ck_assert_int_eq(s21_sprintf(b1, "%.3s", "hello"),
                   sprintf(b2, "%.3s", "hello"));
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sprintf_s_width_and_precision) {
  char b1[100], b2[100];
  ck_assert_int_eq(s21_sprintf(b1, "%10.3s", "hello"),
                   sprintf(b2, "%10.3s", "hello"));
  ck_assert_str_eq(b1, b2);
}
END_TEST

#pragma endregion

#pragma endregion

#pragma region suite
Suite* s21_string_suite(void) {
  Suite* suite = suite_create("s21_string");

  // тестовые кейсы для каждой функции
  TCase* tc_memchr = tcase_create("s21_memchr");
  TCase* tc_memcmp = tcase_create("s21_memcmp");
  TCase* tc_memcpy = tcase_create("s21_memcpy");
  TCase* tc_memset = tcase_create("s21_memset");
  TCase* tc_strcspn = tcase_create("s21_strcspn");
  TCase* tc_strstr = tcase_create("s21_strstr");
  TCase* tc_strtok = tcase_create("s21_strtok");
  TCase* tc_strchr = tcase_create("s21_strchr");
  TCase* tc_strrchr = tcase_create("s21_strrchr");
  TCase* tc_strncmp = tcase_create("s21_strncmp");
  TCase* tc_strpbrk = tcase_create("s21_strpbrk");

  // тесты для s21_memchr
  tcase_add_test(tc_memchr, test_s21_memchr_beginning);
  tcase_add_test(tc_memchr, test_s21_memchr_middle);
  tcase_add_test(tc_memchr, test_s21_memchr_end);
  tcase_add_test(tc_memchr, test_s21_memchr_not_found);
  tcase_add_test(tc_memchr, test_s21_memchr_n_zero);
  tcase_add_test(tc_memchr, test_s21_memchr_n_less_than_position);
  tcase_add_test(tc_memchr, test_s21_memchr_n_greater_than_position);
  tcase_add_test(tc_memchr, test_s21_memchr_n_equal_one);
  tcase_add_test(tc_memchr, test_s21_memchr_empty_string);
  tcase_add_test(tc_memchr, test_s21_memchr_null_character);
  tcase_add_test(tc_memchr, test_s21_memchr_multiple_occurrences);
  tcase_add_test(tc_memchr, test_s21_memchr_non_ascii);
  tcase_add_test(tc_memchr, test_s21_memchr_int_conversion_positive);
  tcase_add_test(tc_memchr, test_s21_memchr_int_conversion_negative);
  tcase_add_test(tc_memchr, test_s21_memchr_int_conversion_overflow);
  tcase_add_test(tc_memchr, test_s21_memchr_large_string);
  tcase_add_test(tc_memchr, test_s21_memchr_binary_data);
  tcase_add_test(tc_memchr, test_s21_memchr_binary_data_not_found);

  // тесты для s21_memcmp
  tcase_add_test(tc_memcmp, test_s21_memcmp_n_zero);
  tcase_add_test(tc_memcmp, test_s21_memcmp_equal_strings);
  tcase_add_test(tc_memcmp, test_s21_memcmp_different_middle);
  tcase_add_test(tc_memcmp, test_s21_memcmp_different_start);
  tcase_add_test(tc_memcmp, test_s21_memcmp_binary_data);
  tcase_add_test(tc_memcmp, test_s21_memcmp_different_size);
  tcase_add_test(tc_memcmp, test_s21_memcmp_large_equal);
  tcase_add_test(tc_memcmp, test_s21_memcmp_large_different);
  tcase_add_test(tc_memcmp, test_s21_memcmp_single_equal);
  tcase_add_test(tc_memcmp, test_s21_memcmp_single_different);
  tcase_add_test(tc_memcmp, test_s21_memcmp_null_byte);

  // тесты для s21_memcpy
  tcase_add_test(tc_memcpy, test_s21_memcpy_basic);
  tcase_add_test(tc_memcpy, test_s21_memcpy_zero_bytes);
  tcase_add_test(tc_memcpy, test_s21_memcpy_partial_copy);
  tcase_add_test(tc_memcpy, test_s21_memcpy_return_pointer);
  tcase_add_test(tc_memcpy, test_s21_memcpy_with_null_bytes);
  tcase_add_test(tc_memcpy, test_s21_memcpy_empty_string);
  tcase_add_test(tc_memcpy, test_s21_memcpy_large_data);
  tcase_add_test(tc_memcpy, test_s21_memcpy_binary_data);

  // тесты для s21_memset
  tcase_add_test(tc_memset, test_s21_memset_ten_bytes);
  tcase_add_test(tc_memset, test_s21_memset_single_byte);
  tcase_add_test(tc_memset, test_s21_memset_full_string);
  tcase_add_test(tc_memset, test_s21_memset_int_array_full);
  tcase_add_test(tc_memset, test_s21_memset_int_array_half);
  tcase_add_test(tc_memset, test_s21_memset_int_array_single_byte);
  tcase_add_test(tc_memset, test_s21_memset_zero_bytes);
  tcase_add_test(tc_memset, test_s21_memset_return_pointer);

  // тесты для s21_strcspn
  tcase_add_test(tc_strcspn, test_s21_strcspn_basic);
  tcase_add_test(tc_strcspn, test_s21_strcspn_no_match);
  tcase_add_test(tc_strcspn, test_s21_strcspn_match_at_start);
  tcase_add_test(tc_strcspn, test_s21_strcspn_match_at_end);
  tcase_add_test(tc_strcspn, test_s21_strcspn_empty_str1);
  tcase_add_test(tc_strcspn, test_s21_strcspn_empty_str2);
  tcase_add_test(tc_strcspn, test_s21_strcspn_both_empty);
  tcase_add_test(tc_strcspn, test_s21_strcspn_all_match);
  tcase_add_test(tc_strcspn, test_s21_strcspn_multiple_reject_chars);
  tcase_add_test(tc_strcspn, test_s21_strcspn_single_char_match);
  tcase_add_test(tc_strcspn, test_s21_strcspn_single_char_no_match);

  // тесты для s21_strstr
  tcase_add_test(tc_strstr, test_s21_strstr_basic);
  tcase_add_test(tc_strstr, test_s21_strstr_not_found);
  tcase_add_test(tc_strstr, test_s21_strstr_empty_needle);
  tcase_add_test(tc_strstr, test_s21_strstr_empty_haystack);
  tcase_add_test(tc_strstr, test_s21_strstr_both_empty);
  tcase_add_test(tc_strstr, test_s21_strstr_at_start);
  tcase_add_test(tc_strstr, test_s21_strstr_at_end);
  tcase_add_test(tc_strstr, test_s21_strstr_full_match);
  tcase_add_test(tc_strstr, test_s21_strstr_needle_longer);
  tcase_add_test(tc_strstr, test_s21_strstr_multiple_occurrences);
  tcase_add_test(tc_strstr, test_s21_strstr_single_char_found);
  tcase_add_test(tc_strstr, test_s21_strstr_single_char_not_found);

  // тесты для s21_strtok
  tcase_add_test(tc_strtok, test_s21_strtok_basic);
  tcase_add_test(tc_strtok, test_s21_strtok_no_delim);
  tcase_add_test(tc_strtok, test_s21_strtok_multiple_delimiters);
  tcase_add_test(tc_strtok, test_s21_strtok_leading_delimiters);
  tcase_add_test(tc_strtok, test_s21_strtok_trailing_delimiters);
  tcase_add_test(tc_strtok, test_s21_strtok_only_delimiters);
  tcase_add_test(tc_strtok, test_s21_strtok_single_token);

  // тесты для s21_strchr
  tcase_add_test(tc_strchr, test_s21_strchr_basic);
  tcase_add_test(tc_strchr, test_s21_strchr_start);
  tcase_add_test(tc_strchr, test_s21_strchr_end);
  tcase_add_test(tc_strchr, test_s21_strchr_not_found);
  tcase_add_test(tc_strchr, test_s21_strchr_empty_string);
  tcase_add_test(tc_strchr, test_s21_strchr_null_char);
  tcase_add_test(tc_strchr, test_s21_strchr_multiple);

  // тесты для s21_strrchr
  tcase_add_test(tc_strrchr, test_s21_strrchr_basic);
  tcase_add_test(tc_strrchr, test_s21_strrchr_multiple);
  tcase_add_test(tc_strrchr, test_s21_strrchr_start);
  tcase_add_test(tc_strrchr, test_s21_strrchr_not_found);
  tcase_add_test(tc_strrchr, test_s21_strrchr_empty);
  tcase_add_test(tc_strrchr, test_s21_strrchr_null_char);

  // тесты для s21_strncmp
  tcase_add_test(tc_strncmp, test_s21_strncmp_equal);
  tcase_add_test(tc_strncmp, test_s21_strncmp_different_n);
  tcase_add_test(tc_strncmp, test_s21_strncmp_n_zero);
  tcase_add_test(tc_strncmp, test_s21_strncmp_one_empty);
  tcase_add_test(tc_strncmp, test_s21_strncmp_short_n);

  // тесты для s21_strpbrk
  tcase_add_test(tc_strpbrk, test_s21_strpbrk_basic);
  tcase_add_test(tc_strpbrk, test_s21_strpbrk_not_found);
  tcase_add_test(tc_strpbrk, test_s21_strpbrk_empty_accept);
  tcase_add_test(tc_strpbrk, test_s21_strpbrk_match_at_start);
  tcase_add_test(tc_strpbrk, test_s21_strpbrk_match_at_end);

  // Добавляем кейсы в сьют
  suite_add_tcase(suite, tc_memchr);
  suite_add_tcase(suite, tc_memcmp);
  suite_add_tcase(suite, tc_memcpy);
  suite_add_tcase(suite, tc_memset);
  suite_add_tcase(suite, tc_strcspn);
  suite_add_tcase(suite, tc_strstr);
  suite_add_tcase(suite, tc_strtok);
  suite_add_tcase(suite, tc_strchr);
  suite_add_tcase(suite, tc_strrchr);
  suite_add_tcase(suite, tc_strncmp);
  suite_add_tcase(suite, tc_strpbrk);

  TCase* tc_sprintf = tcase_create("s21_sprintf");
  tcase_add_test(tc_sprintf, test_s21_sprintf_f);
  tcase_add_test(tc_sprintf, test_s21_sprintf_space);
  tcase_add_test(tc_sprintf, test_s21_sprintf_u);
  tcase_add_test(tc_sprintf, test_s21_sprintf_percent);
  tcase_add_test(tc_sprintf, test_s21_sprintf_d_signs);
  tcase_add_test(tc_sprintf, test_s21_sprintf_d_precision);
  tcase_add_test(tc_sprintf, test_s21_sprintf_d_lengths_complex);
  tcase_add_test(tc_sprintf, test_s21_sprintf_s_basic);
  tcase_add_test(tc_sprintf, test_s21_sprintf_s_width_right);
  tcase_add_test(tc_sprintf, test_s21_sprintf_s_width_left);
  tcase_add_test(tc_sprintf, test_s21_sprintf_s_width_smaller);
  tcase_add_test(tc_sprintf, test_s21_sprintf_s_precision);
  tcase_add_test(tc_sprintf, test_s21_sprintf_s_width_and_precision);
  suite_add_tcase(suite, tc_sprintf);

  TCase* tc_strlen = tcase_create("s21_strlen");
  tcase_add_test(tc_strlen, test_s21_strlen_basic);
  tcase_add_test(tc_strlen, test_s21_strlen_empty);
  tcase_add_test(tc_strlen, test_s21_strlen_single_char);
  tcase_add_test(tc_strlen, test_s21_strlen_long);
  tcase_add_test(tc_strlen, test_s21_strlen_spaces);
  suite_add_tcase(suite, tc_strlen);

  TCase* tc_strncpy = tcase_create("s21_strncpy");
  tcase_add_test(tc_strncpy, test_s21_strncpy_basic);
  tcase_add_test(tc_strncpy, test_s21_strncpy_truncate);
  tcase_add_test(tc_strncpy, test_s21_strncpy_pad_nulls);
  tcase_add_test(tc_strncpy, test_s21_strncpy_zero_n);
  tcase_add_test(tc_strncpy, test_s21_strncpy_return_ptr);
  suite_add_tcase(suite, tc_strncpy);

  TCase* tc_strncat = tcase_create("s21_strncat");
  tcase_add_test(tc_strncat, test_s21_strncat_basic);
  tcase_add_test(tc_strncat, test_s21_strncat_truncate);
  tcase_add_test(tc_strncat, test_s21_strncat_zero_n);
  tcase_add_test(tc_strncat, test_s21_strncat_empty_dest);
  tcase_add_test(tc_strncat, test_s21_strncat_return_ptr);
  suite_add_tcase(suite, tc_strncat);

  TCase* tc_strerror = tcase_create("s21_strerror");
  tcase_add_test(tc_strerror, test_s21_strerror_zero);
  tcase_add_test(tc_strerror, test_s21_strerror_one);
  tcase_add_test(tc_strerror, test_s21_strerror_two);
  tcase_add_test(tc_strerror, test_s21_strerror_five);
  tcase_add_test(tc_strerror, test_s21_strerror_unknown);
  tcase_add_test(tc_strerror, test_s21_strerror_negative);
  suite_add_tcase(suite, tc_strerror);

  return suite;
}

#pragma endregion

int main(void) {
  Suite* suite = s21_string_suite();
  SRunner* runner = srunner_create(suite);

  srunner_run_all(runner, CK_VERBOSE);

  int failed_count = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed_count == 0) ? 0 : 1;
}