#include "board.h"
#include "zobrist.h"
#include <stdio.h>
#include <inttypes.h>



char piece_to_char(int piece){
    switch (piece) {
        case White_Pawn:   return 'P';
        case White_Knight: return 'N';
        case White_Bishop: return 'B';
        case White_Rook:   return 'R';
        case White_Queen:  return 'Q';
        case White_King:   return 'K';
        case Black_Pawn:   return 'p';
        case Black_Knight: return 'n';
        case Black_Bishop: return 'b';
        case Black_Rook:   return 'r';
        case Black_Queen:  return 'q';
        case Black_King:   return 'k';
        default:           return '.';
    }
}
int char_to_piece(char c){
        if(c=='.')   return Empty;
        if(c=='P')   return White_Pawn;
        if(c=='N')   return White_Knight;
        if(c=='B')   return White_Bishop;
        if(c=='R')   return White_Rook;
        if(c=='Q')   return White_Queen;
        if(c=='K')   return White_King;
        if(c=='p')   return Black_Pawn;
        if(c=='n')   return Black_Knight;
        if(c=='b')   return Black_Bishop;
        if(c=='r')   return Black_Rook;
        if(c=='q')   return Black_Queen;
        if(c=='k')   return Black_King;
        return Empty;
}

void print_position(Position *pos){
    printf("\n   +-----------------+\n");
    for(int rank=7;rank>=0;rank--){
        printf(" %d | ", rank + 1);
        for(int file=0;file<8;file++){
            int sq=rank*8+file;
            printf("%c ",piece_to_char(pos->squares[sq]));
        }
        printf("|\n");
    }
    printf("   +-----------------+\n");
    printf("     a b c d e f g h\n\n");

    printf("To play: %s \n",pos->side_to_move?"Black":"White");
    printf("Castling rights: ");
    if(pos->castling==0) printf("-");
    else{
        if(pos->castling&8) printf("K");
        if(pos->castling&4) printf("Q");
        if(pos->castling&2) printf("k");
        if(pos->castling&1) printf("q");
    }
    printf("\n");
    printf("En-passant: ");
    if(pos->ep!=-1) {
        printf("%c%d",'a'+(pos->ep%8),1+(pos->ep/8));
    }
    else printf("-");
    printf("\n");

    printf("Halfmove: %d | Fullmove: %d\n", pos->halfmove, pos->fullmove);
    printf("Zobrist Hash: 0x%016" PRIx64 "\n\n", pos->hash_key);

}

void init_squares_by_bb(Position *pos){
    for(int i=0;i<64;i++){
        pos->squares[i]=0;
    }
    for(int i=1;i<=14;i++){
        if(i>=7&&i<=8)continue;
        U64 bb=pos->piece_bb[i];
        while(bb){
            int sq= __builtin_ctzll(bb);
            pos->squares[sq]=i;
            bb=bb&(bb-1);
        }
    }
}

void init_bb_by_squares(Position *pos,int sq[64]){
    for(int i = 0; i < 64; i++)pos->squares[i] = sq[i];
    for(int i=0;i<16;i++)pos->piece_bb[i]=0;
    pos->colour_bb[White]=0;
    pos->colour_bb[Black]=0;
    pos->both_bb=0;
    for(int i=0;i<64;i++){
        if(pos->squares[i]){
            pos->piece_bb[pos->squares[i]]|=(1ULL<<i);
            pos->colour_bb[COLOUR(pos->squares[i])]|=(1ULL<<i);
            pos->both_bb|=(1ULL<<i);
        }
    }
}

void init_board(){
    clear_board();
    init_bb_by_squares(&pos,init_squares);
    init_zobrist();
    pos.side_to_move=0;
    pos.castling=0XF;
    pos.fullmove=1;
    pos.halfmove=0;
    pos.ep=No_SQ;
    pos.hash_key=generate_zobrist_key(&pos);
    clear_history();
}

void clear_board(){
    for(int i=0;i<64;i++)pos.squares[i]=Empty;
    for(int i=0;i<16;i++)pos.piece_bb[i]=0;
    for(int i=0;i<2;i++)pos.colour_bb[i]=0;
    pos.both_bb=0;
    pos.hash_key=0;
    pos.fullmove=1;
    pos.halfmove=0;
    pos.ep=-1;
    pos.castling=0;
    pos.side_to_move=0;
}

void clear_history(){
    for(int i=0;i<Max_Moves;i++){
        history.move[i]=0;
        history.captured_piece[i]=0;
        history.castling[i]=0;
        history.ep[i]=0;      
        history.halfmove[i]=0;
        history.hash_key[i]=0;
    }
    history.move_count=0;
}