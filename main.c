#include <stdio.h>
#include <string.h>
#include "board.h"
#include "move.h"
#include "fen.h"

int main() {
    init_board();
    print_position(&pos);
    const char* fen="rnbqkbnr/pppppppp/8/8/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
    fen_to_position(fen);
    print_position(&pos);
    int move=MakeMove(e7,e5,DoublePawn,0);
    make_move(move);
    print_position(&pos);
    undo_move();
    print_position(&pos);

    return 0;
}
