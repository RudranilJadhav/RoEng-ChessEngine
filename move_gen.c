#include "move_gen.h"

void generate_pseudo_legal_moves(MOVE *move_list,int *count){
    generate_pseudo_legal_pawn_moves(move_list,count);
    generate_pseudo_legal_knight_moves(move_list,count);
    generate_pseudo_legal_bishop_moves(move_list,count);
    generate_pseudo_legal_rook_moves(move_list,count);
    generate_pseudo_legal_queen_moves(move_list,count);
    generate_pseudo_legal_king_moves(move_list,count);
}

void generate_pseudo_legal_pawn_moves(MOVE *move_list,int *count){
    if(pos.side_to_move==White){
        U64 bb=pos.piece_bb[White_Pawn];
        U64 empty=~pos.both_bb;
        U64 single_push=(bb<<8)&empty;
        U64 double_push=((single_push&RANK_3)<<8)&empty;
        U64 left_attacks=(((~FILE_A)&(bb))<<7)&pos.colour_bb[Black];
        U64 right_attacks=(((~FILE_H)&(bb))<<9)&pos.colour_bb[Black];
        while(single_push){
            int to=pop_lsb(&single_push);
            int from=to-8;
            int movetype=(to/8==7)?Promotion:QuietMove;
            if(movetype==QuietMove){
                move_list[(*count)++]=Encode_Move(from,to,movetype,0);
            }
            else{
                move_list[(*count)++]=Encode_Move(from,to,movetype,White_Knight); 
                move_list[(*count)++]=Encode_Move(from,to,movetype,White_Bishop);
                move_list[(*count)++]=Encode_Move(from,to,movetype,White_Rook);
                move_list[(*count)++]=Encode_Move(from,to,movetype,White_Queen);
            }
        }
        while(double_push){
            int to=pop_lsb(&double_push);
            int from=to-16;
            move_list[(*count)++]=Encode_Move(from,to,DoublePawn,0);
        }
        while(left_attacks){
            int to=pop_lsb(&left_attacks);
            int from=to-7;
            int movetype=(to/8==7)?PromotionCapture:Capture;
            if(movetype==Capture){
                move_list[(*count)++]=Encode_Move(from,to,movetype,0);
            }
            else{
                move_list[(*count)++]=Encode_Move(from,to,movetype,White_Knight);  
                move_list[(*count)++]=Encode_Move(from,to,movetype,White_Bishop);
                move_list[(*count)++]=Encode_Move(from,to,movetype,White_Rook);
                move_list[(*count)++]=Encode_Move(from,to,movetype,White_Queen);
            }
        }
        while(right_attacks){
            int to=pop_lsb(&right_attacks);
            int from=to-9;
            int movetype=(to/8==7)?PromotionCapture:Capture;
            if(movetype==Capture){
                move_list[(*count)++]=Encode_Move(from,to,movetype,0);
            }
            else{
                move_list[(*count)++]=Encode_Move(from,to,movetype,White_Knight);  
                move_list[(*count)++]=Encode_Move(from,to,movetype,White_Bishop);
                move_list[(*count)++]=Encode_Move(from,to,movetype,White_Rook);
                move_list[(*count)++]=Encode_Move(from,to,movetype,White_Queen);
            }
        }
        if(pos.ep!=-1){
            int to=pos.ep;
            if(to%8>0&&to%8<7){
                if(pos.squares[to-7]==White_Pawn){
                    move_list[(*count)++]=Encode_Move(to-7,to,EnPassant,0);           
                }
                if(pos.squares[to-9]==White_Pawn){
                    move_list[(*count)++]=Encode_Move(to-9,to,EnPassant,0);                
                }
            }
            if(to%8==0){
                if(pos.squares[to-7]==White_Pawn){
                   move_list[(*count)++]=Encode_Move(to-7,to,EnPassant,0);              
                }                
            }
            if(to%8==7){
                if(pos.squares[to-9]==White_Pawn){
                    move_list[(*count)++]=Encode_Move(to-9,to,EnPassant,0);                    
                }                
            }
        }
    }
    else{
        U64 bb=pos.piece_bb[Black_Pawn];
        U64 empty=~pos.both_bb;
        U64 single_push=(bb>>8)&empty;
        U64 double_push=((single_push&RANK_6)>>8)&empty;
        U64 left_attacks=(((~FILE_A)&(bb))<<9)&pos.colour_bb[White];
        U64 right_attacks=(((~FILE_H)&(bb))<<7)&pos.colour_bb[White];
        while(single_push){
            int to=pop_lsb(&single_push);
            int from=to+8;
            int movetype=(to/8==0)?Promotion:QuietMove;
            if(movetype==QuietMove){
                move_list[(*count)++]=Encode_Move(from,to,movetype,0);
            }
            else{
                move_list[(*count)++]=Encode_Move(from,to,movetype,Black_Knight);   
                move_list[(*count)++]=Encode_Move(from,to,movetype,Black_Bishop);
                move_list[(*count)++]=Encode_Move(from,to,movetype,Black_Rook);
                move_list[(*count)++]=Encode_Move(from,to,movetype,Black_Queen);
            }
        }
        while(double_push){
            int to=pop_lsb(&double_push);
            int from=to+16;
           move_list[(*count)++]=Encode_Move(from,to,DoublePawn,0);
        }
        while(left_attacks){
            int to=pop_lsb(&left_attacks);
            int from=to+7;
            int movetype=(to/8==0)?PromotionCapture:Capture;
            if(movetype==Capture){
                move_list[(*count)++]=Encode_Move(from,to,movetype,0);
            }
            else{
                move_list[(*count)++]=Encode_Move(from,to,movetype,Black_Knight);   
                move_list[(*count)++]=Encode_Move(from,to,movetype,Black_Bishop);
                move_list[(*count)++]=Encode_Move(from,to,movetype,Black_Rook);
                move_list[(*count)++]=Encode_Move(from,to,movetype,Black_Queen);
            }
        }
        while(right_attacks){
            int to=pop_lsb(&right_attacks);
            int from=to+7;
            int movetype=(to/8==0)?PromotionCapture:Capture;
            if(movetype==Capture){
                move_list[(*count)++]=Encode_Move(from,to,movetype,0);
            }
            else{
                move_list[(*count)++]=Encode_Move(from,to,movetype,Black_Knight);    
                move_list[(*count)++]=Encode_Move(from,to,movetype,Black_Bishop);
                move_list[(*count)++]=Encode_Move(from,to,movetype,Black_Rook);
                move_list[(*count)++]=Encode_Move(from,to,movetype,Black_Queen);
            }
        }
        if(pos.ep!=-1){
            int to=pos.ep;
            if(to%8>0&&to%8<7){
                if(pos.squares[to+7]==Black_Pawn){
                    move_list[(*count)++]=Encode_Move(to+7,to,EnPassant,0);                 
                }
                if(pos.squares[to+9]==Black_Pawn){
                    move_list[(*count)++]=Encode_Move(to+9,to,EnPassant,0);                   
                }
            }
            if(to%8==0){
                if(pos.squares[to+9]==Black_Pawn){
                    move_list[(*count)++]=Encode_Move(to+9,to,EnPassant,0);               
                }                
            }
            if(to%8==7){
                if(pos.squares[to+7]==Black_Pawn){
                    move_list[(*count)++]=Encode_Move(to+7,to,EnPassant,0);                   
                }                
            }
        }
    }
}

