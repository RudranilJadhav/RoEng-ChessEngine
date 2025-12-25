#include "init.h"

void init(){
    init_zobrist();
    init_knight_attacks();
    init_king_attacks();
    init_eval_mask();
    clear_hash_table();
    repetition_index=0;
    memset(repetition_table, 0ULL, sizeof(repetition_table));
}

int parse_move(char *move_string){
    int movelist[256];
    int movecount=generate_legal_moves(movelist);
    int ss=(move_string[0]-'a')+(move_string[1]-'0')*8;
    int ts=(move_string[2]-'a')+(move_string[3]-'0')*8;
    for(int count=0;count<movecount;count++){
        if(ss==From(movelist[count])&&ts==To(movelist[count])){
            int p=Promo(movelist[count]);
            if(p){
                if((p==White_Queen||p==Black_Queen)&&move_string[4]=='q')return movelist[count];
                if((p==White_Rook||p==Black_Rook)&&move_string[4]=='r')return movelist[count];
                if((p==White_Bishop||p==Black_Bishop)&&move_string[4]=='b')return movelist[count];
                if((p==White_Knight||p==Black_Knight)&&move_string[4]=='n')return movelist[count];
                continue;
            }
            return movelist[count];
        }
    }
    return 0;
}

void parse_position(char *command){
    command+=9;
    char *current_char = command;
    if(strncmp(command,"startpos",8)==0)fen_to_position(START_FEN);
    else{
        current_char=strstr(command,"fen");
        if(current_char==NULL)fen_to_position(START_FEN);
        else{
            current_char+=4;
            fen_to_position(current_char);
        }
    }
    if(current_char!=NULL){
        current_char+=6;
        while(*current_char){
            int move=parse_move(current_char);
            if(move==0)break;
            repetition_index++;
            repetition_table[repetition_index]=pos.hash_key;
            make_move(move);
            while(*current_char&&*current_char!=' ')current_char++;
            current_char++;
        }
    }
    print_position();
}

void parse_go(char *command){
    int depth = -1;
    char *argument = NULL;
    if ((argument = strstr(command,"infinite"))) {}
    if ((argument = strstr(command,"binc")) && pos.side_to_move == Black)inc = atoi(argument + 5);
    if ((argument = strstr(command,"winc")) && pos.side_to_move == White)inc=atoi(argument+5);
    if ((argument = strstr(command,"wtime")) && pos.side_to_move == White)time = atoi(argument + 6);
    if ((argument = strstr(command,"btime")) && pos.side_to_move==Black)time = atoi(argument + 6);
    if ((argument = strstr(command,"movestogo")))movestogo = atoi(argument + 10);
    if ((argument = strstr(command,"movetime")))movetime = atoi(argument + 9);
    if((argument=strstr(command,"depth"))) depth = atoi(argument + 6);
    if(movetime != -1){
        time = movetime;
        movestogo = 1;
    }
    starttime = get_time_ms();
    depth = depth;
    if(time != -1){
        timeset = 1;
        time /= movestogo;
        if(time>1500)time-=50;
        stoptime = starttime + time + inc;
    }
    if(depth==-1) depth = 12;
    printf("time:%d start:%d stop:%d depth:%d timeset:%d\n",
             time, starttime, stoptime, depth, timeset);
    search_position(depth);
}

void uci_loop(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    char input[2000];
    printf("id name ROENG\n");
    printf("id name V.1.0.0\n");
    printf("uciok\n");
    while(1){
        memset(input, 0, sizeof(input));
        fflush(stdout);
        if (!fgets(input, 2000, stdin))continue;
        if (input[0] == '\n')continue;
        if (strncmp(input, "isready", 7) == 0){
            printf("readyok\n");
            continue;
        }
        else if (strncmp(input, "position", 8) == 0){
            parse_position(input);
            clear_hash_table();
        }
        else if (strncmp(input, "ucinewgame", 10) == 0){
            parse_position("position startpos");
            clear_hash_table();
        }
        else if (strncmp(input, "go", 2) == 0)parse_go(input);
        else if (strncmp(input, "quit", 4) == 0) break;
        else if (strncmp(input, "uci", 3) == 0)
        {
            // print engine info
            printf("id name ROENG\n");
            printf("id name V.1.0.0\n");
            printf("uciok\n");
        }
    }
}