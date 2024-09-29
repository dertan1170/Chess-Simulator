/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Rules.c: Chess Rules function definitons				  			 */
/*********************************************************************/
#include "Rules.h"

LastMove lastMove;

// Helper function to check if a square is within board bounds
int isInBounds(int x, int y) {
    return x >= 0 && x < BOARDSIZE && y >= 0 && y < BOARDSIZE; // if the values inputted are within the board
}

// Helper function to check path is clear for line moves (Rooks, Queens)
int isPathClear(BOARD *board, int startX, int startY, int endX, int endY) {
    int stepX = (endX > startX) - (endX < startX); // if endx greater moving right, if endx less moving left
    int stepY = (endY > startY) - (endY < startY); // if endy greater move up, if endy less move up
    int x, y;
    for (x = startX + stepX, y = startY + stepY; x != endX || y != endY; x += stepX, y += stepY) { // iterate each square until we get to the ending move square (increments by 1 or -1 depending on step x or step y)
        if (board->squares[x][y] != NULL) {
            return 0; // Path is not clear
        }
    }
    return 1;
}

// helper function for updating the last move made for piece (mainly for pawn)
void updateLastMove(LastMove *lastMove, int startX, int startY, int endX, int endY, int pieceMoved, int pieceCaptured, int wasPawnDoubleStep) {
    lastMove->startX = startX; // set last moves to current move made for x
    lastMove->startY = startY; // set last moves to ocurrent move made for y 
    lastMove->endX = endX; // set last moves ending to current ending 
    lastMove->endY = endY; // set last move ending to current ending
    lastMove->pieceMoved = pieceMoved;
    lastMove->pieceCaptured = pieceCaptured;
    lastMove->wasPawnDoubleStep = wasPawnDoubleStep;
}

int isPawnMoveLegal(PIECE *piece, int startX, int startY, int endX, int endY, BOARD *board, LastMove *lastMove) {
    
    int direction = (piece->color == White) ? 1 : -1; // if its white it moves up, if black moves down
    int initialRow = (piece->color == White) ? 1 : 6; // starting row is 1 (indexed with 0) for white, 6 for black 
    int enPassantRow = (piece->color == White) ? 4 : 3; // white can do enpassant to black solely on row 4 (indexed 0) cause double move from 6 goes to 4 

    // Single step forward
    if (startX == endX && board->squares[endX][endY] == NULL) {
        if (startY + direction == endY) {
            return 1;
        }
        // Double step from initial position
        if (startY == initialRow && startY + 2 * direction == endY && board->squares[startX][startY + direction] == NULL) {
            lastMove->wasPawnDoubleStep = 1;  // Mark this move as a double step for en passant
            return 1;
        }
    }

    // Capturing moves
    if (abs(endX - startX) == 1 && startY + direction == endY) { // if the x position is moving left or right 
        if (board->squares[endX][endY] != NULL && board->squares[endX][endY]->color != piece->color) {
            return 1;
        }
        // En Passant capture
        if (startY == enPassantRow && lastMove->wasPawnDoubleStep && // if we are starting our move on the enpassant row, and the opposing pawn move was double stepped
            lastMove->endX == endX && lastMove->endY == startY) { // if the opposing pawns last move's column is the same as current pawn's column that is ATTEMPTING to go to, and if the the opposing pawns ending row of last move is the same row as the current pawns row
            removePiece(board, endX, startY);  // Execute en passant capture (executing here cause remove piece in make move function checks if ending square is not null)
            return 1;
        }
    }
    return 0;
}



// checks for if the move is legal
int isMoveLegal(PIECE *piece, int startX, int startY, int endX, int endY, BOARD *board, LastMove *lastMove) {
    assert(piece && board);

    if (!isInBounds(endX, endY) || (board->squares[endX][endY] && board->squares[endX][endY]->color == piece->color)) { // checks if move is in bounds
        return 0;
    }

    if (piece->type == King && abs(startX - endX) == 2 && startY == endY) {
        // Castling attempt
        int rookX = (endX == 6) ? 7 : 0; // if king is not moving to the right side castle then its trying to move to the left side
        int rookY = startY; // the rooks y should be the same as the starting position y for the king
        return canPerformCastling(board, piece->color, startX, startY, rookX, rookY);
    }
    
    switch (piece->type) {
        case Pawn:
            // Pawn specific move validation
            return isPawnMoveLegal(piece, startX, startY, endX, endY, board, lastMove);
        case Knight:
            // Knight move validation
            return (((abs(endX - startX) == 2 && abs(endY - startY) == 1) || 
                     (abs(endX - startX) == 1 && abs(endY - startY) == 2)) &&
                    (board->squares[endX][endY] == NULL || board->squares[endX][endY]->color != piece->color)); // doesnt use path clear cause knight jumps
        case Bishop:
            // Bishop move validation
            return (abs(endX - startX) == abs(endY - startY) && isPathClear(board, startX, startY, endX, endY));
        case Rook:
            // Rook move validation
            return ((startX == endX || startY == endY) && isPathClear(board, startX, startY, endX, endY));
        case Queen:
            // Queen move validation
            return (isPathClear(board, startX, startY, endX, endY) &&
                    (abs(endX - startX) == abs(endY - startY) || startX == endX || startY == endY));
        case King:
            // King move validation, including simple one-step move checks
            return (abs(startX - endX) <= 1 && abs(startY - endY) <= 1 &&
                    (board->squares[endX][endY] == NULL || board->squares[endX][endY]->color != piece->color));
        default:
            // If piece type is undefined or not recognized
            return 0;
    }
}

