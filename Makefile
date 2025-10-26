CC = gcc
CFLAGS = -Wall -O2
SRC = main.c board.c zobrist.c def.c bbc.c move.c fen.c
OUT = main

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)
