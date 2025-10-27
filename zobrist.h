#ifndef ZOBRIST_H
#define ZOBRIST_H
#include "board.h"

void init_zobrist();
U64 generate_zobrist_key(Position *pos);
void update_zobrist(Position *pos,int move);

#endif