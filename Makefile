CC = gcc
CFLAGS = -Wall -Werror -Wextra
STD = -std=c11
CAT_SRC = ./cat/my_cat.c
GREP_SRC = ./grep/my_grep.c
CAT_TARGET = my_cat
GREP_TARGET = my_grep

.PHONY: all clean rebuild my_cat my_grep

all: my_cat my_grep

my_cat:
	$(CC) $(CFLAGS) $(STD) $(CAT_SRC) -o $(CAT_TARGET)

my_grep:
	$(CC) $(CFLAGS) $(STD) $(GREP_SRC) -o $(GREP_TARGET)

clean:
	rm -rf $(CAT_TARGET) $(GREP_TARGET)

rebuild: clean all
