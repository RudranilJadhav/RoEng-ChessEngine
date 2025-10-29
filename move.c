#include "move.h"

void make_move(Move move){
    int from = From(move);
    int to = To(move);
    int promo = Promo(move);
    int piece_moved = pos.squares[from];

    int piece_captured = pos.squares[to];
    int piece_captured_from = to;

    if(MoveType(move)==EnPassent){
        if(pos.side_to_move==White){
            piece_captured=Black_Pawn;
            piece_captured_from=to-8;
        }
        else{
            piece_captured=White_Pawn;
            piece_captured_from=to+8;
        }
    }

    history.move[history.move_count]=move;
    history.castling[history.move_count]=pos.castling;
    history.ep[history.move_count]=pos.ep;
    history.captured_piece[history.move_count]=piece_captured;
    history.halfmove[history.move_count]=pos.halfmove;
    history.hash_key[history.move_count]=pos.hash_key;
    history.move_count++;

    if((piece_moved==White_Rook&&from==a1)||(piece_captured==White_Rook&&to==a1))pos.castling&=(0xB);
    if((piece_moved==White_Rook&&from==h1)||(piece_captured==White_Rook&&to==h1))pos.castling&=(0x7);
    if((piece_moved==Black_Rook&&from==h8)||(piece_captured==Black_Rook&&to==h8))pos.castling&=(0xD);
    if((piece_moved==Black_Rook&&from==a8)||(piece_captured==Black_Rook&&to==a8))pos.castling&=(0xE);
    if(piece_moved==White_King)pos.castling&=(0x3);
    if(piece_moved==Black_King)pos.castling&=(0xC);
    
    pos.squares[piece_captured_from]=Empty;
    pos.squares[to]=(MoveType(move)==Promotion||MoveType(move)==PromotionCapture)?promo:piece_moved;
    pos.squares[from]=Empty;

    pos.piece_bb[piece_moved]&=~(1ULL<<from);
    if(piece_captured!=Empty)pos.piece_bb[piece_captured]&=~(1ULL<<piece_captured_from);
    pos.piece_bb[pos.squares[to]]|=(1ULL<<to);

    pos.colour_bb[COLOUR(piece_moved)]&=~(1ULL<<from);
    if(piece_captured!=Empty)pos.colour_bb[COLOUR(piece_captured)]&=~(1ULL<<piece_captured_from);
    pos.colour_bb[COLOUR(pos.squares[to])]|=(1ULL<<to);

    if(MoveType(move)==DoublePawn){
        if(pos.side_to_move==White)pos.ep=to-8;
        else pos.ep=to+8;
    }
    else{pos.ep=-1;}

    int rook_from=-1;
    int rook_to=-1;
    int rook=(pos.side_to_move==White)?White_Rook:Black_Rook;
    if(MoveType(move)==Castling){
        if(pos.side_to_move==White&&to==c1){rook_from=a1;rook_to=d1;}
        if(pos.side_to_move==White&&to==g1){rook_from=h1;rook_to=f1;}
        if(pos.side_to_move==Black&&to==g8){rook_from=h8;rook_to=f8;}
        if(pos.side_to_move==Black&&to==c8){rook_from=a8;rook_to=d8;}

        if(rook_from!=-1&&rook_to!=-1){
            pos.squares[rook_from]=Empty;
            pos.squares[rook_to]=rook;

            pos.piece_bb[rook]&=~(1ULL<<rook_from);
            pos.piece_bb[rook]|=(1ULL<<rook_to);

            pos.colour_bb[COLOUR(rook)]&=~(1ULL<<rook_from);
            pos.colour_bb[COLOUR(rook)]|=(1ULL<<rook_to);

            if(pos.side_to_move==White)pos.castling&=(0x3);
            else pos.castling&=(0xC);
        }
    }


    pos.both_bb=pos.colour_bb[White]|pos.colour_bb[Black];

    if(pos.side_to_move==Black)pos.fullmove++;
    pos.halfmove=(MoveType(move)==Capture||MoveType(move)==PromotionCapture||piece_moved==White_Pawn||piece_moved==Black_Pawn)?0:pos.halfmove+1;



    pos.hash_key^=zobrist.zobrist_pieces[piece_moved][from];
    if(piece_captured!=Empty)pos.hash_key^=zobrist.zobrist_pieces[piece_captured][piece_captured_from];
    pos.hash_key^=zobrist.zobrist_pieces[pos.squares[to]][to];
    pos.hash_key^=zobrist.zobrist_side;

    if(history.ep[history.move_count-1]!=No_SQ)pos.hash_key^=zobrist.zobrist_ep[(history.ep[history.move_count-1])%8];
    if(pos.ep!=No_SQ)pos.hash_key^=zobrist.zobrist_ep[(pos.ep)%8];

    pos.hash_key^=zobrist.zobrist_castling[history.castling[history.move_count-1]];
    pos.hash_key^=zobrist.zobrist_castling[pos.castling];
    if(MoveType(move)==Castling&&rook_from!=-1&&rook_to!=-1){
        pos.hash_key^=zobrist.zobrist_pieces[rook][rook_from];
        pos.hash_key^=zobrist.zobrist_pieces[rook][rook_to];
    }
    pos.side_to_move^=1;
}

