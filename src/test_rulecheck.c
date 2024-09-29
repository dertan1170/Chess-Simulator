#include <stdio.h>
#include "Constants.h"
#include "Board.h"
#include "Pieces.h"
#include "Rules.h"

#ifndef TEST_RULESCHECK_C
#define TEST_RULESCHECK_C

//give char out of piece type
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

//char out of piece color
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


//Print Board to Terminal
void printGameBoard(BOARD *board)
{
	// for(int x = 7; x >= 0; x--)
	// {
	// printf("%d | %c%c | %c%c | %c%c | %c%c | %c%c | %c%c | %c%c | %c%c |", 
	// x+1,printPieceColor(board, 0, x), printPieceType(board, 0, x),
	// printPieceColor(board, 1, x), printPieceType(board, 1, x),
	// printPieceColor(board, 2, x), printPieceType(board, 2, x),
	// printPieceColor(board, 3, x), printPieceType(board, 3, x),
	// printPieceColor(board, 4, x), printPieceType(board, 4, x),
	// printPieceColor(board, 5, x), printPieceType(board, 5, x),
	// printPieceColor(board, 6, x), printPieceType(board, 6, x),
	// printPieceColor(board, 7, x), printPieceType(board, 7, x));
	// printf("\n");	
	// printf("   ———————————————————————————————————————\n");
	// }
	// // Prints the letters at the bottom of the board
	// for (int i = 0; i < BOARDSIZE; i++)
	// {
	// 	printf("    %c", 'A'+i);
	// }
	// printf("\n");

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

//Test for Check
int CheckTest(void)
{
	int flag;
	BLIST *BoardList2;
	BOARD *Board;
	BoardList2 = CreateBoardList();
	Board = CreateBoard(BoardList2, 1);

	PIECE  *WR1, *WH1, *WK, *WP1;
	PIECE *BR1, *BB1, *BK;

	WP1 = CreatePiece(1, 1, 1);
	//WP2 = CreatePiece(1, 1, 1);
	//WP3 = CreatePiece(1, 1, 1);
	//WP4 = CreatePiece(1, 1, 1);
	//WP5 = CreatePiece(1, 1, 1);
	//WP6 = CreatePiece(1, 1, 1);
	//WP7 = CreatePiece(1, 1, 1);
	//WP8 = CreatePiece(1, 1, 1);
	
	WR1 = CreatePiece(4, 1, 5);
	//WB1 = CreatePiece(3, 1, 3);
	//WQ = CreatePiece(5, 1, 9);
	WK = CreatePiece(6, 1, 100);
	WH1 = CreatePiece(2, 1, 3);
	//WR2 = CreatePiece(4, 1, 5);
	//WB2 = CreatePiece(3, 1, 3);
	//WH2 = CreatePiece(2, 1, 3);


	//BP1 = CreatePiece(1, 2, 1);
	//BP2 = CreatePiece(1, 2, 1);
	//BP3 = CreatePiece(1, 2, 1);
	//BP4 = CreatePiece(1, 2, 1);
	//BP5 = CreatePiece(1, 2, 1);
	//BP6 = CreatePiece(1, 2, 1);
	//BP7 = CreatePiece(1, 2, 1);
	//BP8 = CreatePiece(1, 2, 1);

	BR1 = CreatePiece(4, 2, 5);
	BB1 = CreatePiece(3, 2, 3);
	//BQ = CreatePiece(5, 2, 9);
	BK = CreatePiece(6, 2, 100);
	//BH1 = CreatePiece(2, 2, 3);
	//BH2 = CreatePiece(2, 2, 3);
	//BR2 = CreatePiece(4, 2, 5);
	//BB2 = CreatePiece(3, 2, 3);

	Board -> squares[0][1] = BB1;
	Board -> squares[5][0] = BR1;
	Board -> squares[1][3] = WH1;
	Board -> squares[2][5] = WR1;
	Board -> squares[3][6] = WP1;

	Board -> squares[4][5] = WK;
	Board -> squares[7][7] = BK;


	printGameBoard(BoardList2 -> First ->Board);
	flag = isKingInCheck(BoardList2 -> First ->Board, BoardList2 ->First -> Board -> Turn);
	if(flag == 1)
	{
		printf("Check full Functionality\n");
	}
	DeleteBoardList(BoardList2);
	return 1;

}

//Test for Checkmate
int CheckMateTest(void)
{
	int flag;
	BLIST *BoardList3;
	BOARD *Board;
	BoardList3 = CreateBoardList();
	Board = CreateBoard(BoardList3, 1);

	PIECE  *WR1, *WH1, *WK;
	PIECE *BP1, *BK;

	//WP1 = CreatePiece(1, 1, 1);
	//WP2 = CreatePiece(1, 1, 1);
	//WP3 = CreatePiece(1, 1, 1);
	//WP4 = CreatePiece(1, 1, 1);
	//WP5 = CreatePiece(1, 1, 1);
	//WP6 = CreatePiece(1, 1, 1);
	//WP7 = CreatePiece(1, 1, 1);
	//WP8 = CreatePiece(1, 1, 1);
	
	WR1 = CreatePiece(4, 1, 5);
	//WB1 = CreatePiece(3, 1, 3);
	//WQ = CreatePiece(5, 1, 9);
	WK = CreatePiece(6, 1, 100);
	WH1 = CreatePiece(2, 1, 3);
	//WR2 = CreatePiece(4, 1, 5);
	//WB2 = CreatePiece(3, 1, 3);
	//WH2 = CreatePiece(2, 1, 3);


	BP1 = CreatePiece(1, 2, 1);
	//BP2 = CreatePiece(1, 2, 1);
	//BP3 = CreatePiece(1, 2, 1);
	//BP4 = CreatePiece(1, 2, 1);
	//BP5 = CreatePiece(1, 2, 1);
	//BP6 = CreatePiece(1, 2, 1);
	//BP7 = CreatePiece(1, 2, 1);
	//BP8 = CreatePiece(1, 2, 1);

	//BR1 = CreatePiece(4, 2, 5);
	//BB1 = CreatePiece(3, 2, 3);
	//BQ = CreatePiece(5, 2, 9);
	BK = CreatePiece(6, 2, 100);
	//BH1 = CreatePiece(2, 2, 3);
	//BH2 = CreatePiece(2, 2, 3);
	//BR2 = CreatePiece(4, 2, 5);
	//BB2 = CreatePiece(3, 2, 3);

	Board -> squares[6][6] = BP1;
	Board -> squares[4][6] = WH1;
	Board -> squares[7][2] = WR1;

	Board -> squares[6][0] = WK;
	Board -> squares[7][6] = BK;


	printGameBoard(BoardList3 -> First ->Board);
	flag = isCheckMate(BoardList3 -> First ->Board, 2);
	if(flag == 1)
	{
		printf("CheckMate full Functionality\n");
	}
	DeleteBoardList(BoardList3);
	return 1;

}

//Test for Stalemate
int StaleMateTest(void)
{
	int flag;
	BLIST *BoardList3;
	BOARD *Board;
	BoardList3 = CreateBoardList();
	Board = CreateBoard(BoardList3, 1);

	PIECE *WK;
	PIECE *BQ, *BK;

	//WP1 = CreatePiece(1, 1, 1);
	//WP2 = CreatePiece(1, 1, 1);
	//WP3 = CreatePiece(1, 1, 1);
	//WP4 = CreatePiece(1, 1, 1);
	//WP5 = CreatePiece(1, 1, 1);
	//WP6 = CreatePiece(1, 1, 1);
	//WP7 = CreatePiece(1, 1, 1);
	//WP8 = CreatePiece(1, 1, 1);
	
	//WR1 = CreatePiece(4, 1, 5);
	//WB1 = CreatePiece(3, 1, 3);
	//WQ = CreatePiece(5, 1, 9);
	WK = CreatePiece(6, 1, 100);
	//WH1 = CreatePiece(2, 1, 3);
	//WR2 = CreatePiece(4, 1, 5);
	//WB2 = CreatePiece(3, 1, 3);
	//WH2 = CreatePiece(2, 1, 3);


	//BP1 = CreatePiece(1, 2, 1);
	//BP2 = CreatePiece(1, 2, 1);
	//BP3 = CreatePiece(1, 2, 1);
	//BP4 = CreatePiece(1, 2, 1);
	//BP5 = CreatePiece(1, 2, 1);
	//BP6 = CreatePiece(1, 2, 1);
	//BP7 = CreatePiece(1, 2, 1);
	//BP8 = CreatePiece(1, 2, 1);

	//BR1 = CreatePiece(4, 2, 5);
	//BB1 = CreatePiece(3, 2, 3);
	BQ = CreatePiece(5, 2, 9);
	BK = CreatePiece(6, 2, 100);
	//BH1 = CreatePiece(2, 2, 3);
	//BH2 = CreatePiece(2, 2, 3);
	//BR2 = CreatePiece(4, 2, 5);
	//BB2 = CreatePiece(3, 2, 3);
	
	Board -> squares[2][3] = BK;
	Board -> squares[0][7] = WK;
	Board -> squares[2][6] = BQ;


	printGameBoard(BoardList3 -> First ->Board);
	flag = isStalemate(BoardList3 -> First ->Board, BoardList3 -> First -> Board -> Turn);
	if(flag == 1)
	{
		printf("StaleMate full Functionality\n");
	}
	DeleteBoardList(BoardList3);
	return 1;

}

//Test for en passant

//Test for Castleing

//Test to move all Piece Types
int MovePieceTest(void)
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
	Board -> squares[4][0] = WQ; 
	Board -> squares[3][0] = WK; 
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
	printGameBoard(BoardList -> First ->Board);
		
	makeAndValidateMove(BoardList -> First -> Board, 1,0,2,2);
	
	printGameBoard(BoardList -> First ->Board);
	makeAndValidateMove(BoardList -> First -> Board, 0,1,0,2);
	printGameBoard(BoardList -> First ->Board);
	makeAndValidateMove(BoardList -> First -> Board, 0,0,0,1);
	printGameBoard(BoardList -> First ->Board);
	makeAndValidateMove(BoardList -> First -> Board, 3,1,3,2);
	printGameBoard(BoardList -> First ->Board);
	makeAndValidateMove(BoardList -> First -> Board, 2,0,4,2);
	printGameBoard(BoardList -> First ->Board);
	makeAndValidateMove(BoardList -> First -> Board, 3,0,3,1);
	printGameBoard(BoardList -> First ->Board);
	makeAndValidateMove(BoardList -> First -> Board, 4,0,3,0);

	printGameBoard(BoardList -> First ->Board);
	printf("Piece Movement full Functionality\n");
	DeleteBoardList(BoardList);
	return 1;

}

int main()
{
	MovePieceTest();
	//CheckTest();
	//CheckMateTest();
	//StaleMateTest();
}

#endif
