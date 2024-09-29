/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Board.h: Struct + Functionality of Board header file				 */
/*********************************************************************/
#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <assert.h>
#include "Constants.h"
#include "Pieces.h"
// #include "Bot.h"
// #include "Gui.h"

typedef struct BoardList BLIST;
typedef struct BoardEntry BENTRY;
typedef struct Board BOARD;

struct Board{
	int Turn;	/* int to represent current players turn */
	PIECE *squares[BOARDSIZE][BOARDSIZE]; /* An Array 8 x 8 of piece pointers */ 
};

struct BoardEntry{
	BLIST *List;	/* Pointer to BoarList */
	BENTRY *Next;	/* Pointer to next entry in List */
	BENTRY *Prev;   /* Pointer to Previous entry in list */
	BOARD *Board;	/* Pointer to current Board */

};


struct BoardList{
	unsigned int Length; 	/* Length of List */
	BENTRY *First;			/* Pointer to First entry */
	BENTRY *Last;			/* Pointer to last entry */

};

BLIST *CreateBoardList(void); /* Create board List */

BENTRY *CreateBoardEntry(BLIST *BoardList); /* Create board entry */

void AppendBoardEntry(BLIST *BoardList, BENTRY *BoardEntry);	/* append Board Entry to Board List */

void UnAppendBoardEntry(BLIST *BoardList);	/* Unappend Board Entry from list */

BOARD *CreateBoard(BLIST *BoardList, int Turn);	/* Create Board */

void DeleteBoardList(BLIST *BoardList);	/* Delete the Board List */

void DeleteBoardEntry(BENTRY *BoardEntry);	/*Delete the board entry */

void DeleteBoard(BOARD *Board); /* Delete the Board */

void WriteTurn(BOARD *Board, int turn);

int Matching(BOARD *CURBOARD, BOARD *NEXTBOARD); /* Checks if it is matching */

void Duplicate(BOARD *CURBOARD, BOARD *NEXTBOARD);	/* Duplicate the Board */

BLIST *InitializeBoard(void);	/* initialize the chess system */

void ResetList(BLIST *BoardList); /* Reset list back to origional board */
///// Write board entry delete and board delete
#endif
