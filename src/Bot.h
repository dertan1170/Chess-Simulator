/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Bot.h: Bot functions header file									 */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "Board.h"
#include "Pieces.h"
#include "Rules.h"
#include "Log.h"

typedef struct {
    int xpos;
    int ypos;
} BOARD_COORDS;

/*
typedef struct {
    int gameover;
    int* get_moves();
    void make_move(int, int);
    void unmake_move();
} BOARD_GAME;
*/

// scan through the board to look for a specific piece
// take in board to scan through
// take in a random piece's number pawn1, knight2, queen1, etc...
// take in a random integer to tell what piece to grab (1st piece it comes across, 2nd, 3rd, and so on)
// take in an array to hold the coordinates
//void scanboard(BOARD *board, int piecetype, int randpiece, int piececoords[2]);
//void scanboard(BOARD *board, int piecetype, int piececoords[2]);
int scanboard(BOARD *board, BOARD_COORDS coords[10], int piecetype);

// bot selects a random pawn to move either one or two spaces, regardless if bot
// moves first (white) or second (black)
//void firstmove(BOARD *board);

// bot calculates all of the possible moves it can make with the peices available
// bot makes a best move using minimax algorithm with depth 1
int botmove(BOARD *board, BLIST *boardlist, FILE *fptr, LastMove *lastMove);

// bot calculates the best move that it can make with the pieces available and 
// the pieces on the enemy's side
// always go for captures and capture highest point piece 
MOVE* bestmove(BOARD *board, int turn, LastMove *lastMove);

int evaluateBoard(BOARD *board, int turn);

void generateAllMoves(BOARD *board, MOVE *moves, int *moveCount, int turn, LastMove *lastMove);