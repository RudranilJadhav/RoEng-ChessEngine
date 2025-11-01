#include "move_gen.h"

int generate_pseudo_legal_moves(Move *move_list){
    int count=0;
    //Knight
    U64 knights=(pos.side_to_move==White?pos.piece_bb[White_Knight]:pos.piece_bb[Black_Knight]);
    while(knights){
        int from=pop_lsb(&knights);
        U64 attacks=knight_attacks[from]&(~pos.colour_bb[pos.side_to_move]);
        while(attacks){
            int to=pop_lsb(&attacks);
            int move_type = (pos.colour_bb[!pos.side_to_move] & (1ULL << to)) ? Capture : QuietMove;
            move_list[count++]=MakeMove(from,to,move_type,0);
        }
    }

    //King
    U64 kings=(pos.side_to_move==White?pos.piece_bb[White_King]:pos.piece_bb[Black_King]);
    while(kings){
        int from=pop_lsb(&kings);
        U64 attacks=king_attacks[from]&(~pos.colour_bb[pos.side_to_move]);
        while(attacks){
            int to=pop_lsb(&attacks);
            int move_type = (pos.colour_bb[!pos.side_to_move]& (1ULL<<to))?Capture:QuietMove;
            move_list[count++]=MakeMove(from,to,move_type,0);
        }
    }
    if(pos.side_to_move==White && pos.castling&0X8 && pos.squares[f1]==Empty && pos.squares[g1]==Empty)move_list[count++]=MakeMove(e1,g1,Castling,0);
    if(pos.side_to_move==White && pos.castling&0X4 && pos.squares[b1]==Empty && pos.squares[c1]==Empty && pos.squares[d1]==Empty)move_list[count++]=MakeMove(e1,c1,Castling,0);
    if(pos.side_to_move==Black && pos.castling&0X2 && pos.squares[f8]==Empty && pos.squares[g8]==Empty)move_list[count++]=MakeMove(e8,g8,Castling,0);
    if(pos.side_to_move==Black && pos.castling&0X1 && pos.squares[b8]==Empty && pos.squares[c8]==Empty && pos.squares[d8]==Empty)move_list[count++]=MakeMove(e8,c8,Castling,0);

    //Pawn
    if(pos.side_to_move==White){
        U64 single_pushes = (pos.piece_bb[White_Pawn]<< 8)&(~pos.both_bb);
        U64 double_pushes = ((single_pushes&RANK_3)<<8)&(~pos.both_bb);
        while(single_pushes){
            int to=pop_lsb(&single_pushes);
            int from=to-8;
            if(to/8==7){
                move_list[count++]=MakeMove(from,to,Promotion,White_Knight);
                move_list[count++]=MakeMove(from,to,Promotion,White_Bishop);
                move_list[count++]=MakeMove(from,to,Promotion,White_Rook);
                move_list[count++]=MakeMove(from,to,Promotion,White_Queen);
            }
            else move_list[count++]=MakeMove(from,to,QuietMove,0);
        }
        while(double_pushes){
            int to=pop_lsb(&double_pushes);
            int from=to-16;
            move_list[count++]=MakeMove(from,to,DoublePawn,0);
        }
        U64 left_attacks  = (pos.piece_bb[White_Pawn]<<7)&(~FILE_A)&pos.colour_bb[Black];
        U64 right_attacks = (pos.piece_bb[White_Pawn]<<9)&(~FILE_H)&pos.colour_bb[Black];
        while(left_attacks){
            int to=pop_lsb(&left_attacks);
            int from=to-7;
            if(to/8==7){
                move_list[count++]=MakeMove(from,to,PromotionCapture,White_Knight);
                move_list[count++]=MakeMove(from,to,PromotionCapture,White_Bishop);
                move_list[count++]=MakeMove(from,to,PromotionCapture,White_Rook);
                move_list[count++]=MakeMove(from,to,PromotionCapture,White_Queen);
            }
            else move_list[count++]=MakeMove(from,to,Capture,0);
        }
        while(right_attacks){
            int to=pop_lsb(&right_attacks);
            int from=to-9;
            if(to/8==7){
                move_list[count++]=MakeMove(from,to,PromotionCapture,White_Knight);
                move_list[count++]=MakeMove(from,to,PromotionCapture,White_Bishop);
                move_list[count++]=MakeMove(from,to,PromotionCapture,White_Rook);
                move_list[count++]=MakeMove(from,to,PromotionCapture,White_Queen);
            }
            else move_list[count++]=MakeMove(from,to,Capture,0);
        }
        if(pos.ep != No_SQ){
            int ep_sq = pos.ep;
            if((ep_sq % 8) != 0 && pos.squares[ep_sq - 9] == White_Pawn) move_list[count++] = MakeMove(ep_sq - 9, ep_sq, EnPassent, 0);
            if((ep_sq % 8) != 7 && pos.squares[ep_sq - 7] == White_Pawn) move_list[count++] = MakeMove(ep_sq - 7, ep_sq, EnPassent, 0);
        }
    }
    else{
        U64 single_pushes = (pos.piece_bb[Black_Pawn]>>8)&(~pos.both_bb);
        U64 double_pushes = ((single_pushes&RANK_6)>>8)&(~pos.both_bb);
        while(single_pushes){
            int to=pop_lsb(&single_pushes);
            int from=to+8;
            if(to/8==0){
                move_list[count++]=MakeMove(from,to,Promotion,Black_Knight);
                move_list[count++]=MakeMove(from,to,Promotion,Black_Bishop);
                move_list[count++]=MakeMove(from,to,Promotion,Black_Rook);
                move_list[count++]=MakeMove(from,to,Promotion,Black_Queen);
            }
            else move_list[count++]=MakeMove(from,to,QuietMove,0);
        }
        while(double_pushes){
            int to=pop_lsb(&double_pushes);
            int from=to+16;
            move_list[count++]=MakeMove(from,to,DoublePawn,0);
        }
        U64 left_attacks  = (pos.piece_bb[Black_Pawn]>>9)&(~FILE_A)&pos.colour_bb[White];
        U64 right_attacks = (pos.piece_bb[Black_Pawn]>>7)&(~FILE_H)&pos.colour_bb[White];
        while(left_attacks){
            int to=pop_lsb(&left_attacks);
            int from=to+9;
            if(to/8==0){
                move_list[count++]=MakeMove(from,to,PromotionCapture,Black_Knight);
                move_list[count++]=MakeMove(from,to,PromotionCapture,Black_Bishop);
                move_list[count++]=MakeMove(from,to,PromotionCapture,Black_Rook);
                move_list[count++]=MakeMove(from,to,PromotionCapture,Black_Queen);
            }
            else move_list[count++]=MakeMove(from,to,Capture,0);
        }
        while(right_attacks){
            int to=pop_lsb(&right_attacks);
            int from=to+7;
            if(to/8==0){
                move_list[count++]=MakeMove(from,to,PromotionCapture,Black_Knight);
                move_list[count++]=MakeMove(from,to,PromotionCapture,Black_Bishop);
                move_list[count++]=MakeMove(from,to,PromotionCapture,Black_Rook);
                move_list[count++]=MakeMove(from,to,PromotionCapture,Black_Queen);
            }
            else move_list[count++]=MakeMove(from,to,Capture,0);
        }
        if(pos.ep != No_SQ){
            int ep_sq = pos.ep;
            if((ep_sq % 8) != 0 && pos.squares[ep_sq + 7] == Black_Pawn) move_list[count++] = MakeMove(ep_sq + 7, ep_sq, EnPassent, 0);
            if((ep_sq % 8) != 7 && pos.squares[ep_sq + 9] == Black_Pawn) move_list[count++] = MakeMove(ep_sq + 9, ep_sq, EnPassent, 0);
        }
    }

    //Rook
    U64 rooks=(pos.side_to_move==White?pos.piece_bb[White_Rook]:pos.piece_bb[Black_Rook]);
    while(rooks){
        int from=pop_lsb(&rooks);
        U64 attacks=rook_attacks(from)&(~pos.colour_bb[pos.side_to_move]);
        while(attacks){
            int to=pop_lsb(&attacks);
            int move_type = (pos.colour_bb[!pos.side_to_move]& (1ULL<<to))?Capture:QuietMove;
            move_list[count++]=MakeMove(from,to,move_type,0);            
        }
    }
    //Bishop
    U64 bishops=(pos.side_to_move==White?pos.piece_bb[White_Bishop]:pos.piece_bb[Black_Bishop]);
    while(bishops){
        int from=pop_lsb(&bishops);
        U64 attacks=bishop_attacks(from)&(~pos.colour_bb[pos.side_to_move]);
        while(attacks){
            int to=pop_lsb(&attacks);
            int move_type = (pos.colour_bb[!pos.side_to_move]& (1ULL<<to))?Capture:QuietMove;
            move_list[count++]=MakeMove(from,to,move_type,0);            
        }
    }
    //Queen
    U64 queens=(pos.side_to_move==White?pos.piece_bb[White_Queen]:pos.piece_bb[Black_Queen]);
    while(queens){
        int from=pop_lsb(&queens);
        U64 attacks=queen_attacks(from)&(~pos.colour_bb[pos.side_to_move]);
        while(attacks){
            int to=pop_lsb(&attacks);
            int move_type = (pos.colour_bb[!pos.side_to_move]& (1ULL<<to))?Capture:QuietMove;
            move_list[count++]=MakeMove(from,to,move_type,0);            
        }
    }
    return count;
}

