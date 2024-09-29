/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Rules.h: Chess Rules header file						  			 */
/*********************************************************************/
#ifndef RULES_H
#define RULES_H

#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "Board.h"
#include "Pieces.h"

typedef struct{
    int startX;
    int startY;
    int endX;
    int endY;
    int pieceMoved;  // Store the type of piece moved
    int pieceCaptured; // Store the type of piece captured, if any
    int wasPawnDoubleStep; // Specifically for tracking two-square pawn moves
} LastMove;

extern LastMove lastMove;

typedef struct {
    int startX;
    int startY;
    int endX;
    int endY;
} MOVE;

LastMove lastMove;

// Function declarations
// Helper function to check if a square is within board bounds
int isInBounds(int x, int y);
// helper function for updating the last move made for piece
void updateLastMove(LastMove *lastMove, int startX, int startY, int endX, int endY, int pieceMoved, int pieceCaptured, int wasPawnDoubleStep);
int isPawnMoveLegal(PIECE *piece, int startX, int startY, int endX, int endY, BOARD *board, LastMove *lastMove);
// checks for if the move is legal
int isMoveLegal(PIECE *piece, int startX, int startY, int endX, int endY, BOARD *board, LastMove *lastMove);
// Helper function to remove a piece from the board
void removePiece(BOARD *board, int x, int y);
void performCastling(BOARD *board, int kingStartX, int kingStartY, int kingEndX, int kingEndY, int rookStartX, int rookEndX);
int canPerformCastling(BOARD *board, int kingColor, int kingX, int kingY, int rookX, int rookY);
// helper function determining if square is underattack
int isSquareUnderAttack(BOARD *board, int x, int y, int KingColor);
// Function to determine if the king of the specified color is in check
int isKingInCheck(BOARD *board, int KingColor);
int isCheckMate(BOARD *board, int kingColor);
int isMoveSelfCheck(BOARD *board, int startX, int startY, int endX, int endY);
// Function to determine if the current game state is a stalemate
int isStalemate(BOARD *board, int playerColor);
// Pawn Promotion
void pawnPromotion(BOARD *board, int x, int y, int newPieceType);
int makeAndValidateMove(BOARD *board, int startX, int startY, int endX, int endY);

#endif // RULES_H


 