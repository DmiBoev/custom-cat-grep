CC = gcc
CFLAGS = -Wall -Werror -Wextra 

TARGET = my_grep

SRC = my_grep.c

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf $(TARGET)

rebuild: clean all
