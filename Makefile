CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -g
COVER = --coverage
TESTS = -lgtest
SOURCES = matrix_oop.cc matrix_oop_funcs.cc matrix_oop_operators.cc

all: test

clean:
	rm -rf *.o *.a test *.html *.css *.out
	rm -rf *.gcda *.gcno test.dSYM ./report

test: matrix_oop.a matrix_oop_tests.cc
	$(CC) $(CFLAGS) $(TESTS) $(COVER) matrix_oop_tests.cc matrix_oop.a -o $@
	./test

matrix_oop.a: $(SOURCES)
	$(CC) -c $(CFLAGS) $(COVER) $?
	ar rc $@ *.o
	ranlib $@
	rm -f *.o

rebuild: clean all

gcov_report: test
	./$?
	mkdir report
	gcovr -r . --html --html-details -o ./report/coverage_report.html
	rm -f *.gcda *.gcno
	open ./report/coverage_report.html

.PHONY: all clean test matrix_oop.a rebuild gcov_report

