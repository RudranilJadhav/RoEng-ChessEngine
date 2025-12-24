#include "eval.h"

U64 set_file_rank_mask(int f,int r){
    U64 mask=0;
    for(int rank=0;rank<8;rank++){
        for(int file=0;file<8;file++){
            int sq=8*rank+file;
            if(f!=-1){
                if(f==file)mask|=(1LL<<sq);
            }
            else if(r!=-1){
                if(r==rank)mask|=(1LL<<sq);
            }
        }
    }
    return mask;
}

void init_eval_mask(){
    for(int rank=0;rank<8;rank++){
        for(int file=0;file<8;file++){
            int sq=rank*8+file;
            file_mask[sq]=set_file_rank_mask(file,-1);
        }
    }
    for(int rank=0;rank<8;rank++){
        for(int file=0;file<8;file++){
            int sq=rank*8+file;
            rank_mask[sq]=set_file_rank_mask(-1,rank);
        }
    }
    for(int rank=0;rank<8;rank++){
        for(int file=0;file<8;file++){
            int sq=8*rank+file;
            isolated_mask[sq]|=set_file_rank_mask(file+1,-1);
            isolated_mask[sq]|=set_file_rank_mask(file-1,-1);
        }
    }
    for(int rank=0;rank<8;rank++){
        for(int file=0;file<8;file++){
            int sq=8*rank+file;
            white_passed_mask[sq]|=set_file_rank_mask(file+1,-1);
            white_passed_mask[sq]|=set_file_rank_mask(file  ,-1);
            white_passed_mask[sq]|=set_file_rank_mask(file-1,-1);
            for(int r=0;r<=rank;r++){
                white_passed_mask[sq]&=(~rank_mask[r*8+file]);
            }
        }
    }
    for(int rank=0;rank<8;rank++){
        for(int file=0;file<8;file++){
            int sq=8*rank+file;
            black_passed_mask[sq]|=set_file_rank_mask(file+1,-1);
            black_passed_mask[sq]|=set_file_rank_mask(file  ,-1);
            black_passed_mask[sq]|=set_file_rank_mask(file-1,-1);
            for(int r=0;r<(8-rank);r++){
                black_passed_mask[sq]&=(~rank_mask[(7-r)*8+file]);
            }
        }
    }    
}

int evaluate(){
    int score=0;
    U64 bb;
    int piece,sq;
    int double_pawns=0;
    for(int p=White_Pawn;p<=Black_King;p++){
        bb=pos.piece_bb[p];
        piece=p;
        while(bb){
            sq=lsb_index(bb);
            score+=material_score[piece];
            switch(piece){
                case White_Pawn:
                    score+=pawn_score[sq];
                    double_pawns=__builtin_popcountll(pos.piece_bb[White_Pawn]&file_mask[sq]);
                    if(double_pawns>1)score+=double_pawns*double_pawn_penalty;
                    if((pos.piece_bb[White_Pawn]&isolated_mask[sq])==0)score+=isolated_pawn_penalty;
                    if((pos.piece_bb[Black_Pawn]&white_passed_mask[sq])==0)score+=passed_pawn_bonus[sq/8];
                    break;

                case White_Knight:
                    score+=knight_score[sq];
                    break;

                case White_Bishop:
                    score+=bishop_score[sq];
                    score+=__builtin_popcountll((bishop_attacks(sq)&(~pos.colour_bb[White])));
                    break;

                case White_Rook:
                    score+=rook_score[sq];
                    if((pos.piece_bb[White_Pawn]&file_mask[sq])==0)score+=semi_open_file_score;
                    if(((pos.piece_bb[White_Pawn]|pos.piece_bb[Black_Pawn])&file_mask[sq])==0)score+=open_file_score;
                    break;

                case White_Queen:
                    score+=__builtin_popcountll((queen_attacks(sq)&(~pos.colour_bb[White])));
                    break;

                case White_King:
                    score+=king_score[sq];
                    if((pos.piece_bb[White_Pawn]&file_mask[sq])==0)score-=semi_open_file_score;
                    if(((pos.piece_bb[White_Pawn]|pos.piece_bb[Black_Pawn])&file_mask[sq])==0)score-=open_file_score;  
                    score+=__builtin_popcountll(king_attacks[sq]&pos.colour_bb[White])*king_shield_bonus;    
                    break;

                case Black_Pawn:
                    score-=pawn_score[mirror_score[sq]];
                    double_pawns=__builtin_popcountll(pos.piece_bb[Black_Pawn]&file_mask[sq]);
                    if(double_pawns>1)score-=double_pawns*double_pawn_penalty;
                    if((pos.piece_bb[Black_Pawn]&isolated_mask[sq])==0)score-=isolated_pawn_penalty;
                    if((pos.piece_bb[White_Pawn]&black_passed_mask[sq])==0)score-=passed_pawn_bonus[mirror_score[sq]/8];
                    break;

                case Black_Knight:
                    score-=knight_score[mirror_score[sq]];
                    break;

                case Black_Bishop:
                    score-=bishop_score[mirror_score[sq]];
                    score-=__builtin_popcountll((bishop_attacks(sq)&(~pos.colour_bb[Black])));
                    break;

                case Black_Rook:
                    score-=rook_score[mirror_score[sq]];
                    if((pos.piece_bb[Black_Pawn]&file_mask[sq])==0)score-=semi_open_file_score;
                    if(((pos.piece_bb[White_Pawn]|pos.piece_bb[Black_Pawn])&file_mask[sq])==0)score-=open_file_score;
                    break;

                case Black_Queen:
                    score-=__builtin_popcountll((queen_attacks(sq)&(~pos.colour_bb[Black])));
                    break;

                case Black_King:
                    score-=king_score[mirror_score[sq]];
                    if((pos.piece_bb[White_Pawn]&file_mask[sq])==0)score+=semi_open_file_score;
                    if(((pos.piece_bb[White_Pawn]|pos.piece_bb[Black_Pawn])&file_mask[sq])==0)score+=open_file_score;
                    score-=__builtin_popcountll(king_attacks[sq]&pos.colour_bb[Black])*king_shield_bonus;                    
                    break;
            }
            pop_lsb(&bb);
        }
    }
    return (pos.side_to_move==White)?score:-score;
    // return score;
}