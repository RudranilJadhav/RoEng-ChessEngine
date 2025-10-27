#ifndef MOVE_H
#define MOVE_H
#include "zobrist.h"

typedef int Move;

#define From(move) ((move)&(63))
#define To(move) ((move>>6)&(63))
#define MoveType(move) ((move>>12)&7)
#define Promo(move) ((move>>15)&7)

#define QuietMove 0
#define Promotion 1 
#define Capture 2
#define EnPassent 3 
#define Castling 4 
#define DoublePawn 5
#define PromotionCapture 6

#define MakeMove(from,to,movetype,promo) ((from&63)|((to&63)<<6)|((movetype&7)<<12)|((promo&7)<<15))
#define IsCapture(move) (MoveType(move)==Capture||MoveType(move)==PromotionCapture)
#define IsPromo(move) (MoveType(move)==Promotion||MoveType(move)==PromotionCapture)

void make_move(Move move);
#endif