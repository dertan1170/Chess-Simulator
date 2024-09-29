/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Pieces.c: Struct + Functionality of Pieces definitions  			 */
/*********************************************************************/
#include "Pieces.h"

/* Function to create piece */
PIECE *CreatePiece(int type, int color, int Weight)
{
	/* allocating size of piece */
	PIECE *piece = (PIECE *)malloc(sizeof(PIECE));
	if(piece == NULL)
	{
		return NULL;
	}

	/* assigning values and returning piece pointer */
	piece -> type = type;
	piece -> color = color;
	piece -> weight = Weight;
	piece -> hasMoved = 0;
	
	return piece;
}

/* Function to Delete Piece */
void DeletePiece(PIECE *piece)
{
	/* Checking for all neccesary values */
	assert(piece);
	
	free(piece);
}

/* Function to get piece color */
PieceColor CheckPieceColor(PIECE *piece)
{
	/* check for piece */
	if (!piece)
	{
		return 0;
	}
	return piece -> color;
}

/* Function to get piece type */
PieceType CheckPieceType(PIECE *piece)
{
	/* check for piece */
	if (!piece)
	{
		return 0;
	}
	return piece -> type;
}

/* Funtion returns char given a pieceType*/
char getPieceChar(int pieceType)
{
    switch (pieceType) {
        case Pawn:   return 'P';
        case Knight: return 'N';
        case Bishop: return 'B';
        case Rook:   return 'R';
        case Queen:  return 'Q';
        case King:   return 'K';
        default:     return '?'; // Unknown piece type
    }
}

/* Functiont to check for piece weight */
int CheckPieceWeight(PIECE *piece)
{
	/* Check for piece */
	assert(piece);

	return piece -> weight;
}

/* functing to check for casteling flag */
int SetPieceMoved(PIECE *piece)
{
	assert(piece);

	return piece -> hasMoved;
}

/* Function to promopt piece */
void Promote(PIECE *piece, PieceType type)
{
	/* check for piece */
	assert(piece);

	piece -> type = type;
	return;
}