void generate_pseudo_legal_knight_moves(MOVE *move_list,int *count){
    U64 bb=(pos.side_to_move==White)?pos.piece_bb[White_Knight]:pos.piece_bb[Black_Knight];
    while(bb){
        int from=pop_lsb(&bb);
        U64 attacks=(knight_attacks[from])&(~pos.colour_bb[pos.side_to_move]);
        while(attacks){
            int to=pop_lsb(&attacks);
            int movetype=(pos.squares[to]==Empty)?QuietMove:Capture;
            move_list[(*count)++]=Encode_Move(from,to,movetype,0);
        }
    }
}

void generate_pseudo_legal_bishop_moves(MOVE *move_list,int *count){
    U64 bb=(pos.side_to_move==White)?pos.piece_bb[White_Bishop]:pos.piece_bb[Black_Bishop];
    while(bb){
        int from=pop_lsb(&bb);
        U64 attacks=bishop_attacks(from)&(~pos.colour_bb[pos.side_to_move]);
        while(attacks){
            int to=pop_lsb(&attacks);
            int movetype=(pos.squares[to]==Empty)?QuietMove:Capture;
            move_list[(*count)++]=Encode_Move(from,to,movetype,0);            
        }
    }
}

void generate_pseudo_legal_rook_moves(MOVE *move_list,int *count){
    U64 bb=(pos.side_to_move==White)?pos.piece_bb[White_Rook]:pos.piece_bb[Black_Rook];
    while(bb){
        int from=pop_lsb(&bb);
        U64 attacks=rook_attacks(from)&(~pos.colour_bb[pos.side_to_move]);
        while(attacks){
            int to=pop_lsb(&attacks);
            int movetype=(pos.squares[to]==Empty)?QuietMove:Capture;
            move_list[(*count)++]=Encode_Move(from,to,movetype,0);            
        }
    }   
}