int generate_legal_moves(Move *legal_moves){
    Move pseudo_moves[256];
    int pseudo_count=generate_pseudo_legal_moves(pseudo_moves);
    int legal_count=0;
    for(int i=0;i<pseudo_count;i++){
        Move move=pseudo_moves[i];
        make_move(move);
        if(legal_move()){  
            legal_moves[legal_count++]=move;
        }
        undo_move();
    }
    return legal_count;
}

bool legal_move(){
    int moved_side=(pos.side_to_move==White)?Black:White;
    int king_square=__builtin_ctzll(pos.piece_bb[moved_side==White?White_King:Black_King]);
    Move last_move=history.move[history.move_count];
    if(MoveType(last_move)!=Castling){
        return !is_square_attacked(king_square, moved_side);
    }
    Square to=To(last_move);
    if(moved_side==White) {
        if(to==c1){
            return !(is_square_attacked(c1, White)||is_square_attacked(d1, White));
        } 
        else{
            return !(is_square_attacked(f1, White)||is_square_attacked(g1, White));
        }
    }
    else{
        if(to==c8){
            return !(is_square_attacked(c8, Black) || is_square_attacked(d8, Black));
        } 
        else{
            return !(is_square_attacked(f8, Black) || is_square_attacked(g8, Black));
        }
    }
}

