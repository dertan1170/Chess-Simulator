/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Board.h: Struct + Functionality of Board function defintions		 */
/*********************************************************************/
#include "Board.h"

/* Function to Create Board List */
BLIST *CreateBoardList(void)
{
	BLIST *BoardList;
	BoardList = (BLIST *)malloc(sizeof(BLIST));
	BoardList -> Length = 0;
	BoardList -> First = NULL;
	BoardList -> Last = NULL;
	return BoardList;
}

/* Create Board Entry */
BENTRY *CreateBoardEntry(BLIST *BoardList)
{
	assert(BoardList);

	BENTRY *BoardEntry;
	BoardEntry = (BENTRY *)malloc(sizeof(BENTRY));
	BoardEntry -> List = BoardList;
	BoardEntry -> Prev = NULL;
	BoardEntry -> Next = NULL;
	AppendBoardEntry(BoardList, BoardEntry);
	return BoardEntry;

}

/* Append Board Entry to Board List */
void AppendBoardEntry(BLIST *BoardList, BENTRY *BoardEntry)
{
	assert(BoardList);
	assert(BoardEntry);

	BoardList -> Length = (BoardList -> Length) + 1;
	if(BoardList -> First == NULL)
	{
		BoardList -> First = BoardEntry;
		BoardList -> Last = BoardEntry;
	}
	else
	{
	BoardEntry -> Prev = BoardList-> Last;
	BoardList -> Last -> Next = BoardEntry;
	BoardList -> Last = BoardEntry;
	}

	return;
}

/* Unappend Board Entry from list */
void UnAppendBoardEntry(BLIST *BoardList)
{
	assert(BoardList);
	BENTRY *Prev;

	Prev = BoardList -> Last -> Prev;
	DeleteBoardEntry(BoardList -> Last);

	Prev -> Next = NULL;
	BoardList -> Last = Prev;
	BoardList -> Length = (BoardList -> Length) - 1;
	return;
}

/* Create a Board */
BOARD *CreateBoard(BLIST *BoardList, int Turn)
{
	assert(BoardList);

	BOARD *Board;
	BENTRY *BoardEntry;
	Board = (BOARD *)malloc(sizeof(BOARD));

	Board -> Turn = Turn;
	
	BoardEntry = CreateBoardEntry(BoardList);
	BoardEntry -> Board = Board;

	return Board;
}

/*Delete the BoardList */
void DeleteBoardList(BLIST *BoardList)
{
	assert(BoardList);
	BENTRY *entry, *next;

	entry = BoardList -> First;

	for( int x = 0; x < BOARDSIZE; x++)
	{
		for(int y = 0; y < BOARDSIZE; y++)
		{
			if(entry -> Board -> squares[x][y] != NULL)
			{
				DeletePiece(entry -> Board -> squares[x][y]);
			}
		}
	}

	while(entry != NULL)
	{
		next = entry -> Next;

		DeleteBoard(entry -> Board);
		free(entry);
		entry = next;
	}

	free(BoardList);
	BoardList = NULL;
	return;

}

/* Delete Board Entry */
void DeleteBoardEntry(BENTRY *BoardEntry)
{
	assert(BoardEntry);
	
	DeleteBoard(BoardEntry -> Board);
	free(BoardEntry);
	return;

}

/* Delete Board */
void DeleteBoard(BOARD *Board)
{
	assert(Board);
	free(Board);

}

void WriteTurn(BOARD *Board, int turn)
{
	assert(Board);
	Board -> Turn = turn;
	return;
}

void Duplicate(BOARD *CURBOARD, BOARD *NEXTBOARD)
{
	for(int x = 0; x < BOARDSIZE; x++)
	{
		for(int y = 0; y < BOARDSIZE; y++)
		{
			NEXTBOARD -> squares[x][y] = CURBOARD -> squares[x][y];
		}
	}
	return;

}

/* Checks if the Boards are matching */
// Output: 0 ~ Boards don't match; 1 ~ Boards match
int Matching(BOARD *CURBOARD, BOARD *NEXTBOARD)
{
	for(int x = 0; x < BOARDSIZE; x++)
	{
		for(int y = 0; y < BOARDSIZE; y++)
		{
			if(NEXTBOARD -> squares[x][y] != CURBOARD -> squares[x][y])
			{
				return 0;
			}
		}
	}
	return 1;
}

