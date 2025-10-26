#include <stdio.h>
#include <string.h>
#include "board.h"
#include "move.h"
#include "fen.h"

int main() {
    init_board();
    print_position(&pos);
    const char* fen="rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2";
    fen_to_position(fen);
    init_bb_by_squares(&pos,pos.squares);
    print_position(&pos);

    return 0;
}
