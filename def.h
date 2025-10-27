#ifndef DEF_H
#define DEF_H

#define Max_Moves 1024

#define White 0
#define Black 1

#define No_SQ -1
#define Empty 0
#define Pawn 1
#define Knight 2
#define Bishop 3
#define Rook 4
#define Queen 5
#define King 6

#define White_Pawn 1
#define White_Knight 2
#define White_Bishop 3
#define White_Rook 4
#define White_Queen 5
#define White_King 6

#define Black_Pawn 9
#define Black_Knight 10
#define Black_Bishop 11
#define Black_Rook 12
#define Black_Queen 13
#define Black_King 14

#define PIECE(x) ((x)&7)
#define COLOUR(x) ((x)&8)

typedef unsigned long long U64;

typedef enum {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8,
} Square;

typedef struct{
    int squares[64];
    int side_to_move;
    int castling;
    int fullmove;
    int halfmove;
    int ep;
    U64 piece_bb[16];
    U64 colour_bb[2];
    U64 both_bb;
    U64 hash_key;
} Position;


typedef struct{
    int move[Max_Moves];          
    int captured_piece[Max_Moves]; 
    int castling[Max_Moves];      
    int ep[Max_Moves];            
    int halfmove[Max_Moves];      
    U64 hash_key[Max_Moves];   
    int move_count;
} History;

typedef struct{
    U64 zobrist_pieces[16][64];
    U64 zobrist_ep[8];
    U64 zobrist_castling[16];
    U64 zobrist_side;
}Zobrist;

extern Position pos;
extern History history;
extern Zobrist zobrist;
extern int init_squares[64];

#endif