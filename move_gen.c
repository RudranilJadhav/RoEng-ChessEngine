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
        U64 left_attacks=(((~FILE_A)&(bb))>>9)&pos.colour_bb[White];
        U64 right_attacks=(((~FILE_H)&(bb))>>7)&pos.colour_bb[White];
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
            int from=to+9;
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
    pos.hash_key^=zobrist.zobrist_castling[pos.castling];
    if(pos.ep!=-1)pos.hash_key^=zobrist.zobrist_ep[pos.ep%8];

    pos.squares[from]=Empty;pos.hash_key^=zobrist.zobrist_pieces[moved_piece][from];
    if(captured_piece!=Empty){pos.squares[captured_from]=Empty;pos.hash_key^=zobrist.zobrist_pieces[captured_piece][captured_from];}
    pos.squares[to]=piece_on_to_square;pos.hash_key^=zobrist.zobrist_pieces[piece_on_to_square][to];

    pos.piece_bb[moved_piece]&=~(1LL<<from);
    if(captured_piece!=Empty){pos.piece_bb[captured_piece]&=~(1LL<<captured_from);}
    pos.piece_bb[piece_on_to_square]|=(1LL<<to);

    pos.colour_bb[pos.side_to_move]&=~(1LL<<from);
    pos.colour_bb[pos.side_to_move]|=(1LL<<to);
    if(captured_piece!=Empty)pos.colour_bb[pos.side_to_move^1]&=~(1LL<<captured_from);
    
    if(movetype==Castling){
        if(pos.side_to_move==White&&to==g1){
            pos.squares[h1]=Empty;pos.hash_key^=zobrist.zobrist_pieces[White_Rook][h1];
            pos.squares[f1]=White_Rook;pos.hash_key^=zobrist.zobrist_pieces[White_Rook][f1];

            pos.piece_bb[White_Rook]&=~(1LL<<h1);
            pos.piece_bb[White_Rook]|=(1LL<<f1);

            pos.colour_bb[White]&=~(1LL<<h1);
            pos.colour_bb[White]|=(1LL<<f1);

            pos.castling&=~(WKCA|WQCA);
        }
        if(pos.side_to_move==White&&to==c1){
            pos.squares[a1]=Empty;pos.hash_key^=zobrist.zobrist_pieces[White_Rook][a1];
            pos.squares[d1]=White_Rook;pos.hash_key^=zobrist.zobrist_pieces[White_Rook][d1];

            pos.piece_bb[White_Rook]&=~(1LL<<a1);
            pos.piece_bb[White_Rook]|=(1LL<<d1);

            pos.colour_bb[White]&=~(1LL<<a1);
            pos.colour_bb[White]|=(1LL<<d1);

            pos.castling&=~(WKCA|WQCA);
        }
        if(pos.side_to_move==Black&&to==g8){
            pos.squares[h8]=Empty;pos.hash_key^=zobrist.zobrist_pieces[Black_Rook][h8];
            pos.squares[f8]=Black_Rook;pos.hash_key^=zobrist.zobrist_pieces[Black_Rook][f8];

            pos.piece_bb[Black_Rook]&=~(1LL<<h8);
            pos.piece_bb[Black_Rook]|=(1LL<<f8);

            pos.colour_bb[Black]&=~(1LL<<h8);
            pos.colour_bb[Black]|=(1LL<<f8);

            pos.castling&=~(BKCA|BQCA);
        }
        if(pos.side_to_move==Black&&to==c8){
            pos.squares[a8]=Empty;pos.hash_key^=zobrist.zobrist_pieces[Black_Rook][a8];
            pos.squares[d8]=Black_Rook;pos.hash_key^=zobrist.zobrist_pieces[Black_Rook][d8];

            pos.piece_bb[Black_Rook]&=~(1LL<<a8);
            pos.piece_bb[Black_Rook]|=(1LL<<d8);

            pos.colour_bb[Black]&=~(1LL<<a8);
            pos.colour_bb[Black]|=(1LL<<d8);

            pos.castling&=~(BKCA|BQCA);
        }    
    }
    if(moved_piece==White_King)pos.castling&=~(WKCA|WQCA);
    if(moved_piece==Black_King)pos.castling&=~(BKCA|BQCA);
    if(to==a1||from==a1)pos.castling&=~WQCA;
    if(to==h1||from==h1)pos.castling&=~WKCA;
    if(to==a8||from==a8)pos.castling&=~BQCA;
    if(to==h8||from==h8)pos.castling&=~BKCA;

    pos.hash_key^=zobrist.zobrist_castling[pos.castling];

    pos.both_bb=pos.colour_bb[White]|pos.colour_bb[Black];
    if(movetype==DoublePawn){
        if(pos.side_to_move==White)pos.ep=to-8;
        if(pos.side_to_move==Black)pos.ep=to+8;
        pos.hash_key^=zobrist.zobrist_ep[pos.ep%8];
    }else{
        pos.ep=-1;
    }
    pos.halfmove=(moved_piece==White_Pawn||moved_piece==Black_Pawn||captured_piece!=Empty)?0:pos.halfmove+1;
    pos.fullmove+=(pos.side_to_move==Black?1:0);
    pos.side_to_move^=1;pos.hash_key^=zobrist.zobrist_side;
}

