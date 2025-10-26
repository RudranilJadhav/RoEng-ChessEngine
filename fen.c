#include "fen.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void fen_to_position(const char *fen){
    if (!fen) return;
    clear_board();
    const char *ptr=fen;
    if (!*ptr) return;
    int sq=a8;
    while(*ptr && *ptr!=' '){
        char c=*ptr;
        if(c!='/'){
            if(c-'0'>0&&c-'0'<=8){
                sq+=(c-'0');
            }
            else{
                pos.squares[sq]=char_to_piece(c);
                sq++;
            }
        }
        else{
            sq-=16;
        }
        ptr++;
    }
    ptr++;

    pos.side_to_move=(*ptr=='w')?White:Black;
    ptr+=2;
    while(*ptr&&*ptr!=' '){
        if(*ptr=='K')pos.castling|=0x8;
        if(*ptr=='Q')pos.castling|=0x4;
        if(*ptr=='k')pos.castling|=0x2;
        if(*ptr=='q')pos.castling|=0x1;
        ptr++;
    }
    ptr++;
    if(*ptr=='-'){ptr+=2;pos.ep=No_SQ;}
    else{
        int sq=0;
        sq+=(*ptr-'a')%8;
        ptr++;
        sq+=(*ptr-'1')*8;
        ptr+=2;
        pos.ep=sq;
    }

    pos.halfmove = 0;
    while (*ptr>='0'&& *ptr<='9') {
        pos.halfmove=pos.halfmove*10+(*ptr-'0');
        ptr++;
    }
    if(*ptr==' ')ptr++;
    pos.fullmove=0;
    while(*ptr>='0'&&*ptr<='9') {
        pos.fullmove=pos.fullmove*10+(*ptr-'0');
        ptr++;
    }
}