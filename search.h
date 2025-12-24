#ifndef SEARCH_H
#define SEARCH_H

#include "tt.h"


static inline int quiescence(int alpha, int beta){
    if((nodes&2047)==0)communicate();
    nodes++;
    if(ply>=max_ply)return evaluate();
    int eval=evaluate();
    if(eval>=beta)return beta;
    if(eval>alpha)alpha=eval;

    MOVE move_list[256];
    int move_count = generate_legal_moves(move_list);
    sort_moves(move_list,move_count);   
    for(int i=0;i<move_count;i++){
        if(Move_Type(move_list[i])==Capture||Move_Type(move_list[i])==EnPassant||Move_Type(move_list[i])==PromotionCapture){
            ply++;
            make_move(move_list[i]);
            repetition_index++;
            repetition_table[repetition_index]=pos.hash_key;
            int score=-quiescence(-beta,-alpha);
            ply--;
            repetition_index--;
            undo_move();
            if(stopped==1)return 0;
            if(score>alpha){
                alpha=score;
                if(score>=beta)return beta;
            }
        }
    }
    return alpha;
}


#endif