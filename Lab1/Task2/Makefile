CC = gcc
CFLAGS=-Wall -Wextra
TARGET=Cache_L2_1W

all:
	$(CC) $(CFLAGS) ./tests/SimpleProgram.c ./Cache_L2_1W.c -o $(TARGET)
	./$(TARGET) > ./tests/out.txt
	diff ./tests/out.txt ./tests/results_L2_1W.txt > ./tests/diff.txt
	$(CC) $(CFLAGS) ./tests/test.c ./Cache_L2_1W.c -o ./tests/test
	clear
	./tests/test


clean:
	rm $(TARGET) ./tests/out.txt ./tests/diff.txt ./tests/test