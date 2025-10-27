#ifndef BBC_H
#define BBC_H

#include "def.h"

#define get_bit(bitboard, square) (bitboard & (1ULL << square))

void print_bb(U64 bitboard);

#endif


