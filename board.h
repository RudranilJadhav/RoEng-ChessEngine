#ifndef BOARD_H
#define BOARD_H

#include "def.h"
#include "bbc.h"

char piece_to_char(int piece);
int char_to_piece(char c);
void print_position(Position *pos);
void init_squares_by_bb(Position *pos);
void init_bb_by_squares(Position *pos,int sq[64]);
void init_board();
void clear_history();
void clear_board();


#endif