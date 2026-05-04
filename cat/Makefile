CC = gcc
CFLAGS = -Wall -Werror -Wextra 

TARGET = my_cat

SRC = my_cat.c

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf $(TARGET)

rebuild: clean all
