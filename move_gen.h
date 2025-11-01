#ifndef MOVE_GEN_H
#define MOVE_GEN_H
#include "move.h"
#include "attacks.h"

int generate_pawn_moves(Move *move_list);
int generate_sliding_moves(Move *movelist);
int generate_king_moves(Move *move_list);
int generate_pseudo_legal_moves(Move *move_list);
int generate_legal_moves(Move *legal_moves);
bool legal_move();
bool is_squares_attacked(int square,int moved_side);

#endif