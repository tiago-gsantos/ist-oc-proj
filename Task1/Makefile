CC = gcc
CFLAGS=-Wall -Wextra
TARGET=Cache_L1

all:
	$(CC) $(CFLAGS) ../tests/SimpleProgram.c ./Cache_L1.c -o $(TARGET)
	./$(TARGET) > out.txt
	diff out.txt ../tests/results_L1.txt > diff.txt

clean:
	rm $(TARGET) out.txt diff.txt