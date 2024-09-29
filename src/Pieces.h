/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Pieces.h: Struct + Functionality of Pieces header file  			 */
/*********************************************************************/
#ifndef PIECES_H
#define PIECES_H

#include <stdlib.h>
#include <assert.h>

// Enumeration for different types of chess pieces.
typedef enum {
    Pawn = 1, Knight, Bishop, Rook, Queen, King
} PieceType;

// Enumeration for piece colors.
typedef enum {
    White = 1, Black
} PieceColor;

// Struct to represent the properties of a chess piece.
typedef struct Piece {
    PieceType type;       // The type of the piece.
    PieceColor color;     // The color of the piece (which player controls it).
    int weight;           // The point value of the piece.
    int hasMoved;         // Flag to indicate if the piece has moved (for castling).
} PIECE;


// Function to create a new piece.
PIECE *CreatePiece(int type, int color, int weight);

// Function to delete a piece.
void DeletePiece(PIECE *piece);

// Function to check the color of a piece.
PieceColor CheckPieceColor(PIECE *piece);

// Function to check the type of a piece.
PieceType CheckPieceType(PIECE *piece);

// Funtion returns char given a pieceType
char getPieceChar(int pieceType);

// Function to check the weight of a piece.
int CheckPieceWeight(PIECE *piece);

// Function to set the 'hasMoved' flag of a piece.
int SetPieceMoved(PIECE *piece);

// Function to promote a piece to a different type.
void Promote(PIECE *piece, PieceType type);

#endif // PIECES_H