void undo_move(){
    history.move_count--;
    int move=history.move[history.move_count];
    int to=To(move);
    int from=From(move);
    int promo=Promo(move);

    pos.ep=history.ep[history.move_count];
    pos.castling=history.castling[history.move_count];
    pos.halfmove=history.halfmove[history.move_count];
    pos.hash_key=history.hash_key[history.move_count];

    int moved_piece=(MoveType(move)==Promotion||MoveType(move)==PromotionCapture)?(pos.side_to_move==Black?White_Pawn:Black_Pawn):pos.squares[to];

    int piece_captured_from = to;
    if(MoveType(move)==EnPassent){
        piece_captured_from =(pos.side_to_move==Black)?to-8:to+8;
    }
    pos.squares[to]=Empty;
    pos.squares[piece_captured_from]=history.captured_piece[history.move_count];
    pos.squares[from]=moved_piece;


    pos.piece_bb[promo]&=~(1ULL<<to);
    pos.piece_bb[moved_piece]&=~(1ULL<<to);
    pos.piece_bb[moved_piece]|=(1ULL<<from);

    pos.colour_bb[COLOUR(moved_piece)]&=~(1ULL<<to);
    pos.colour_bb[COLOUR(moved_piece)]|=(1ULL<<from);
    if(history.captured_piece[history.move_count]!=Empty){
        pos.piece_bb[history.captured_piece[history.move_count]]|=(1ULL<<piece_captured_from);
        pos.colour_bb[COLOUR(history.captured_piece[history.move_count])]|=(1ULL<<piece_captured_from);
    }

    pos.both_bb=pos.colour_bb[White]|pos.colour_bb[Black];

    if(MoveType(move)==Castling){
        int rook_from=-1, rook_to=-1;
        int rook=(pos.side_to_move==Black)?White_Rook:Black_Rook;
    
        if(pos.side_to_move==Black&&to==c1){rook_from=a1;rook_to=d1;}
        if(pos.side_to_move==Black&&to==g1){rook_from=h1;rook_to=f1;}
        if(pos.side_to_move==White&&to==g8){rook_from=h8;rook_to=f8;}
        if(pos.side_to_move==White&&to==c8){rook_from=a8;rook_to=d8;}
    
        if(rook_from!=-1&&rook_to!=-1){
            pos.squares[rook_from]=rook;
            pos.squares[rook_to]=Empty;
    
            pos.piece_bb[rook]|=(1ULL<<rook_from);
            pos.piece_bb[rook]&=~(1ULL<<rook_to);
    
            pos.colour_bb[COLOUR(rook)]|=(1ULL<<rook_from);
            pos.colour_bb[COLOUR(rook)]&=~(1ULL<<rook_to);
        }
    }
    pos.side_to_move^=1;
    if(pos.side_to_move==Black)pos.fullmove--;
}
