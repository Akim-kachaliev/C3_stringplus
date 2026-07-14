OFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic
TFLAGS = -lcheck -lm -lpthread -lsubunit
#lcov для создаение отчета (нужно устанавливать)

all: s21_string.a

s21_string.a: s21_string.o s21_sprintf.o
	ar rc s21_string.a s21_string.o s21_sprintf.o
	ranlib s21_string.a

s21_sprintf.o: s21_sprintf.c
	gcc $(OFLAGS) -c s21_sprintf.c -o s21_sprintf.o

test: s21_string_test
	chmod +x ./s21_string_test
	./s21_string_test

s21_string_test: tests/s21_string_test.c s21_string.a
	gcc $(OFLAGS) -o s21_string_test tests/s21_string_test.c s21_string.a $(TFLAGS)

gcov_report: s21_string.c s21_sprintf.c tests/s21_string_test.c
	gcc $(OFLAGS) --coverage -o test_gcov s21_string.c s21_sprintf.c tests/s21_string_test.c $(TFLAGS)

	chmod +x ./test_gcov
	./test_gcov

	lcov -t "s21_string_test" -o s21_string.info -c -d .

	lcov --remove s21_string.info '*/tests/*' -o s21_string_filtered.info --ignore-errors unused

	genhtml -o report s21_string_filtered.info

	rm -f *.gcda *.gcno test_gcov

clean: 
	rm -rf *.o *.gch s21_string s21_string_test s21_string.a test_s21_string test_gcov *.gcda *.gcno *.info report/ 

rebuild: clean all

.PHONY: all test clean rebuild gcov_report
	