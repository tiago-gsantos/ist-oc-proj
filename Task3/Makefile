CC = gcc
CFLAGS=-Wall -Wextra
TARGET=Cache_L2_2W

all:
	$(CC) $(CFLAGS) ../tests/SimpleProgram.c ./Cache_L2_2W.c -o $(TARGET)
	./$(TARGET) > out.txt
	diff out.txt ../tests/results_L2_2W.txt > diff.txt

clean:
	rm $(TARGET) out.txt diff.txt