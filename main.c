#include "init.h"

int main(){
    init();
    fen_to_position(START_FEN);
    uci_loop();
    return 0;
}
