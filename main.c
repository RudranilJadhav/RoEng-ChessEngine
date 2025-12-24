#include "init.h"
void test_perft() {
    long nodes1 = perft(1);
    long nodes2 = perft(2);
    long nodes3 = perft(3);
    long nodes4 = perft(4);
    long nodes5 = perft(5);
    // long nodes6 = perft(6);
    // long nodes7 = perft(7);
    printf("Perft(1) = %ld\n", nodes1);
    printf("Perft(2) = %ld\n", nodes2);
    printf("Perft(3) = %ld\n", nodes3);
    printf("Perft(4) = %ld\n", nodes4);
    printf("Perft(5) = %ld\n", nodes5);
    // printf("Perft(6) = %ld\n", nodes6);
    // printf("Printf(7) = %ld\n", nodes7);
}

int main(){
    const char *fen ="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNB1KBNR w KQkq - 0 1";
    init(fen);
    // print_position();
    // test_perft();    
    printf("%d\n",evaluate());
}
