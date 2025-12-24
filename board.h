#ifndef BOARD_H
#define BOARD_H

#include "def.h"
#include "zobrist.h"

char piece_to_char(int piece);
int char_to_piece(char ch);
void print_position();
void init_bb_by_squares(int squares[64]);
void clear_history();
void clear_board();



#endif