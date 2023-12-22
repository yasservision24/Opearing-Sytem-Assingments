CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC = example.c
EXE = example

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC)

clean:
	rm -f $(EXE)
