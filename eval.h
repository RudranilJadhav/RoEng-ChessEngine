#ifndef EVAL_H
#define EVAL_H
#include "move_gen.h"

U64 set_file_rank_mask(int file,int rank);
void init_eval_mask();
int evaluate();

#endif