SHELL := /bin/bash
FLAG =-Wall -Wextra -Werror -std=c11
FILE=*.txt
PATTERNS=patterns.reg

all: clean s21_grep 

build: s21_grep

s21_grep:
	gcc $(FLAG) s21_grep.c -o s21_grep

rebuild: clean build

tests: rebuild
	-diff <(./s21_grep se $(FILE)) <(grep se $(FILE))
	-diff <(./s21_grep -v se $(FILE)) <(grep -v se $(FILE))
	-diff <(./s21_grep -i se $(FILE)) <(grep -i se $(FILE))
	-diff <(./s21_grep -iv se $(FILE)) <(grep -iv se $(FILE))
	-diff <(./s21_grep -in se $(FILE)) <(grep -in  se $(FILE))
	-diff <(./s21_grep -ie "^se" $(FILE)) <(grep -ie "^se" $(FILE))
	-diff <(./s21_grep -ince "^se" $(FILE)) <(grep -ince "^se" $(FILE))
	-diff <(./s21_grep -lh se $(FILE)) <(grep -lh se $(FILE))
	-diff <(./s21_grep -hc e $(FILE)) <(grep -hc e $(FILE))

	-diff <(./s21_grep -e He -e he $(FILE)) <(grep -e He -e he $(FILE))
	-diff <(./s21_grep -f $(PATTERNS) $(FILE)) <(grep -f $(PATTERNS) $(FILE))
	-diff <(./s21_grep -oi he $(FILE)) <(grep -oi he $(FILE))
	-diff <(./s21_grep -ohf $(PATTERNS) $(FILE)) <(grep -ohf $(PATTERNS) $(FILE))
	-diff <(./s21_grep -oinc he $(FILE)) <(grep -oinc he $(FILE))
	-diff <(./s21_grep -oihlnc -e he -e Se -f $(PATTERNS) $(FILE)) <(grep -oihlnc -e he -e Se -f $(PATTERNS) $(FILE))

clean: 
	rm -rf s21_grep
