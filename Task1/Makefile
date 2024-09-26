CC = gcc
CFLAGS=-Wall -Wextra
TARGET=Cache_L1

all:
	$(CC) $(CFLAGS) ./tests/SimpleProgram.c ./Cache_L1.c -o $(TARGET)
	./$(TARGET) > ./tests/out.txt
	diff ./tests/out.txt ./tests/results_L1.txt > ./tests/diff.txt
	$(CC) $(CFLAGS) ./tests/test.c ./Cache_L1.c -o ./tests/test
	clear
	./tests/test


clean:
	rm $(TARGET) ./tests/out.txt ./tests/diff.txt ./tests/test