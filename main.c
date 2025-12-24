#include "init.h"
void test_perft() {
    long start = get_time_ms();
    long nodes5 = perft(5);
    long end = get_time_ms();
    // long nodes6 = perft(6);
    // long nodes7 = perft(7);

    // perft_debug(5);
    // printf("Perft(1) = %ld\n", nodes1);
    // printf("Perft(2) = %ld\n", nodes2);
    // printf("Perft(3) = %ld\n", nodes3);
    // printf("Perft(4) = %ld\n", nodes4);
    printf("Perft(5) = %ld\n", nodes5);
    printf("Time: %ld",end-start);
    // printf("Perft(6) = %ld\n", nodes6);
    // printf("Printf(7) = %ld\n", nodes7);
}

int main(){
    const char *fen ="rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8 ";
    init(fen);
    print_position();
    test_perft();    
    // printf("%d\n",evaluate());
}
