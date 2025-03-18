SHELL := /bin/bash
FLAG =-Wall -Wextra -Werror -std=c11
FILE=*.txt

all: s21_cat tests

build: s21_cat

s21_cat: clean
	gcc $(FLAG) s21_cat.c -o s21_cat

rebuild: clean build

tests:	rebuild
	-diff <(./s21_cat $(FILE)) <(cat $(FILE))
	-diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	-diff <(./s21_cat -t $(FILE)) <(cat -t $(FILE))
	-diff <(./s21_cat -s $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat --squeeze-blank $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat -n $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat --number $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat -b $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat --number-nonblank $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat -etsnb $(FILE)) <(cat -etsnb $(FILE))


clean: 
	rm -rf s21_cat