// Helper function to remove a piece from the board
void removePiece(BOARD *board, int x, int y) {

    // Check if there is actually a piece at the given position to be removed.
    if (board->squares[x][y] == NULL) {
        return;
    }

    // Remove the piece by setting the square to NULL.
    board->squares[x][y] = NULL;
    
    // Print a confirmation message.
    printf("Piece removed from position %c%d.\n", x, y + 1);
}


void performCastling(BOARD *board, int kingStartX, int kingStartY, int kingEndX, int kingEndY, int rookStartX, int rookEndX) {
    // Move the king
    board->squares[kingEndX][kingEndY] = board->squares[kingStartX][kingStartY]; // move made for king
    board->squares[kingStartX][kingStartY] = NULL; // clear where it was before

    // Move the rook
    board->squares[rookEndX][kingEndY] = board->squares[rookStartX][kingStartY];
    board->squares[rookStartX][kingStartY] = NULL;
}

int canPerformCastling(BOARD *board, int kingColor, int kingX, int kingY, int rookX, int rookY) {

    // Ensure the King and Rook are present
    if (board->squares[kingX][kingY] == NULL || board->squares[rookX][rookY] == NULL) {
        return 0; // if the selected piece doesnt return value, means no piece, so return 0
    }

    // Ensure correct pieces are attempting to castle
    if (board->squares[kingX][kingY]->type != King || board->squares[rookX][rookY]->type != Rook) {
        return 0; // make sure pieces are actual kings or rooks
    }
    
    // Ensure neither the King nor the Rook has moved
    if (board->squares[kingX][kingY]->hasMoved || board->squares[rookX][rookY]->hasMoved) {
        return 0; // making sure these pieces have not moved
    }

    // Check if the path between the King and the Rook is clear
    int stepX = (rookX > kingX) ? 1 : -1; // if the rook is on the right sidem then king moves right
    for (int currentX = kingX + stepX; currentX != rookX; currentX += stepX) { // iterates through every space between rook and king
        if (board->squares[currentX][kingY] != NULL) { // if theres something on the path it cant castle
            return 0;
        }
        if (isSquareUnderAttack(board, currentX, kingY, kingColor)) { // if the square for that current iteration is under attack, cant be castled
            return 0;
        }
    }

    // Check if the king's final position would be under attack
    if (isSquareUnderAttack(board, kingX + 2 * stepX, kingY, kingColor)) {
        return 0; 
    }

    // If all checks passed, perform the castling move
    return 1;
}

// helper function determining if square is underattack
int isSquareUnderAttack(BOARD *board, int x, int y, int KingColor) {
   LastMove lastMove = {0}; // pass last move being 0
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) { // iterate through all squares
            PIECE *attacker = board->squares[i][j]; 
            if (attacker && attacker->color != KingColor) { // if theres a piece, and the piece is not equal to the kings color
                if (isMoveLegal(attacker, i, j, x, y, board, &lastMove)) { // if the kings position is possible to be reached, then under attack
                    return 1;  // The square is under attack
                }
            }
        }
    }
    return 0;
}

// Function to determine if the king of the specified color is in check
int isKingInCheck(BOARD *board, int KingColor) {
    
   for (int x = 0; x < 8; x++) { 
        for (int y = 0; y < BOARDSIZE; y++) { // iterate through every square
            PIECE *piece = board->squares[x][y];
            if (piece && (piece->type == King) && (piece->color == KingColor)){ // if the piece is king and the color is current player's color
                if (isSquareUnderAttack(board, x, y, KingColor)) { // if the king is under attackm then it is in check
                    return 1;
                }
                break;
            } 
        }
    }
    return 0;
}

int isCheckMate(BOARD *board, int kingColor) {
     // Check if the king is in check
    if (!isKingInCheck(board, kingColor)) {
        return 0; // If not in check, it can't be checkmate
    }
    LastMove lastMove = {0};
    // Try all possible moves for all pieces of the king's color
    for (int x = 0; x < BOARDSIZE; x++) {
        for (int y = 0; y < BOARDSIZE; y++) {
            PIECE *piece = board->squares[x][y];
            if (piece && piece->color == kingColor) { // Check only pieces of the king's color
                for (int dx = 0; dx < BOARDSIZE; dx++) {
                    for (int dy = 0; dy < BOARDSIZE; dy++) {
                        // Check legal move that does not result in self-check
                        if (isMoveLegal(piece, x, y, dx, dy, board, &lastMove) && !isMoveSelfCheck(board, x, y, dx, dy)) {
                            return 0; // Found a legal move that removes check
                            
                        }
                    }
                }
            }
        }
    }
    return 1; // No legal move found, it's a checkmate
}

