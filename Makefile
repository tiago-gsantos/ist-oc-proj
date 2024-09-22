CC = gcc
CFLAGS=-Wall -Wextra
TARGET=L1Cache

all:
	$(CC) $(CFLAGS) ./tests/SimpleProgram.c ./Task1/L1Cache.c -o $(TARGET)

clean:
	rm $(TARGET)