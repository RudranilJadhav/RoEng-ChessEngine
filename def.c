#include "def.h"

Position pos;
History history;
Zobrist zobrist;
const char START_FEN[]="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
U64 knight_attacks[64];
U64 king_attacks[64];
const int rook_directions[4]={-1,-8,8,1};
const int bishop_directions[4]={-9,-7,7,9};
const int knight_directions_x[8]={-2,-2,-1,-1, 1,1, 2,2};
const int knight_directions_y[8]={-1, 1,-2, 2,-2,2,-1,1};
const int material_score[13]={
    0,        // empty sq
    100,      // white pawn 
    300,      // white knight scrore
    350,      // white bishop score
    500,      // white rook score
   1000,      // white queen score
  10000,      // white king score
   -100,      // black pawn score
   -300,      // black knight scrore
   -350,      // black bishop score
   -500,      // black rook score
  -1000,      // black queen score
 -10000,      // black king score
};
const int pawn_score[64] = 
{
     0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   0, -10, -10,   0,   0,   0,
     0,   0,   0,   5,   5,   0,   0,   0,
     5,   5,  10,  20,  20,   5,   5,   5,
    10,  10,  10,  20,  20,  10,  10,  10,
    20,  20,  20,  30,  30,  30,  20,  20,
    30,  30,  30,  40,  40,  30,  30,  30,
    90,  90,  90,  90,  90,  90,  90,  90
};
const int knight_score[64] = 
{
    -5, -10,   0,   0,   0,   0, -10,  -5,
    -5,   0,   0,   0,   0,   0,   0,  -5,
    -5,   5,  20,  10,  10,  20,   5,  -5,
    -5,  10,  20,  30,  30,  20,  10,  -5,
    -5,  10,  20,  30,  30,  20,  10,  -5,
    -5,   5,  20,  20,  20,  20,   5,  -5,
    -5,   0,   0,  10,  10,   0,   0,  -5,
    -5,   0,   0,   0,   0,   0,   0,  -5
};
const int bishop_score[64] = 
{
     0,   0, -10,   0,   0, -10,   0,   0,
     0,  30,   0,   0,   0,   0,  30,   0,
     0,  10,   0,   0,   0,   0,  10,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,  20,   0,  10,  10,   0,  20,   0,
     0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   0,   0,   0,   0,   0,   0
};
const int rook_score[64] =
{
    50,  50,  50,  50,  50,  50,  50,  50,
    50,  50,  50,  50,  50,  50,  50,  50,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,   0,  20,  20,   0,   0,   0
};
const int king_score[64] = 
{
     0,   0,   5,   0, -15,   0,  10,   0,
     0,   5,   5,  -5,  -5,   0,   5,   0,
     0,   0,   5,  10,  10,   5,   0,   0,
     0,   5,  10,  20,  20,  10,   5,   0,
     0,   5,  10,  20,  20,  10,   5,   0,
     0,   5,   5,  10,  10,   5,   5,   0,
     0,   0,   5,   5,   5,   5,   0,   0,
     0,   0,   0,   0,   0,   0,   0,   0
};
const int mirror_score[64] = 
{
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

const int double_pawn_penalty = -10;
const int isolated_pawn_penalty = -10;
const int passed_pawn_bonus[8] = { 0, 10, 30, 50, 75, 100, 150, 200 }; 
const int semi_open_file_score = 10;
const int open_file_score = 15;
const int king_shield_bonus = 5;

U64 file_mask[64];
U64 rank_mask[64];
U64 isolated_mask[64];
U64 white_passed_mask[64];
U64 black_passed_mask[64];

const int mvv_lva[13][13]={
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0, 105, 205, 305, 405, 505, 605, 105, 205, 305, 405, 505, 605,
    0, 104, 204, 304, 404, 504, 604, 104, 204, 304, 404, 504, 604,
    0, 103, 203, 303, 403, 503, 603, 103, 203, 303, 403, 503, 603,
    0, 102, 202, 302, 402, 502, 602, 102, 202, 302, 402, 502, 602,
    0, 101, 201, 301, 401, 501, 601, 101, 201, 301, 401, 501, 601,
    0, 100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600,

    0, 105, 205, 305, 405, 505, 605, 105, 205, 305, 405, 505, 605,
    0, 104, 204, 304, 404, 504, 604, 104, 204, 304, 404, 504, 604,
    0, 103, 203, 303, 403, 503, 603, 103, 203, 303, 403, 503, 603,
    0, 102, 202, 302, 402, 502, 602, 102, 202, 302, 402, 502, 602,
    0, 101, 201, 301, 401, 501, 601, 101, 201, 301, 401, 501, 601,
    0, 100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600
};
int killer_moves[2][max_ply];
int history_moves[12][64];
int pv_length[max_ply];
int pv_table[max_ply][max_ply];
int follow_pv, score_pv;
int ply;
tt hash_table[hash_size];
U64 repetition_table[1000];
int repetition_index;

int quit = 0;
int movestogo = 30;
int movetime = -1;
int time = -1;
int inc = 0;
int starttime = 0;
int stoptime = 0;
int timeset = 0;
int stopped = 0;
U64 nodes;

/**********************************\
 ==================================
 
       Miscellaneous functions
          forked from VICE
         by Richard Allbert
 
 ==================================
\**********************************/

// get time in milliseconds
int get_time_ms()
{
    #ifdef WIN64
        return GetTickCount();
    #else
        struct timeval time_value;
        gettimeofday(&time_value, NULL);
        return time_value.tv_sec * 1000 + time_value.tv_usec / 1000;
    #endif
}

/*

  Function to "listen" to GUI's input during search.
  It's waiting for the user input from STDIN.
  OS dependent.
  
  First Richard Allbert aka BluefeverSoftware grabbed it from somewhere...
  And then Code Monkey King has grabbed it from VICE)
  
*/
  
int input_waiting()
{
    #ifndef WIN32
        fd_set readfds;
        struct timeval tv;
        FD_ZERO (&readfds);
        FD_SET (fileno(stdin), &readfds);
        tv.tv_sec=0; tv.tv_usec=0;
        select(16, &readfds, 0, 0, &tv);

        return (FD_ISSET(fileno(stdin), &readfds));
    #else
        static int init = 0, pipe;
        static HANDLE inh;
        DWORD dw;

        if (!init)
        {
            init = 1;
            inh = GetStdHandle(STD_INPUT_HANDLE);
            pipe = !GetConsoleMode(inh, &dw);
            if (!pipe)
            {
                SetConsoleMode(inh, dw & ~(ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT));
                FlushConsoleInputBuffer(inh);
            }
        }
        
        if (pipe)
        {
           if (!PeekNamedPipe(inh, NULL, 0, NULL, &dw, NULL)) return 1;
           return dw;
        }
        
        else
        {
           GetNumberOfConsoleInputEvents(inh, &dw);
           return dw <= 1 ? 0 : dw;
        }

    #endif
}

// read GUI/user input
void read_input()
{
    // bytes to read holder
    int bytes;
    
    // GUI/user input
    char input[256] = "", *endc;

    // "listen" to STDIN
    if (input_waiting())
    {
        // tell engine to stop calculating
        stopped = 1;
        
        // loop to read bytes from STDIN
        do
        {
            // read bytes from STDIN
            bytes=read(fileno(stdin), input, 256);
        }
        
        // until bytes available
        while (bytes < 0);
        
        // searches for the first occurrence of '\n'
        endc = strchr(input,'\n');
        
        // if found new line set value at pointer to 0
        if (endc) *endc=0;
        
        // if input is available
        if (strlen(input) > 0)
        {
            // match UCI "quit" command
            if (!strncmp(input, "quit", 4))
            {
                // tell engine to terminate exacution    
                quit = 1;
            }

            // // match UCI "stop" command
            else if (!strncmp(input, "stop", 4))    {
                // tell engine to terminate exacution
                quit = 1;
            }
        }   
    }
}

// a bridge function to interact between search and GUI input
static void communicate(){
	// if time is up break here
    if(timeset == 1 && get_time_ms() > stoptime) {
		// tell engine to stop calculating
		stopped = 1;
	}
	
    // read GUI input
	read_input();
}
