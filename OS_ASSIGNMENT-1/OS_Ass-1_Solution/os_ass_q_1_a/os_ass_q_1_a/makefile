CC = gcc
CFLAGS = -Wall -Wextra

.PHONY: all clean

all: program

program: main.c
	$(CC) $(CFLAGS) -o run main.c

clean:
	rm -f run