int isMoveSelfCheck(BOARD *board, int startX, int startY, int endX, int endY) {
   // Validate bounds and presence of a piece at the starting position
    if (!isInBounds(startX, startY) || !isInBounds(endX, endY) || board->squares[startX][startY] == NULL) { // making sure piece is there
        return 0;
    }

    PIECE *piece = board->squares[startX][startY];
    int kingColor = piece->color;

    // Temporarily make the move
    PIECE *capturedPiece = board->squares[endX][endY];
    board->squares[endX][endY] = piece;
    board->squares[startX][startY] = NULL;

    // Check if this move puts own king in check
    int inCheck = isKingInCheck(board, kingColor);

    // Undo the move
    board->squares[startX][startY] = piece;
    board->squares[endX][endY] = capturedPiece;

    return inCheck;  // Return whether the king is in check after the move
}

// Function to determine if the current game state is a stalemate
int isStalemate(BOARD *board, int playerColor) {
    // Check if the player's king is in check. If the king is in check, it's not a stalemate (could be checkmate instead).
    if (isKingInCheck(board, playerColor)) {
        return 0;  // Not stalemate because the king is in check
    
    }

    // Iterate over all pieces of the playerColor
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            PIECE *piece = board->squares[x][y];
            if (piece && piece->color == playerColor) {
                // Try all possible moves for this piece
                for (int dx = 0; dx < BOARDSIZE; dx++) {
                    for (int dy = 0; dy < BOARDSIZE; dy++) { // iterating through all possible ending moves
                        if (dx == x && dy == y){
                            continue;  // Skip no-move scenario (same end and start)
                        }
                        // Check if the move from (x, y) to (dx, dy) is legal and doesn't put the king in self-check
                        if (isMoveLegal(piece, x, y, dx, dy, board, &lastMove) && !isMoveSelfCheck(board, x, y, dx, dy)) {
                            return 0;  // Found at least one valid move, thus not a stalemate
                            
                        }
                    }
                }
            }
        }
    }
    // No legal moves found and the king is not in check, it's a stalemate
    return 1;
}


// Pawn Promotion
void pawnPromotion(BOARD *board, int x, int y, int newPieceType) {
 PIECE *pawn = board->squares[x][y];
    if (pawn != NULL && pawn->type == Pawn && (y == 0 || y == BOARDSIZE - 1)) { // has the pawn reached the end
        Promote(pawn, newPieceType);  // update the piece type
    }
}

int makeAndValidateMove(BOARD *board, int startX, int startY, int endX, int endY) {
  if (!isInBounds(startX, startY) || !isInBounds(endX, endY)) {
        printf("Move out of bounds.\n");
        return 0;
    }

    PIECE *piece = board->squares[startX][startY];
    if (!piece) {
        printf("No piece at start position.\n");
        return 0;
    }

        if (piece->type == King && (abs(startX - endX) == 2) && startY == endY) {
        // Checking if castling is attempted
        // if moving to x = 2 (indexed 0) then it is attempting castling on left rook side, on right rook-side otherwise
        int rookX = (endX == 2) ? 0 : 7; // Choose the correct rook based on the king's end column
        int rookY = startY; // rooky should be same as king y
        if (canPerformCastling(board, piece->color, startX, startY, rookX, rookY)) {
            int stepX = (rookX > startX) ? 1 : -1;
            performCastling(board, startX, startY, startX + 2 * stepX, startY, rookX, startX + stepX);
            updateLastMove(&lastMove, startX, startY, endX, endY, piece->type, 0, 0); // update the last move
            printf("Castling performed.\n");
            return 1; // return 1 if castling can be performed
        }
        return 0; // Castling conditions not met
    }

    int pieceCaptured = (board->squares[endX][endY] != NULL);
    int wasPawnDoubleStep = (piece->type == Pawn && abs(startY - endY) == 2);


    if (!isMoveLegal(piece, startX, startY, endX, endY, board, &lastMove)) { 
        printf("Move not legal according to rules.\n");
        return 0;
    }

      // If a piece is at the target location, remove it using the removePiece function
    if (board->squares[endX][endY] != NULL) {
        removePiece(board, endX, endY);
    }

    // Perform the move
    board->squares[endX][endY] = piece;
    board->squares[startX][startY] = NULL;
    piece->hasMoved = 1;

    // Update last move details
    updateLastMove(&lastMove, startX, startY, endX, endY, piece->type, pieceCaptured, wasPawnDoubleStep);

    if (isMoveSelfCheck(board, startX, startY, endX, endY)) {
        // Undo the move if it leads to self-check
        board->squares[startX][startY] = board->squares[endX][endY];
        board->squares[endX][endY] = NULL;
        piece->hasMoved = 0;
        printf("Move leads to self-check, undoing.\n");
        return 0;
    }

    if (piece->type == Pawn && (endY == 0 || endY == BOARDSIZE - 1)) {
        pawnPromotion(board, endX, endY, Queen);
        printf("Pawn promoted at (%d, %d).\n", endX, endY);
    }

    printf("Move made successfully from (%c%d) to (%c%d).\n", startX+'A', startY+1, endX+'A', endY+1);
    return 1;
}