void generate_pseudo_legal_queen_moves(MOVE *move_list,int *count){
    U64 bb=(pos.side_to_move==White)?pos.piece_bb[White_Queen]:pos.piece_bb[Black_Queen];
    while(bb){
        int from=pop_lsb(&bb);
        U64 attacks=queen_attacks(from)&(~pos.colour_bb[pos.side_to_move]);
        while(attacks){
            int to=pop_lsb(&attacks);
            int movetype=(pos.squares[to]==Empty)?QuietMove:Capture;
            move_list[(*count)++]=Encode_Move(from,to,movetype,0);            
        }
    }  
}

void generate_pseudo_legal_king_moves(MOVE *move_list,int *count){
    U64 bb=(pos.side_to_move==White)?pos.piece_bb[White_King]:pos.piece_bb[Black_King];
    int from=pop_lsb(&bb);
    U64 attacks=king_attacks[from]&(~pos.colour_bb[pos.side_to_move]);
    while(attacks){
        int to=pop_lsb(&attacks);
        int movetype=(pos.squares[to]==Empty)?QuietMove:Capture;
        move_list[(*count)++]=Encode_Move(from,to,movetype,0);            
    }
    if((pos.castling&WKCA)&&pos.side_to_move==White&&from==e1&&pos.squares[f1]==Empty&&pos.squares[g1]==Empty&&pos.squares[h1]==White_Rook){
        move_list[(*count)++]=Encode_Move(e1,g1,Castling,0);
    }
    if((pos.castling&WQCA)&&pos.side_to_move==White&&from==e1&&pos.squares[d1]==Empty&&pos.squares[c1]==Empty&&pos.squares[b1]==Empty&&pos.squares[a1]==White_Rook){
        move_list[(*count)++]=Encode_Move(e1,c1,Castling,0);
    }
    if((pos.castling&BKCA)&&pos.side_to_move==Black&&from==e8&&pos.squares[f8]==Empty&&pos.squares[g8]==Empty&&pos.squares[h8]==Black_Rook){
        move_list[(*count)++]=Encode_Move(e8,g8,Castling,0);
    }
    if((pos.castling&BQCA)&&pos.side_to_move==Black&&from==e8&&pos.squares[d8]==Empty&&pos.squares[c8]==Empty&&pos.squares[b8]==Empty&&pos.squares[a8]==Black_Rook){
        move_list[(*count)++]=Encode_Move(e8,c8,Castling,0);
    }
}

void make_move(MOVE move){
    history.game_state[history.move_count]=pos;
    history.moves[history.move_count]=move;
    history.move_count++;
    
    int to=To(move);
    int from=From(move);
    int movetype=Move_Type(move);
    int promo=Promo(move);
    int moved_piece=pos.squares[from];
    int piece_on_to_square=(movetype==Promotion||movetype==PromotionCapture)?promo:moved_piece;
    int captured_piece=pos.squares[to];
    int captured_from=to;
    if(movetype==EnPassant){
        captured_piece=(pos.side_to_move==White)?Black_Pawn:White_Pawn;
        captured_from=(pos.side_to_move==White)?to-8:to+8;
    }
 

}

void undo_move(){
    if(history.move_count==0)return;
    history.move_count--;
    pos=history.game_state[history.move_count];
}

int generate_legal_moves(MOVE *legal_moves){

}

bool legal_move(){

}

bool is_square_attacked(int square,int by_side){
    
}

U64 perft(int depth) {
    // if(depth==0)return 1;
    // MOVE move_list[256];
    // int move_count = generate_legal_moves(move_list);
    // long nodes = 0;

    // for (int i = 0; i < move_count; i++) {
    //     make_move(move_list[i]);
    //     nodes += perft(depth - 1);
    //     undo_move();
    // }
    // return nodes;
}
