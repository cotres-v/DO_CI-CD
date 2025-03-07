СС = gcc
ССflag = -Wextra -Werror -Wall -std=c11

all:clean main

main: s21_grep

s21_grep: grep_main.c grep_func.c grep_main.h
	$(СС) $(ССflag) grep_main.c grep_func.c -o s21_grep

clang:
	clang-format -n *.c *.h

test:
	bash test_grep.sh

valgrind:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -e time test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -i time test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -v time test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -c time test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -l time test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -n time test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -h time test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -f test_2 test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_grep -o time test_1.txt

clean:
	rm -rf s21_grep

rebuild: clean all