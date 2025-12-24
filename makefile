CC = gcc
CFLAGS = -Wall -O2
SRC = attacks.c bbc.c board.c def.c fen.c init.c main.c move_gen.c zobrist.c eval.c tt.c
OUT = main

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)