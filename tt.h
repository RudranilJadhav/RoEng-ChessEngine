#ifndef TT_H
#define TT_H
#include "eval.h"

void clear_hash_table();

static inline int read_hash_entry(int alpha, int beta, int depth){
    tt *hash_entry=&hash_table[pos.hash_key%hash_size];
    if(hash_entry->hash_key==pos.hash_key){
        if(hash_entry->depth>=depth){
            int score=hash_entry->score;
            if(score<-mate_score)score+=ply;
            if(score>mate_score)score-=ply;
            if(hash_entry->flag==hash_flag_exact)return score;
            if(hash_entry->flag==hash_flag_alpha&&score<=alpha)return alpha;
            if(hash_entry->flag==hash_flag_beta&&score>=beta)return beta;
        }
    }
    return no_hash_entry;
}

static inline void write_hash_entry(int score, int depth, int hash_flag){
    tt *hash_entry=&hash_table[pos.hash_key%hash_size];
    if(score< -mate_score)score-=ply;
    if(score> mate_score)score+=ply;
    hash_entry->hash_key=pos.hash_key;
    hash_entry->score=score;
    hash_entry->flag=hash_flag;
    hash_entry->depth=depth;
}

static inline void enable_pv_scoring(MOVE *move_list,int move_count){
    follow_pv=0;
    for(int i=0;i<move_count;i++){
        if(pv_table[0][ply]==move_list[move_count]){
            follow_pv=1;
            score_pv=1;
        }
    }
}

static inline int score_move(int move){
    if(score_pv){
        if(pv_table[0][ply]==move){score_pv=0;return 20000;}
    }
    if(Move_Type(move)==Capture||Move_Type(move)==PromotionCapture||Move_Type(move)==EnPassant){
        if(Move_Type(move)!=EnPassant){
            return mvv_lva[pos.squares[From(move)]][pos.squares[To(move)]]+10000;
        }
        else{
            return mvv_lva[White_Pawn][Black_Pawn]+10000;
        }
    }
    if(killer_moves[0][ply] == move)return 9000;
    if(killer_moves[1][ply] == move)return 8000;
    return history_moves[pos.squares[From(move)]][To(move)];
}

static inline void sort_moves(MOVE *move_list,int move_count){
    int move_scores[move_count];
    for(int i=0;i<move_count;i++)move_scores[i]=score_move(move_list[i]);
    for(int i=0;i<move_count;i++){
        for(int j=i+1;j<move_count;j++){
            if(move_scores[i]<move_scores[j]){
                int temp=move_scores[i];
                move_scores[i]=move_scores[j];
                move_scores[j]=temp;

                temp=move_list[i];
                move_list[i]=move_list[j];
                move_list[j]=temp;
            }
        }
    }
}

static inline int is_repetition(){
    for(int index=0;index<repetition_index;index++){if(repetition_table[index]==pos.hash_key)return 1;}
    return 0;
}

#endif