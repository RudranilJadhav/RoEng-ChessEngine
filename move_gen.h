#ifndef MOVE_GEN_H
#define MOVE_GEN_H

#include "def.h"
#include "attacks.h"

void generate_pseudo_legal_moves(MOVE *move_list,int *count);
void generate_pseudo_legal_pawn_moves(MOVE *move_list,int *count);
void generate_pseudo_legal_knight_moves(MOVE *move_list,int *count);
void generate_pseudo_legal_bishop_moves(MOVE *move_list,int *count);
void generate_pseudo_legal_rook_moves(MOVE *move_list,int *count);
void generate_pseudo_legal_queen_moves(MOVE *move_list,int *count);
void generate_pseudo_legal_king_moves(MOVE *move_list,int *count);

void make_move(MOVE move);
void undo_move();
int generate_legal_moves(MOVE *legal_moves);
bool legal_move();
bool is_square_attacked(int square,int moved_side);
U64 perft(int depth);

#endif