/* initialize the chess system */
BLIST *InitializeBoard(void)
{
	BLIST *BoardList;
	BOARD *Board;
	BoardList = CreateBoardList();
	Board = CreateBoard(BoardList, 1);

	PIECE *WP1, *WP2, *WP3, *WP4, *WP5, *WP6, *WP7, *WP8;
	PIECE  *WR1, *WR2, *WB1, *WB2, *WH1, *WH2, *WQ, *WK;
	PIECE *BP1, *BP2, *BP3, *BP4, *BP5, *BP6, *BP7, *BP8;
	PIECE *BR1, *BR2, *BB1, *BB2, *BH1, *BH2, *BQ, *BK;

	WP1 = CreatePiece(1, 1, 1);
	WP2 = CreatePiece(1, 1, 1);
	WP3 = CreatePiece(1, 1, 1);
	WP4 = CreatePiece(1, 1, 1);
	WP5 = CreatePiece(1, 1, 1);
	WP6 = CreatePiece(1, 1, 1);
	WP7 = CreatePiece(1, 1, 1);
	WP8 = CreatePiece(1, 1, 1);
	
	WR1 = CreatePiece(4, 1, 5);
	WB1 = CreatePiece(3, 1, 3);
	WQ = CreatePiece(5, 1, 9);
	WK = CreatePiece(6, 1, 100);
	WH1 = CreatePiece(2, 1, 3);
	WR2 = CreatePiece(4, 1, 5);
	WB2 = CreatePiece(3, 1, 3);
	WH2 = CreatePiece(2, 1, 3);


	BP1 = CreatePiece(1, 2, 1);
	BP2 = CreatePiece(1, 2, 1);
	BP3 = CreatePiece(1, 2, 1);
	BP4 = CreatePiece(1, 2, 1);
	BP5 = CreatePiece(1, 2, 1);
	BP6 = CreatePiece(1, 2, 1);
	BP7 = CreatePiece(1, 2, 1);
	BP8 = CreatePiece(1, 2, 1);

	BR1 = CreatePiece(4, 2, 5);
	BB1 = CreatePiece(3, 2, 3);
	BQ = CreatePiece(5, 2, 9);
	BK = CreatePiece(6, 2, 100);
	BH1 = CreatePiece(2, 2, 3);
	BH2 = CreatePiece(2, 2, 3);
	BR2 = CreatePiece(4, 2, 5);
	BB2 = CreatePiece(3, 2, 3);


	Board -> squares[0][0] = WR1; 
	Board -> squares[1][0] = WH1; 
	Board -> squares[2][0] = WB1; 
	Board -> squares[3][0] = WQ; 
	Board -> squares[4][0] = WK; 
	Board -> squares[5][0] = WB2; 
	Board -> squares[6][0] = WH2; 
	Board -> squares[7][0] = WR2;
	Board -> squares[0][1] = WP1; 	
	Board -> squares[1][1] = WP2; 
	Board -> squares[2][1] = WP3; 
	Board -> squares[3][1] = WP4; 
	Board -> squares[4][1] = WP5; 
	Board -> squares[5][1] = WP6; 
	Board -> squares[6][1] = WP7; 
	Board -> squares[7][1] = WP8;

	Board -> squares[0][7] = BR1; 
	Board -> squares[1][7] = BH1; 
	Board -> squares[2][7] = BB1; 
	Board -> squares[3][7] = BQ; 
	Board -> squares[4][7] = BK; 
	Board -> squares[5][7] = BB2; 
	Board -> squares[6][7] = BH2; 
	Board -> squares[7][7] = BR2;
	Board -> squares[0][6] = BP1; 
	Board -> squares[1][6] = BP2; 
	Board -> squares[2][6] = BP3; 
	Board -> squares[3][6] = BP4; 
	Board -> squares[4][6] = BP5; 
	Board -> squares[5][6] = BP6; 
	Board -> squares[6][6] = BP7; 
	Board -> squares[7][6] = BP8; 

	return BoardList;
}

void ResetList(BLIST *BoardList)
{
	BENTRY *entry, *Next;

	entry = BoardList -> First;
	Next = BoardList -> First -> Next;

	BoardList -> Length = 1;
	BoardList -> Last = entry;

	entry -> Next = NULL;

	while(Next != NULL)
	{
		entry = Next;
		Next = entry -> Next;
		DeleteBoardEntry(entry);
	}
	return;
}
