#include <stdio.h>
#include "Constants.h"
#include "Board.h"
#include "Pieces.h"

void printGameBoard(BOARD *board);
char printPieceType(BOARD *board, int i, int j);
char printPieceColor(BOARD *board, int i, int j);

#ifdef MAIN
int main(void)
{
	BLIST *BoardList = NULL;
	BoardList = InitializeBoard();
	printGameBoard(BoardList -> Last -> Board);
	return 0;
}
#endif

// Prints the chess board in ASCII given the board strucuture
void printGameBoard(BOARD *board)
{
	printf("\n");
	for (int i = 0; i < BOARDSIZE; i++)
	{
		// Prints the numbers on the left side of the board
		printf("%d ", BOARDSIZE - i);
		for (int j = 0; j < BOARDSIZE; j++)
		{
			// Prints the Pieces on the Board
			if (j == 0)
			{
				printf("| %c%c ", printPieceColor(board, j, BOARDSIZE-1-i), printPieceType(board, j, BOARDSIZE-1-i));
			}
			else if (j == BOARDSIZE-1)
			{
				printf("| %c%c ", printPieceColor(board, j, BOARDSIZE-1-i), printPieceType(board, j, BOARDSIZE-1-i));
			}
			else
			{
				printf("| %c%c ", printPieceColor(board, j, BOARDSIZE-1-i), printPieceType(board, j, BOARDSIZE-1-i));
			}
		}
		printf("|\n");	
		printf("   ———————————————————————————————————————\n");
		
	}
	// Prints the letters at the bottom of the board
	for (int i = 0; i < BOARDSIZE; i++)
	{
		printf("    %c", 'A'+i);
	}
	printf("\n");
} 

char printPieceType(BOARD *board, int i, int j)
{
	switch(CheckPieceType(board->squares[i][j]))
	{
	case Pawn:
		return 'P';
		break;
	case Knight:
		return 'N';
		break;
	case Bishop:
		return 'B';
		break;
	case Rook:
		return 'R';
		break;
	case Queen:
		return 'Q';
		break;
	case King:
		return 'K';
		break;
	default:
		return ' ';
	}
}

char printPieceColor(BOARD *board, int i, int j)
{
	switch(CheckPieceColor(board->squares[i][j]))
	{
	case White:
		return 'W';
		break;
	case Black:
		return 'B';
		break;
	default:
		return ' ';
	}
}