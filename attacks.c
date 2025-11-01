#include "attacks.h"

U64 knight_attacks[64];
U64 king_attacks[64];
U64 pawn_attacks[2][64];
U64 rook_attacks[64][4096];
U64 bishop_attacks[64][512];

const int rook_directions[4]={8,-8,1,-1};   
const int bishop_directions[4]={9,7,-7,-9};


U64 mask_knight(int sq){
    U64 attacks=0ULL;
    int rank=sq/8;
    int file=sq%8; 

    int dr[8]={2,1,-1,-2,-2,-1,1,2};
    int df[8]={1,2,2,1,-1,-2,-2,-1};

    for (int i=0;i<8;i++){
        int r =rank+dr[i];
        int f =file+df[i];
        if (r>=0&&r<8&&f>=0&&f<8){
            int sq_to=r*8+f;
            attacks|=(1ULL<<sq_to);
        }
    }
    return attacks;
}

void init_knight_attacks() {
    for(int sq=0;sq<64;sq++) knight_attacks[sq]=mask_knight(sq);
}


U64 mask_king(int sq){
    U64 attacks=0ULL;
    int rank=sq/8;
    int file=sq%8;
    for(int dr=-1;dr<=1;dr++){
        for(int df=-1;df<=1;df++){
            int r=rank+dr;int f=file+df;
            if(r>=0&&r<8&&f>=0&&f<8){
                int sq_to=r*8+f;
                attacks|=(1ULL<<sq_to);
            }
        }
    }
    return attacks;
}

void init_king_attacks(){
    for(int sq=0;sq<64;sq++) king_attacks[sq]=mask_king(sq);
}

inline bool is_valid_move(int from, int to, int dir) {
    int from_rank = from / 8, from_file = from % 8;
    int to_rank = to / 8, to_file = to % 8;
    if (dir==1||dir==-1){
        return (from_rank==to_rank);
    }
    if (dir==8||dir==-8){
        return (from_file==to_file);
    }
    if(dir==9||dir==-9||dir==7||dir==-7) {
        return (abs(from_rank-to_rank)==abs(from_file-to_file));
    }
    return false;
}


inline U64 sliding_attacks(int sq,const int *directions){
    U64 attacks=0ULL;
    int from_rank=sq/8;
    int from_file=sq%8;
    for(int i=0;i<4;i++){
        int dir=directions[i];
        int to=sq;
        while(1){
            to+=dir;

            if(to<0||to>63)break;
            int to_rank=to/8;
            int to_file=to%8;
            if(!is_valid_move(sq,to,dir))break;
            attacks|=(1ULL<<to);
            if((1ULL<<to)&pos.both_bb)break;
        }
    }
    return attacks;
}

inline U64 rook_attacks(int sq){
    return sliding_attacks(sq,rook_attacks);
}

inline U64 bishop_attacks(int sq){
    return sliding_attacks(sq,bishop_attacks);
}

inline U64 queen_attacks(int sq){
    return (sliding_attacks(sq,bishop_attacks)|sliding_attacks(sq,rook_attacks));
}