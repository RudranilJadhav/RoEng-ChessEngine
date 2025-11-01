#ifndef BBC_H
#define BBC_H

#include "def.h"

#define get_bit(bitboard, square) (bitboard & (1ULL << square))

void print_bb(U64 bitboard);

static inline pop_lsb(U64 *bb){
    int idx=__builtin_ctzll(*bb);
    *bb&=(*bb-1);
    return idx;
}

static inline int bit_count(U64 x){
    return __builtin_popcountll(x);
}

static inline U64 set_bit(U64 bb,int sq){return bb|(1ULL<<sq);}

static inline int lsb_index(U64 bb){return __builtin_ctzll(bb);}

#endif