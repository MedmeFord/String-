CC_FLAGS = -Wall -Werror -Wextra
CC = gcc
NAME = s21_string.a test
TEST_LIBS = -lcheck -lm -lpthread
OBJECTS = s21_sprintf.o s21_string.o
SOURSES = s21_sprintf.c s21_string.c
OS = $(shell uname)
ifeq ($(OS),Linux)
	CFLAGS+=-D LINUX
	TST_LIBS+= -lcheck_pic -lrt -lsubunit
else
	ifeq ($(OS),Darwin)
		CFLAGS+=-D MAC
	else
		CFLAGS+=-D LINUX
		TST_LIBS+= -lcheck_pic -lrt -lsubunit
	endif
endif

.PHONY: all clean test s21_string.a gcov_report

all: $(NAME)

test: s21_string_test.o s21_string.a $(OBJECTS)
	$(CC) $(CHECK_FLAGS) $(OBJECTS) s21_string_test.o s21_string.a $(TEST_LIBS) -o test
	./test

s21_string.o: s21_string.c
	$(CC) $(CC_FLAGS) -c s21_string.c

s21_string_test.o: s21_string_test.c	
	$(CC) $(CC_FLAGS) -c  s21_string_test.c

gcov_report: s21_string.a 
	$(CC) $(CC_FLAGS) --coverage s21_string_test.c s21_string.c s21_sprintf.c s21_string.a $(TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

check: s21_string.a
	cppcheck *.h *.c
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	$(CC) s21_string_test.c s21_string.a -lcheck
	$(CC) $(CC_FLAGS) -c s21_string_test.c -o test.o
	$(CC) test.o s21_string.a $(TEST_LIBS) -o test
	CK_FORK=no leaks --atExit -- ./test

s21_string.a: s21_string.o
	$(CC) -c $(SOURSES)
	ar rcs s21_string.a $(OBJECTS)

clean:
	rm -rf *.o test s21_string.a s21_string_test.c.gcov s21_string.c.gcov s21_string_test.gc* s21_string.gc* report gcov_report.info s21_sprintf.gc*

lo:
	for i in `seq 100 $(OP)`;	do ./test; done;

valgrind_check: s21_string.a
	CK_FORK=no valgrind --tool=memcheck ./test
	 
lik: s21_string.a
	CK_FORK=no leaks -atExit -- ./test
