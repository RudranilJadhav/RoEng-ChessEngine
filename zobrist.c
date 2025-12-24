#include "zobrist.h"

void init_zobrist(){
    srand(28);
    for(int piece=White_Pawn;piece<=Black_King;piece++){
        for(int sq=a1;sq<=h8;sq++){
            zobrist.zobrist_pieces[piece][sq]=rand64();
        }
    }
    for(int file=0;file<=7;file++)zobrist.zobrist_ep[file]=rand64();
    for(int castling_right=0;castling_right<=15;castling_right++)zobrist.zobrist_castling[castling_right]=rand64();
    zobrist.zobrist_side=rand64();
}

U64 generate_zobrist_key(Position *pos){
    U64 key=0;
    for(int sq=a1;sq<=h8;sq++){
        if(pos->squares[sq]!=Empty){
            int piece=pos->squares[sq];
            key^=zobrist.zobrist_pieces[piece][sq];
        }
    }
    if(pos->side_to_move==White)key^=zobrist.zobrist_side;
    if(pos->ep!=No_SQ){
        int file=(pos->ep)%8;
        key^=zobrist.zobrist_ep[file];
    }
    key^=zobrist.zobrist_castling[pos->castling];
    return key;
}