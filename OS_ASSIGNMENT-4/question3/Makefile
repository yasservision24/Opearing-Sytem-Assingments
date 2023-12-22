CC = g++
CFLAGS = -Wall -Wextra -std=c++11

SRC = 3.c # assuming your source file has a .cpp extension
EXE = 3

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC)

clean:
	rm -f $(EXE)
