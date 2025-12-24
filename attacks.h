#ifndef ATTACKS_H
#define ATTACKS_H
#include "def.h"

U64 mask_knight(int sq);
void init_knight_attacks();
U64 mask_king(int sq);
void init_king_attacks();


U64 sliding_attacks(int sq,const int *directions);
U64 rook_attacks(int sq);
U64 bishop_attacks(int sq);
U64 queen_attacks(int sq);
bool is_valid_move(int from, int to, int dir);

#endif