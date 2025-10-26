#include "def.h"
#include "board.h"
#include "zobrist.h"

Position pos;
Zobrist zobrist;
History history;
int init_squares[64];

int init_squares[64]={
    White_Rook, White_Knight, White_Bishop, White_Queen, White_King, White_Bishop, White_Knight, White_Rook,
    White_Pawn, White_Pawn  , White_Pawn  , White_Pawn , White_Pawn, White_Pawn  , White_Pawn  , White_Pawn,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    Black_Pawn, Black_Pawn  , Black_Pawn  , Black_Pawn , Black_Pawn, Black_Pawn  , Black_Pawn  , Black_Pawn,
    Black_Rook, Black_Knight, Black_Bishop, Black_Queen, Black_King, Black_Bishop, Black_Knight, Black_Rook
};