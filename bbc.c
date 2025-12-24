#include "bbc.h"

void print_bb(U64 bb){
    printf("\n");
    for(int rank=7;rank>=0;rank--){
        for(int file=0;file<=7;file++){
            int sq=rank*8+file;
            printf("%d ",get_bit(bb,sq));
        }
        printf("\n");
    }
    printf("\n");
}