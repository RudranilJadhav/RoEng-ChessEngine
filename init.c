#include "init.h"

void init(const char *fen){
    init_zobrist();
    init_knight_attacks();
    init_king_attacks();
    init_eval_mask();
    clear_hash_table();
    repetition_index=0;
    memset(repetition_table, 0ULL, sizeof(repetition_table));
    fen_to_position(fen);
}