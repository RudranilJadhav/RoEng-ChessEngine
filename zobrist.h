#ifndef ZOBRIST_H
#define ZOBRIST_H
#include "def.h"

void init_zobrist();
U64 generate_zobrist_key(Position *pos);

#endif