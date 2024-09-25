CC = gcc
CFLAGS=-Wall -Wextra
TARGET=Cache_L2_1W

all:
	$(CC) $(CFLAGS) ../tests/SimpleProgram.c ./Cache_L2_1W.c -o $(TARGET)
	./$(TARGET) > out.txt
	diff out.txt ../tests/results_L2_1W.txt > diff.txt

clean:
	rm $(TARGET) out.txt diff.txt