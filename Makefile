CC = gcc
CFLAGS=-Wall -Wextra
TARGET=L2Cache

all:
	$(CC) $(CFLAGS) ./tests/SimpleProgram.c ./Task2/L2Cache.c -o $(TARGET)

clean:
	rm $(TARGET)