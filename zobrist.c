#include "zobrist.h"
#include <stdint.h>
#include <stdlib.h>

static inline uint64_t rand64() {
    uint64_t r=0;
    for (int i=0;i<4;i++) {
        r=(r<<16)|(rand()&0xFFFF);
    }
    return r;
}

void init_zobrist(){
    srand(28);
    for(int p=1;p<=14;p++){
        if(p==7||p==8)continue;
        for(int sq=0;sq<64;sq++){
            zobrist.zobrist_pieces[p][sq]=rand64();
        }
    }
    for(int i=0;i<8;i++)zobrist.zobrist_ep[i]=rand64();
    for(int i=0;i<16;i++)zobrist.zobrist_castling[i]=rand64();
    zobrist.zobrist_side=rand64();
}

U64 generate_zobrist_key(Position *pos){
    U64 key=0;
    for(int sq=0;sq<64;sq++){
        if(pos->squares[sq]){
            key^=zobrist.zobrist_pieces[pos->squares[sq]][sq];
        }
    }
    if(pos->side_to_move)key^=zobrist.zobrist_side;
    if(pos->castling)key^=zobrist.zobrist_castling[pos->castling];
    if(pos->ep!=No_SQ){
        int ep_sq=pos->ep;
        int file=ep_sq%8;     
        key^=zobrist.zobrist_ep[file];       
    }
    return key;
}
