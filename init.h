#ifndef INIT_H
#define INIT_H
#include "def.h"
#include "board.h"
#include "fen.h"
#include "attacks.h"
#include "move_gen.h"
#include "eval.h"
#include "tt.h"
#include "search.h"
void init();
int parse_move(char *move_string);
void parse_position(char *command);
void parse_go(char *command);
void uci_loop();
#endif