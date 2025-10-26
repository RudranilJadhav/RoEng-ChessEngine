#include<stdio.h>
#include "bbc.h"

void print_bb(U64 bitboard){
    printf("\n");
    for(int rank=7 ;rank>=0;rank--){
        for(int file=0;file<8;file++){
            int sq=rank*8+file;
            if(get_bit(bitboard,sq))printf("1 ");
            else printf("0 ");
        }
        printf("\n");
    }
    printf("\n");
}