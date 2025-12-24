#ifndef DEF_H
#define DEF_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#else
    # include <sys/time.h>
#endif

// Board Macros and Structure
#define Max_Moves 1024

typedef unsigned long long U64;
typedef int MOVE;

#define No_Colour -1
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
#define Black_Pawn 7
#define Black_Knight 8
#define Black_Bishop 9
#define Black_Rook 10
#define Black_Queen 11
#define Black_King 12

#define COLOUR(x) (x<=White_King?(x>=White_Pawn?White:No_Colour):(x<=Black_King?Black:No_Colour))

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
extern const char *SQ[64] ;

#define RANK_1 0x00000000000000FFULL
#define RANK_2 0x000000000000FF00ULL
#define RANK_3 0x0000000000FF0000ULL
#define RANK_4 0x00000000FF000000ULL
#define RANK_5 0x000000FF00000000ULL
#define RANK_6 0x0000FF0000000000ULL
#define RANK_7 0x00FF000000000000ULL
#define RANK_8 0xFF00000000000000ULL

#define FILE_A 0x0101010101010101ULL
#define FILE_B 0x0202020202020202ULL
#define FILE_C 0x0404040404040404ULL
#define FILE_D 0x0808080808080808ULL
#define FILE_E 0x1010101010101010ULL
#define FILE_F 0x2020202020202020ULL
#define FILE_G 0x4040404040404040ULL
#define FILE_H 0x8080808080808080ULL

#define WKCA 1
#define WQCA 2
#define BKCA 4
#define BQCA 8


typedef struct{
    int squares[64];
    int side_to_move;
    int castling;
    int fullmove;
    int halfmove;
    int ep;
    U64 piece_bb[13];
    U64 colour_bb[2];
    U64 both_bb;
    U64 hash_key;
} Position;

typedef struct{
    Position game_state[Max_Moves];
    MOVE moves[Max_Moves];
    int move_count;
} History;

typedef struct{
    U64 zobrist_pieces[13][64];
    U64 zobrist_ep[8];
    U64 zobrist_castling[16];
    U64 zobrist_side;
}Zobrist;

typedef struct
{
    U64 hash_key;
    int depth;
    int flag;
    int score;
} tt;


// Bit Manupulation
#define get_bit(bb,sq) (bb&(1ULL<<sq)?1:0)
static inline int pop_lsb(U64 *bb){int idx=__builtin_ctzll(*bb); *bb&=(*bb-1) ; return idx;}
static inline int bit_count(U64 x){return __builtin_popcountll(x);}
static inline U64 set_bit(U64 bb,int sq){return bb|(1ULL<<sq);}
static inline int lsb_index(U64 bb){return __builtin_ctzll(bb);}

// Random
static inline U64 rand64(){U64 r=0;for(int i=0;i<4;i++){r=(r<<16)|(rand()&0xFFFF);}return r;}

// MOVES MACROS
#define From(move) ((move)&(63))
#define To(move) ((move>>6)&(63))
#define Move_Type(move) ((move>>12)&7)
#define Promo(move) ((move>>15)&15)

#define QuietMove 0
#define Promotion 1 
#define Capture 2
#define EnPassant 3 
#define Castling 4 
#define DoublePawn 5
#define PromotionCapture 6

#define Encode_Move(from,to,movetype,promo) (((from)&63)|((to&63)<<6)|((movetype&7)<<12)|((promo&15)<<15))

#define infinity 50000
#define mate_value 49000
#define mate_score 48000
#define max_ply 64
#define hash_size 800000
#define hash_flag_exact 0
#define hash_flag_alpha 1
#define hash_flag_beta 2
#define no_hash_entry 100000

// Globals
extern Position pos;
extern History history;
extern Zobrist zobrist;
extern const char START_FEN[];
extern U64 knight_attacks[64];
extern U64 king_attacks[64];
extern const int rook_directions[4];
extern const int bishop_directions[4];
extern const int knight_directions_x[8];
extern const int knight_directions_y[8];
extern const int material_score[13];
extern const int pawn_score[64];
extern const int knight_score[64];
extern const int bishop_score[64];
extern const int rook_score[64];
extern const int queen_score[64];
extern const int king_score[64];
extern const int mirror_score[64];
extern const int double_pawn_penalty;
extern const int isolated_pawn_penalty;
extern const int passed_pawn_bonus[8]; 
extern const int semi_open_file_score;
extern const int open_file_score;
extern const int king_shield_bonus;
extern int ply;
extern tt hash_table[hash_size];

extern U64 file_mask[64];
extern U64 rank_mask[64];
extern U64 isolated_mask[64];
extern U64 white_passed_mask[64];
extern U64 black_passed_mask[64];

extern const int mvv_lva[13][13];
extern int killer_moves[2][max_ply];
extern int history_moves[13][64];
extern int pv_length[max_ply];
extern int pv_table[max_ply][max_ply];
extern int follow_pv, score_pv;
extern U64 repetition_table[1000];
extern int repetition_index;


extern int quit;
extern int movestogo;
extern int movetime;
extern int time;
extern int inc;
extern int starttime;
extern int stoptime;
extern int timeset;
extern int stopped;
extern U64 nodes;

int get_time_ms();
int input_waiting();
void read_input();
void communicate();

#endif