bool is_squares_attacked(int square,int moved_side){
    U64 attacks=0ULL;
    //knight
    U64 knights=(moved_side==White?pos.piece_bb[White_Knight]:pos.piece_bb[Black_Knight]);
    while(knights){
        int from=pop_lsb(&knights);
        attacks|=knight_attacks[from];
    }
    //king
    U64 kings=(moved_side==White?pos.piece_bb[White_King]:pos.piece_bb[Black_King]);
    while(kings){
        int from=pop_lsb(&kings);
        attacks|=king_attacks[from];
    }
    //Pawn
    if(moved_side==White){
        U64 left_attacks  = (pos.piece_bb[White_Pawn]<<7)&(~FILE_A)&pos.colour_bb[Black];
        U64 right_attacks = (pos.piece_bb[White_Pawn]<<9)&(~FILE_H)&pos.colour_bb[Black];
        attacks=attacks|left_attacks|right_attacks;           
    }
    else{
        U64 left_attacks  = (pos.piece_bb[Black_Pawn]>>9)&(~FILE_A)&pos.colour_bb[White];
        U64 right_attacks = (pos.piece_bb[Black_Pawn]>>7)&(~FILE_H)&pos.colour_bb[White];   
        attacks=attacks|left_attacks|right_attacks;     
    }
    //Rook
    U64 rooks=(moved_side==White?pos.piece_bb[White_Rook]:pos.piece_bb[Black_Rook]);
    while(rooks){
        int from=pop_lsb(&rooks);
        attacks|=(rook_attacks(from)&(~pos.colour_bb[moved_side]));
    }    
    //Bishop
    U64 bishops=(moved_side==White?pos.piece_bb[White_Bishop]:pos.piece_bb[Black_Bishop]);
    while(bishops){
        int from=pop_lsb(&bishops);
        attacks|=(bishop_attacks(from)&(~pos.colour_bb[moved_side]));
    }
    //Queen
    U64 queens=(moved_side==White?pos.piece_bb[White_Queen]:pos.piece_bb[Black_Queen]);
    while(queens){
        int from=pop_lsb(&queens);
        attacks|=(queen_attacks(from)&(~pos.colour_bb[moved_side]));
    }
    return (1ULL<<square&attacks)!=0;
}