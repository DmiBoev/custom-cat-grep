CC = gcc
CFLAGS = -Wall -Werror -Wextra
STD = -std=c11
CAT_SRC = s21_cat.c
GREP_SRC = s21_grep.c
CAT_TARGET = s21_cat
GREP_TARGET = s21_grep

.PHONY: all clean rebuild s21_cat s21_grep

all: s21_cat s21_grep

s21_cat:
	$(CC) $(CFLAGS) $(STD) $(CAT_SRC) -o $(CAT_TARGET)

s21_grep:
	$(CC) $(CFLAGS) $(STD) $(GREP_SRC) -o $(GREP_TARGET)

clean:
	rm -rf $(CAT_TARGET) $(GREP_TARGET)

rebuild: clean all
