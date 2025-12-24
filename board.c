#include "board.h"

void print_position(){
    printf("\n");
    for(int rank=7;rank>=0;rank--){
        for(int file=0;file<=7;file++){
            int sq=rank*8+file;
            char piece = piece_to_char(pos.squares[sq]);
            printf(" %c",piece);
        }
        printf("\n");
    }
    printf("En-passant: ");
    if(pos.ep!=-1) {
        printf("%c%d",'a'+(pos.ep%8),1+(pos.ep/8));
    }
    else printf("-");
    printf("\n");
    printf("Halfmove: %d | Fullmove: %d\n", pos.halfmove, pos.fullmove);
    printf("Castling Rights: ");
    if(pos.castling==0)printf("-");
    else{
        if(pos.castling&WKCA)printf("K");
        if(pos.castling&WQCA)printf("Q");
        if(pos.castling&BKCA)printf("k");
        if(pos.castling&BQCA)printf("q");
    }
    printf("\n");
}

int char_to_piece(char ch){
if(ch=='.')return Empty;
if(ch=='P')return White_Pawn;
if(ch=='N')return White_Knight;
if(ch=='B')return White_Bishop;
if(ch=='R')return White_Rook;
if(ch=='Q')return White_Queen;
if(ch=='K')return White_King;
if(ch=='p')return Black_Pawn;
if(ch=='n')return Black_Knight;
if(ch=='b')return Black_Bishop;
if(ch=='r')return Black_Rook;
if(ch=='q')return Black_Queen;
if(ch=='k')return Black_King;
return Empty;
}

char piece_to_char(int piece){
if(piece==0)return '.';   
if(piece==1)return 'P';
if(piece==2)return 'N';
if(piece==3)return 'B';
if(piece==4)return 'R';
if(piece==5)return 'Q';
if(piece==6)return 'K';
if(piece==7)return 'p';
if(piece==8)return 'n';
if(piece==9)return 'b';
if(piece==10)return 'r';
if(piece==11)return 'q';
if(piece==12)return 'k';
return '.';
}

void init_bb_by_squares(int squares[64]){
    for(int i=0;i<12;i++) pos.piece_bb[i]=0;
    for(int i=0;i<2;i++) pos.colour_bb[i]=0;
    pos.both_bb=0;

    for(int sq=a1;sq<=h8;sq++){
        int piece=pos.squares[sq];
        pos.piece_bb[piece]|=(1ULL<<sq);
        if(COLOUR(piece)==White)pos.colour_bb[White]|=(1ULL<<sq);
        if(COLOUR(piece)==Black)pos.colour_bb[Black]|=(1ULL<<sq);
    }
    pos.both_bb=pos.colour_bb[White]|pos.colour_bb[Black];
}

void clear_history(){
    history.move_count=0;
}

void clear_board(){
    for(int i=0;i<64;i++)pos.squares[i]=Empty;
    for(int i=0;i<12;i++)pos.piece_bb[i]=0;
    for(int i=0;i<2;i++)pos.colour_bb[i]=0;
    pos.both_bb=0;
    pos.hash_key=0;
    pos.fullmove=1;
    pos.halfmove=0;
    pos.ep=-1;
    pos.castling=0;
    pos.side_to_move=0;
}