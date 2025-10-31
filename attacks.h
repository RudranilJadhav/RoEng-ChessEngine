#ifndef ATTACKS_H
#define ATTACKS_H
#include<stdbool.h>
#include "move.h"

extern U64 knight_attacks[64];
extern U64 king_attacks[64];
extern U64 pawn_attacks[2][64];
extern const int rook_directions[4];
extern const int bishop_directions[4];

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