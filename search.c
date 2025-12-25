#include "search.h"

void search_position(int depth){
    int score=0;
    nodes=0;
    stopped=0;
    follow_pv=0;
    score_pv=0;
    ply=0; // Reset ply to 0
    memset(killer_moves, 0, sizeof(killer_moves));
    memset(history_moves, 0, sizeof(history_moves));
    memset(pv_table, 0, sizeof(pv_table));
    memset(pv_length, 0, sizeof(pv_length));
    int alpha = -infinity;
    int beta = infinity; 
    for(int current_depth=1;current_depth<=depth;current_depth++){
        if(stopped==1)break;
        follow_pv=1;
        score=negamax(alpha,beta,current_depth);
        if((score<=alpha)||(score>=beta)) {
            alpha = -infinity;    
            beta = infinity;      
            current_depth--; // Retry the same depth with full window
            continue;
        }        
        alpha=score-50;
        beta=score+50;
        if(score>-mate_value&&score<-mate_score){
            printf("info score mate %d depth %d nodes %lld time %d pv ", -(score + mate_value) / 2 - 1, current_depth, nodes, get_time_ms() - starttime);
        }
        else if(score>mate_score&&score<mate_value){
            printf("info score mate %d depth %d nodes %lld time %d pv ", (mate_value - score) / 2 + 1, current_depth, nodes, get_time_ms() - starttime);   
        
        }
        else{
            printf("info score cp %d depth %d nodes %lld time %d pv ", score, current_depth, nodes, get_time_ms() - starttime);
        }
        for(int count = 0; count < pv_length[0]; count++){
            print_move(pv_table[0][count]);
            printf(" ");
        }
    } 
    printf("\n"); 
    printf("bestmove ");
    print_move(pv_table[0][0]);
    printf("\n");   
}
