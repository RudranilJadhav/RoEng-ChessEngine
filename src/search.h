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

static inline int negamax(int alpha,int beta,int depth){
    
    int score;
    int hash_flag=hash_flag_alpha;
    
    if((ply&&is_repetition())||pos.halfmove>=50)return 0;
    int pv_node=beta-alpha>1;
    if(ply&&(score=read_hash_entry(alpha,beta,depth))!=no_hash_entry&&pv_node==0)return score;

    if((nodes&2047)==0)communicate();
    pv_length[ply] = ply;
    if(depth==0)return quiescence(alpha, beta);
    if(ply>max_ply-1)return evaluate();
    
    nodes++;

    U64 king_bb=pos.side_to_move==White?pos.piece_bb[White_King]:pos.piece_bb[Black_King];
    int king_sq=lsb_index(king_bb);
    
    pos.side_to_move^=1;
    bool is_cheak=is_square_attacked(king_sq);
    pos.side_to_move^=1;
    
    if(is_cheak)depth++;
    int legal_moves=0;
    if(depth>=3&&is_cheak==0&&ply){
        copy_board();
        ply++;
        repetition_index++;
        repetition_table[repetition_index]=pos.hash_key;
        if(pos.ep!=No_SQ)pos.hash_key^= zobrist.zobrist_ep[pos.ep%8];
        pos.ep=No_SQ;
        pos.side_to_move^=1;
        pos.hash_key^=zobrist.zobrist_side;
        score=-negamax(-beta,-beta+1,depth-1-2);
        ply--;
        repetition_index--;
        take_back();
        if(stopped==1)return 0;
        if(score>=beta)return beta;
    }
    int movelist[256];
    int movecount=generate_legal_moves(movelist);
    if(follow_pv)enable_pv_scoring(movelist,movecount);
    sort_moves(movelist,movecount);
    int moves_searched=0;
    for(int count=0;count<movecount;count++){
        // copy_board(); // REMOVED: redundant and dangerous with make_move
        ply++;
        repetition_index++;
        repetition_table[repetition_index]=pos.hash_key;
        
        make_move(movelist[count]);
        
        legal_moves++;
        if(moves_searched==0){
            score=-negamax(-beta,-alpha,depth-1);
        }
        else{
            if(
                moves_searched>=full_depth_moves&&
                depth>=reduction_limit&&
                is_cheak==0&&
                is_capture(movelist[count])==0&&
                is_promotion(movelist[count])==0
            )   
                score=-negamax(-alpha-1,-alpha,depth-2);
            else  score=alpha+1;

            if(score>alpha){
                score=-negamax(-alpha-1,-alpha,depth-1);
                if((score>alpha)&&(score<beta)){
                    score=-negamax(-beta,-alpha,depth-1);
                }
            }
        }
        ply--;
        repetition_index--;
        
        undo_move(); // CHANGED: from take_back() to undo_move()
        
        if(stopped==1)return 0;
        moves_searched++;
        if(score>alpha){
            hash_flag=hash_flag_exact;
            if(is_capture(movelist[count])==0){
                int piece = pos.squares[From(movelist[count])];
                int to = To(movelist[count]);
                history_moves[piece][to] += depth;
            }
            alpha=score;
            pv_table[ply][ply]=movelist[count];
            for(int next_ply=ply+1;next_ply<pv_length[ply+1];next_ply++)
                pv_table[ply][next_ply] = pv_table[ply + 1][next_ply];
            pv_length[ply] = pv_length[ply + 1];
            if(score>=beta){
                write_hash_entry(beta, depth, hash_flag_beta);
                if(is_capture(movelist[count])==0){
                    killer_moves[1][ply] = killer_moves[0][ply];
                    killer_moves[0][ply] = movelist[count];
                }
                return beta;
            }
        }
    }
    if(legal_moves==0){
        if(is_cheak) return -mate_value+ply;
        else return 0;
    }
    write_hash_entry(alpha, depth, hash_flag);
    return alpha;
}

void search_position(int depth);

#endif
