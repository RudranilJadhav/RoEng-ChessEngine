#include "transposition.h"

void clear_hash_table(){
    for(int i=0;i<hash_size;i++){
        hash_table[i].hash_key=0;
        hash_table[i].depth=0;
        hash_table[i].flag=0;
        hash_table[i].score=0;
    }
}
