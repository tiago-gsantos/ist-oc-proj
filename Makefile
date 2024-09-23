CC = gcc
CFLAGS=-Wall -Wextra
TARGET=L2Cache

all:
	$(CC) $(CFLAGS) ./tests/SimpleProgram.c ./Task3/L2Cache.c -o $(TARGET)
	./$(TARGET) > out.txt
	diff out.txt ./tests/results_L2_2W.txt > diff.txt

clean:
	rm $(TARGET) out.txt diff.txt