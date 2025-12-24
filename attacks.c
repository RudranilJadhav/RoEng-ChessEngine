#include "attacks.h"

U64 mask_knight(int sq){
    U64 attack=0ULL;
    int rank=sq/8;
    int file=sq%8;
    for(int i=0;i<8;i++){
        int r=rank+knight_directions_x[i];
        int f=file+knight_directions_y[i];
        if(r>=0&&r<8&&f>=0&&f<8){
            attack|=(1ULL<<(r*8+f));
        }
    }
    return attack;
}

void init_knight_attacks(){
    for(int sq=a1;sq<=h8;sq++)knight_attacks[sq]=mask_knight(sq);
}

bool is_valid_move(int from, int to, int dir) {
    int from_rank=from/8,from_file=from%8;
    int to_rank=to/8,to_file=to%8;
    if(dir==1||dir==-1){
        return (from_rank==to_rank);
    }
    if(dir==8||dir==-8){
        return (from_file==to_file);
    }
    if(dir==9||dir==-9||dir==7||dir==-7) {
        return (abs(from_rank-to_rank)==abs(from_file-to_file));
    }
    return false;
}


U64 sliding_attacks(int sq,const int *directions){
    U64 attacks=0ULL;
    for(int i=0;i<4;i++){
        int dir=directions[i];
        int to=sq;
        while(1){
            to+=dir;
            if(to<0||to>63)break;
            if(!is_valid_move(sq,to,dir))break;
            attacks|=(1ULL<<to);
            if(((1ULL<<to)&(pos.both_bb)))break;
        }
    }
    return attacks;
}

U64 rook_attacks(int sq){
    return sliding_attacks(sq,rook_directions);
}

U64 bishop_attacks(int sq){
    return sliding_attacks(sq,bishop_directions);
}

U64 queen_attacks(int sq){
    return (sliding_attacks(sq,bishop_directions)|sliding_attacks(sq,rook_directions));
}

U64 mask_king(int sq){
    U64 attacks=0ULL;
    for(int dx=-1;dx<=1;dx++){
        for(int dy=-1;dy<=1;dy++){
            int r=sq/8+dx;int f=sq%8+dy;
            if(r>=0&&r<=7&&f>=0&&f<=7){
                attacks|=(1ULL<<(r*8+f));
            }
        }
    }
    return attacks;
}

void init_king_attacks(){
    for(int sq=a1;sq<=h8;sq++)king_attacks[sq]=mask_king(sq);
}