void undo_move(){
    if(history.move_count==0)return;
    history.move_count--;
    pos=history.game_state[history.move_count];
}

int generate_legal_moves(MOVE *legal_moves){
    int movelist[256];
    int move_count=0;
    generate_pseudo_legal_moves(movelist,&move_count);
    int count=0;
    for(int i=0;i<move_count;i++){
        if(Move_Type(movelist[i])==Castling){
            if(is_castling_legal(movelist[i])){
                make_move(movelist[i]);
                legal_moves[count++]=movelist[i];
                undo_move();
            }
        }
        else {
            make_move(movelist[i]);
            if(legal_move()){
                legal_moves[count++]=movelist[i];
            }
            undo_move();
        }
    }
    return count;
}
bool legal_move(){
    int move_played_by=pos.side_to_move^1;
    U64 king_bb=(move_played_by==White)?pos.piece_bb[White_King]:pos.piece_bb[Black_King];
    int king_sq=pop_lsb(&king_bb);
    return !is_square_attacked(king_sq);
}

bool is_castling_legal(MOVE move){
    bool safe = true;
    pos.side_to_move ^= 1;
    int to = To(move);
    
    if(pos.side_to_move == Black) {
        if(is_square_attacked(e1)) safe = false;
        
        if(safe) {
            if(to == g1) { 
                if(is_square_attacked(f1) || is_square_attacked(g1)) safe = false;
            } else if (to == c1) { 
                if(is_square_attacked(d1) || is_square_attacked(c1)) safe = false;
            }
        }
    }else{
        if(is_square_attacked(e8)) safe = false;
        
        if(safe) {
            if(to == g8) {
                if(is_square_attacked(f8) || is_square_attacked(g8)) safe = false;
            } else if (to == c8){
                if(is_square_attacked(d8) || is_square_attacked(c8)) safe = false;
            }
        }
    }
    pos.side_to_move ^= 1;
    return safe;
}

bool is_square_attacked(int square){
    int side = pos.side_to_move;

    if(side == White){
        U64 pawns = pos.piece_bb[White_Pawn];
        U64 pawn_attacks = ((pawns&(~FILE_A))<<7)|((pawns&(~FILE_H))<<9);
        if(pawn_attacks&(1ULL<<square))return true;
    }else{
        U64 pawns = pos.piece_bb[Black_Pawn];
        U64 pawn_attacks = (((pawns)&(~FILE_H))>>7)|((pawns&(~FILE_A))>>9);
        if(pawn_attacks&(1ULL<<square)) return true;
    }

    U64 knights = pos.piece_bb[side == White ? White_Knight : Black_Knight];
    if(knight_attacks[square] & knights) return true;

    U64 king = pos.piece_bb[side == White ? White_King : Black_King];
    if(king_attacks[square] & king) return true;

    U64 bishops_queens = pos.piece_bb[side == White ? White_Bishop : Black_Bishop] 
                       | pos.piece_bb[side == White ? White_Queen : Black_Queen];
    U64 rooks_queens   = pos.piece_bb[side == White ? White_Rook : Black_Rook] 
                       | pos.piece_bb[side == White ? White_Queen : Black_Queen];

    if(bishop_attacks(square) & bishops_queens) return true;
    if(rook_attacks(square) & rooks_queens) return true;

    return false;
}

U64 perft(int depth) {
    if(depth==0)return 1;
    MOVE move_list[256];
    int move_count = generate_legal_moves(move_list);
    long nodes = 0;
    for (int i = 0; i < move_count; i++) {
        make_move(move_list[i]);
        nodes += perft(depth - 1);
        undo_move();
    }
    return nodes;
}

void perft_debug(int depth) {
    if (depth == 0) return;
    MOVE move_list[256];
    U64 sum=0;
    int move_count = generate_legal_moves(move_list);
    for (int i = 0; i < move_count; i++) {
        make_move(move_list[i]);
        U64 nodes = (depth == 1)?1:perft(depth-1);
        undo_move();
        // Print move and node count for debugging
        sum+=nodes;
        char p=piece_to_char(Promo(move_list[i]));
        if(p=='.') printf("%s %s %llu\n", SQ[From(move_list[i])], SQ[To(move_list[i])], nodes);
        else printf("%s %s %c %llu\n", SQ[From(move_list[i])], SQ[To(move_list[i])],p,nodes);
    }
    printf("%llu \n",sum);
}