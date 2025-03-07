СС = gcc
ССflag = -Wextra -Werror -Wall -std=c11

all:clean main

main: s21_cat

s21_cat: cat_main.c cat_func.c cat_main.h
	$(СС) $(ССflag) cat_main.c cat_func.c -o s21_cat

clean:
	rm -rf s21_cat

rebuild: clean all

clang:
	clang-format -n *.c *.h

test:
	bash test_cat.sh

valgrind:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -b test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -e test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -n test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -s test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -t test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -v test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -E test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat -T test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat --number-nonblank test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat --number test_1.txt
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s  ./s21_cat --squeeze-blank test_1.txt
	
