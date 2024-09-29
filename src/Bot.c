/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Bot.h: Bot functions defintions									 */
/*********************************************************************/


#include "Bot.h"



extern void printGameBoard(BOARD *board);


// original scanboard
/*
void scanboard(BOARD *board, int piecetype, int randpiece, int piececoords[2])
{
    // scan through board for a piece
    // randpiece keeps track of what piece number
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board->squares[i][j] != NULL) // check if the square is occupied
            {
                PIECE *boardpiece = board->squares[i][j];

                // check if the piece at the square is the same as the piece we're trying to find, and the same color
                if ((boardpiece->type == piecetype) && (boardpiece->color == board->Turn))
                {
                    randpiece--;

                    if (randpiece != 0)
                    {
                        continue;
                    }
                    else
                    {
                        piececoords[0] = i;
                        piececoords[1] = j;
                        return;
                    }
                }
            }
        }
    }
}*/


// new functionality:
// can scan the board for the total amount of pieces of that type
// once it finds the total amount of that piece, go back, randomly pick one, and find it again
int scanboard(BOARD *board, BOARD_COORDS coords[10], int piecetype) {
    printf("in scanboard\n");
    // scan through board for a piece
    // piececount keeps track of how many of that piece there are
    int piececount = 0;


    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->squares[i][j] != NULL) // check if the square is occupied
            {
                PIECE *boardpiece = board->squares[i][j];

                // check if the piece at the square is the same as the piece we're trying to find, and the same color
                if ((boardpiece->type == piecetype) && (boardpiece->color == board->Turn)) {
                    // if the piece is found, keep track of how many of that type of piece is found
                    piececount++;
                    printf("count: %d\n", piececount);
                    printf("piece at [%d][%d]\n", i, j);

                    coords[piececount].xpos = i;
                    coords[piececount].ypos = j;
                    printf("found coords for piece: [%d][%d]\n", coords[piececount].xpos, coords[piececount].ypos);
                }
            }
        }
    }

    return piececount;
}


// // bot calculates all of the possible moves it can make with the peices available
// // bot makes a best move using minimax algorithm with depth 1
// void botmove(BOARD *board, BLIST *boardlist, FILE *fptr, LastMove *lastMove) {
//     BOARD *NEXTBoard = boardlist->Last->Board;
//
//     BOARD_COORDS coords[10];
//
//
//     // numbers for pieces: 1 - pawn , 2 - knight,  3 - bishop,
//     //                     4 - rook,  5 - queen,   6 - king
//     int randpiece = 0;
//     int MAXpieces = 6;
//     int legalmove = 0;
//     int piecetype = 0;
//     int movelimit = 0;
//     int piececount = 0;
//
//     // set coords
//     int currentx = 0, currenty = 0;
//     int endx = 0, endy = 0;
//
//     int resetflag = 0;
//
//     while (resetflag != 1) {
//         /*
//                if (isCheckMate)
//                {
//                    randpiece = 6;
//                }*/
//         // randomly select a piece to move
//         randpiece = rand() % (MAXpieces + 1);
//         //randpiece = 3;
//
//         switch (randpiece) {
//             case 0:
//             case 1:
//                 // check if out of tries for this
//                 if (movelimit < 0) {
//                     break;
//                 }
//             // set the piece type to 1 for Pawn
//                 piecetype = 1;
//                 printf("piece chosen is pawn\n");
//
//             // set counter to kick out if no valid moves are found
//                 movelimit = 6;
//
//             // scan through the board for that specific piece
//             // scanboard finds all of the possible pieces of that type on the board
//             // then it randomly chooses  piece based on the coords
//                 piececount = scanboard(board, coords, piecetype);
//                 printf("pieces found: %d\n", piececount);
//                 if (piececount == 0) {
//                     break;
//                 }
//
//             // randomly select a piece to move
//             // max = 6 (range from 0 - piececount)
//                 randpiece = rand() % (piececount);
//             // make sure it cant choose 0 for the random piece
//                 if (randpiece == 0) {
//                     randpiece++;
//                 }
//                 printf("random piece selected: %d\n", randpiece);
//
//             // set the coords
//                 currentx = coords[randpiece].xpos;
//                 currenty = coords[randpiece].ypos;
//                 printf("currentx, currenty[%d][%d]\n", currentx, currenty);
//
//
//                 printf("legalmove = %d\n", legalmove);
//
//                 while (legalmove != 1) {
//                     printf("legalmove = %d\n", legalmove);
//                     printf("pisking a direction to move...\n");
//                     // choose to move up or down
//                     //randpawnmove = rand() % 1;
//
//                     // check for the beginning of the match
//                     if (boardlist->Length == 2 || boardlist->Length == 3) {
//                         // set the new coords
//                         endx = currentx;
//
//
//                         if (board->Turn == 1) // move pawn up
//                         {
//                             endy = currenty + (rand() % 2); // choose to move either one or two spaces
//                             endy++; // increment endy so the the range is 1 - 2 instead of 0 - 1
//                         } else // if (board->Turn == 2)
//                         {
//                             endy = currenty - (rand() % 2); // choose to move either one or two spaces
//                             endy--; // increment endy so the the range is 1 - 2 instead of 0 - 1
//                         }
//                     } else // if not the beginning of the match
//                     {
//                         if (board->Turn == 1) // move pawn up
//                         {
//                             // set the new coords
//                             endy = currenty + 1;
//                         } else // if (board->Turn == 2) move the pawn down
//                         {
//                             // set the new coords
//                             endy = currenty - 1;
//                         }
//
//                         // choose move to the left, middle, or right one space
//                         int randy = rand() % 3; // range 0 - 2
//
//
//                         if (randy == 0) {
//                             endx = currentx - 1; // shift x to the left
//                         } else if (randy == 1) {
//                             endx = currentx; // dont shift x, go straight up
//                         } else // if (endy == 2)
//                         {
//                             endx = currentx + 1; // shift x to the right
//                         }
//                     }
//
//                     // check for legal move and can capture the piece
//                     legalmove = makeAndValidateMove(NEXTBoard, currentx, currenty, endx, endy);
//                     // if move made was legal, exit the function
//                     if (legalmove == 1) {
//                         // Checks if there is a checkmate
//                         /*printf("Checking if there's a Checkmate...\n");
//                         if(isKingInCheck(board, boardlist -> Last -> Board -> Turn))
//                         {
//                         printf("checking if king is in check\n"); */
//                         if (isCheckMate(board, ((board->Turn == White) ? Black : White))) {
//                             printf("checking for checkmate\n");
//                             break;
//                         }
//
//                         printf("out of isKingInCheck\n");
//
//                         if (isStalemate(board, board->Turn)) {
//                             printf("check if in stalemate\n");
//                             break;
//                         }
//                         printf("out of isStalemate\n");
//
//                         currentx++;
//                         currenty++;
//                         endx++;
//                         endy++;
//                         WriteMove(boardlist, currentx, currenty, endx, endy, fptr);
//                         return;
//                     }
//
//                     // decrement counter
//                     movelimit--;
//                     printf("movelimit: %d\n", movelimit);
//                     printf("resetflag: %d\n", resetflag);
//
//                     // if counter reaches 0, then the it's on its last chance to choose a random pawn
//                     // if counter is less than zero, then pawn cannot make any more moves
//                     if (movelimit == 0) {
//                         break;
//                     }
//                 }
//             // write move to log
//             //WriteMove(boardlist, currentx, currenty, endx, endy, fptr);
//
//                 break;
//
//             case 2:
//                 // check if out of tries for this
//                 if (movelimit < 0) {
//                     resetflag = 1;
//                     break;
//                 }
//             // set the piece type to 2 for Knight
//                 piecetype = 2;
//                 printf("piece chosen is knight\n");
//
//             // set counter to kick out if no valid moves are found
//                 movelimit = 6;
//
//             // scan through the board for that specific piece
//                 piececount = scanboard(board, coords, piecetype);
//                 printf("pieces found: %d\n", piececount);
//                 if (piececount == 0) {
//                     break;
//                 }
//
//             // randomly select a piece to move
//                 randpiece = rand() % (piececount);
//             // make sure it cant choose 0 for the random piece
//                 if (randpiece == 0) {
//                     randpiece++;
//                 }
//                 printf("random piece selected: %d\n", randpiece);
//
//             // set the coords
//                 currentx = coords[randpiece].xpos;
//                 currenty = coords[randpiece].ypos;
//                 printf("currentx, currenty[%d][%d]\n", currentx, currenty);
//
//
//             /*
//             knight can only move in L's, two in x direction and one in y (either side),
//             or two in y direction and one in y (either side)
//             */
//                 printf("legalmove = %d\n", legalmove);
//                 while (legalmove != 1) {
//                     printf("legalmove = %d\n", legalmove);
//                     printf("pisking a direction to move...\n");
//                     int newposition = rand() % (9);
//
//                     if (newposition == 0) {
//                         endx = currentx + 1;
//                         endy = currenty + 2;
//                     } else if (newposition == 1) {
//                         endx = currentx + 2;
//                         endy = currenty + 1;
//                     } else if (newposition == 2) {
//                         endx = currentx + 2;
//                         endy = currenty - 1;
//                     } else if (newposition == 3) {
//                         endx = currentx + 1;
//                         endy = currenty - 2;
//                     } else if (newposition == 4) {
//                         endx = currentx - 1;
//                         endy = currenty - 2;
//                     } else if (newposition == 5) {
//                         endx = currentx - 2;
//                         endy = currenty - 1;
//                     } else if (newposition == 6) {
//                         endx = currentx - 2;
//                         endy = currenty + 1;
//                     } else // if (newposition == 7)
//                     {
//                         endx = currentx - 1;
//                         endy = currenty + 2;
//                     }
//
//                     // check for legal move and can capture the piece
//                     legalmove = makeAndValidateMove(NEXTBoard, currentx, currenty, endx, endy);
//
//                     if (legalmove == 1) {
//                         currentx++;
//                         currenty++;
//                         endx++;
//                         endy++;
//                         WriteMove(boardlist, currentx, currenty, endx, endy, fptr);
//                         return;
//                     }
//                     // decrement counter
//                     movelimit--;
//                     printf("movelimit: %d\n", movelimit);
//
//                     // if counter reaches 0, then the pawn cannot make any more moves
//                     if (movelimit == 0) {
//                         break;
//                     }
//                 }
//             // write move to log
//             //WriteMove(boardlist, currentx, currenty, endx, endy, fptr);
//
//                 break;
//
//             case 3:
//                 // check if out of tries for this
//                 if (movelimit < 0) {
//                     break;
//                 }
//             // set the piece type to 3 for Bishop
//                 piecetype = 3;
//                 printf("piece chosen is bishop\n");
//
//             // set counter to kick out if no valid moves are found
//                 movelimit = 6;
//
//             // scan through the board for that specific piece
//                 piececount = scanboard(board, coords, piecetype);
//                 printf("pieces found: %d\n", piececount);
//                 if (piececount == 0) {
//                     break;
//                 }
//
//             // randomly select a piece to move
//                 randpiece = rand() % (piececount);
//             // make sure it cant choose 0 for the random piece
//                 if (randpiece == 0) {
//                     randpiece++;
//                 }
//                 printf("random piece selected: %d\n", randpiece);
//
//             // set the coords
//                 currentx = coords[randpiece].xpos;
//                 currenty = coords[randpiece].ypos;
//                 printf("currentx, currenty[%d][%d]\n", currentx, currenty);
//
//
//             /*
//             bishop can only move in diagonal direction, four different paths, up to seven spaces
//             */
//                 printf("legalmove = %d\n", legalmove);
//                 while (legalmove != 1) {
//                     printf("legalmove = %d\n", legalmove);
//                     printf("pisking a direction to move...\n");
//                     // choose a direction
//                     int newposition = rand() % (5);
//                     // choose how far to move in that direction (up to 7 spaces)
//                     int diag = rand() % 8;
//
//                     if (newposition == 0) {
//                         endx = currentx + diag;
//                         endy = currenty + diag;
//                     } else if (newposition == 1) {
//                         endx = currentx + diag;
//                         endy = currenty - diag;
//                     } else if (newposition == 2) {
//                         endx = currentx - diag;
//                         endy = currenty - diag;
//                     } else // if (newposition == 3)
//                     {
//                         endx = currentx - diag;
//                         endy = currenty + diag;
//                     }
//                     printf("endx, endy[%d][%d]\n", endx, endy);
//
//                     // check for legal move and can capture the piece
//                     legalmove = makeAndValidateMove(NEXTBoard, currentx, currenty, endx, endy);
//                     if (legalmove == 1) {
//                         currentx++;
//                         currenty++;
//                         endx++;
//                         endy++;
//                         WriteMove(boardlist, currentx, currenty, endx, endy, fptr);
//                         return;
//                     }
//
//                     // decrement counter
//                     movelimit--;
//
//                     // if counter reaches 0, then the pawn cannot make any more moves
//                     if (movelimit == 0) {
//                         break;
//                     }
//                 }
//             // write move to log
//             //WriteMove(boardlist, currentx, currenty, endx, endy, fptr);
//
//                 break;
//
//             case 4:
//                 // check if out of tries for this
//                 if (movelimit < 0) {
//                     resetflag = 1;
//                     break;
//                 }
//             // set the piece type to 4 for Rook
//                 piecetype = 4;
//                 printf("piece chosen is rook\n");
//
//             // set counter to kick out if no valid moves are found
//                 movelimit = 6;
//
//             // scan through the board for that specific piece
//                 piececount = scanboard(board, coords, piecetype);
//                 printf("pieces found: %d\n", piececount);
//                 if (piececount == 0) {
//                     break;
//                 }
//
//             // randomly select a piece to move
//                 randpiece = rand() % (piececount);
//             // make sure it cant choose 0 for the random piece
//                 if (randpiece == 0) {
//                     randpiece++;
//                 }
//                 printf("random piece selected: %d\n", randpiece);
//
//             // set the coords
//                 currentx = coords[randpiece].xpos;
//                 currenty = coords[randpiece].ypos;
//                 printf("currentx, currenty[%d][%d]\n", currentx, currenty);
//
//
//             /*
//             rook can only move in vertical or horizontal direction, four different paths, up to seven spaces
//             */
//                 printf("legalmove = %d\n", legalmove);
//                 while (legalmove != 1) {
//                     printf("legalmove = %d\n", legalmove);
//                     printf("pisking a direction to move...\n");
//                     // choose a direction
//                     int newposition = rand() % (5);
//                     // choose how far to move in that direction (up to 7 spaces)
//                     int direction = rand() % 8;
//                     // prevent from moving 0 spacces
//                     if (direction == 0) {
//                         direction++;
//                     }
//
//                     if (newposition == 0) {
//                         endx = currentx;
//                         endy = currenty + direction;
//                     } else if (newposition == 1) {
//                         endx = currentx + direction;
//                         endy = currenty;
//                     } else if (newposition == 2) {
//                         endx = currentx;
//                         endy = currenty - direction;
//                     } else // if (newposition == 3)
//                     {
//                         endx = currentx - direction;
//                         endy = currenty;
//                     }
//                     printf("endx, endy[%d][%d]\n", endx, endy);
//
//                     // check for legal move and can capture the piece
//                     legalmove = makeAndValidateMove(NEXTBoard, currentx, currenty, endx, endy);
//                     if (legalmove == 1) {
//                         currentx++;
//                         currenty++;
//                         endx++;
//                         endy++;
//                         WriteMove(boardlist, currentx, currenty, endx, endy, fptr);
//                         return;
//                     }
//
//                     // decrement counter
//                     movelimit--;
//
//                     // if counter reaches 0, then the pawn cannot make any more moves
//                     if (movelimit == 0) {
//                         break;
//                     }
//                 }
//             // write move to log
//             //WriteMove(boardlist, currentx, currenty, endx, endy, fptr);
//
//                 break;
//
//             case 5:
//                 // check if out of tries for this
//                 if (movelimit < 0) {
//                     resetflag = 1;
//                     break;
//                 }
//             // set the piece type to 5 for Queen
//                 piecetype = 5;
//                 printf("piece chosen is queen\n");
//
//             // set counter to kick out if no valid moves are found
//                 movelimit = 10;
//
//             // scan through the board for that specific piece
//                 piececount = scanboard(board, coords, piecetype);
//                 printf("pieces found: %d\n", piececount);
//                 if (piececount == 0) {
//                     break;
//                 }
//
//             // randomly select a piece to move
//                 randpiece = rand() % (piececount);
//             // make sure it cant choose 0 for the random piece
//                 if (randpiece == 0) {
//                     randpiece++;
//                 }
//                 printf("random piece selected: %d\n", randpiece);
//
//             // set the coords
//                 currentx = coords[randpiece].xpos;
//                 currenty = coords[randpiece].ypos;
//                 printf("currentx, currenty[%d][%d]\n", currentx, currenty);
//
//
//             /*
//             queen can only move in same directions as both rook and bishop
//             */
//                 printf("legalmove = %d\n", legalmove);
//                 while (legalmove != 1) {
//                     printf("legalmove = %d\n", legalmove);
//                     printf("pisking a direction to move...\n");
//                     // choose a direction (up to 8 directions)
//                     int newposition = rand() % (9);
//                     // choose how far to move in that direction (up to 7 spaces)
//                     int direction = rand() % 8;
//                     int diag = rand() % 8;
//
//                     if (newposition == 0) {
//                         endx = currentx;
//                         endy = currenty + direction;
//                     } else if (newposition == 1) {
//                         endx = currentx + direction;
//                         endy = currenty;
//                     } else if (newposition == 2) {
//                         endx = currentx;
//                         endy = currenty - direction;
//                     } else if (newposition == 3) {
//                         endx = currentx - direction;
//                         endy = currenty;
//                     } else if (newposition == 4) {
//                         endx = currentx + diag;
//                         endy = currenty + diag;
//                     } else if (newposition == 5) {
//                         endx = currentx + diag;
//                         endy = currenty - diag;
//                     } else if (newposition == 6) {
//                         endx = currentx - diag;
//                         endy = currenty - diag;
//                     } else // if (newposition == 7)
//                     {
//                         endx = currentx - diag;
//                         endy = currenty + diag;
//                     }
//                     printf("endx, endy[%d][%d]\n", endx, endy);
//
//                     // check for legal move and can capture the piece
//                     legalmove = makeAndValidateMove(NEXTBoard, currentx, currenty, endx, endy);
//                     if (legalmove == 1) {
//                         currentx++;
//                         currenty++;
//                         endx++;
//                         endy++;
//                         WriteMove(boardlist, currentx, currenty, endx, endy, fptr);
//                         return;
//                     }
//
//                     // decrement counter
//                     movelimit--;
//
//                     // if counter reaches 0, then the pawn cannot make any more moves
//                     if (movelimit == 0) {
//                         break;
//                     }
//                 }
//             // write move to log
//             //WriteMove(boardlist, currentx, currenty, endx, endy, fptr);
//
//                 break;
//
//             case 6:
//                 // check if out of tries for this
//                 if (movelimit < 0) {
//                     resetflag = 1;
//                     break;
//                 }
//             // set the piece type to 6 for king
//                 piecetype = 6;
//                 printf("piece chosen is king\n");
//
//             // set counter to kick out if no valid moves are found
//                 movelimit = 10;
//
//             // scan through the board for that specific piece
//                 piececount = scanboard(board, coords, piecetype);
//
//             // randomly select a piece to move
//             //randpiece = rand() % (piececount);
//             // make sure it cant choose 0 for the random piece
//             //if (randpiece == 0)
//             //{
//             //    randpiece++;
//             //}
//                 printf("king piece selected: %d\n", piececount);
//
//             // set the coords
//                 currentx = coords[piececount].xpos;
//                 currenty = coords[piececount].ypos;
//                 printf("currentx, currenty[%d][%d]\n", currentx, currenty);
//
//
//             // set counter to kick out if no valid moves are found
//                 movelimit = 10;
//
//             /*
//             king can only move in one space, just in the blocks around him (donut)
//             */
//                 printf("legalmove = %d\n", legalmove);
//                 while (legalmove != 1) {
//                     printf("legalmove = %d\n", legalmove);
//                     printf("pisking a direction to move...\n");
//                     // choose a direction
//                     int newposition = rand() % (9);
//                     // choose how far to move in that direction (can only move up to one space)
//                     //int direction = 1;
//
//                     if (newposition == 0) {
//                         endx = currentx;
//                         endy = currenty + 1;
//                     } else if (newposition == 1) {
//                         endx = currentx + 1;
//                         endy = currenty + 1;
//                     } else if (newposition == 2) {
//                         endx = currentx + 1;
//                         endy = currenty;
//                     } else if (newposition == 3) {
//                         endx = currentx + 1;
//                         endy = currenty - 1;
//                     } else if (newposition == 4) {
//                         endx = currentx;
//                         endy = currenty - 1;
//                     } else if (newposition == 5) {
//                         endx = currentx - 1;
//                         endy = currenty - 1;
//                     } else if (newposition == 6) {
//                         endx = currentx - 1;
//                         endy = currenty;
//                     } else // if (newposition == 7)
//                     {
//                         endx = currentx - 1;
//                         endy = currenty + 1;
//                     }
//                     printf("[%d][%d]\n", endx, endy);
//
//                     // check for legal move and can capture the piece
//                     legalmove = makeAndValidateMove(NEXTBoard, currentx, currenty, endx, endy);
//                     if (legalmove == 1) {
//                         currentx++;
//                         currenty++;
//                         endx++;
//                         endy++;
//                         WriteMove(boardlist, currentx, currenty, endx, endy, fptr);
//                         return;
//                     }
//
//                     // decrement counter
//                     movelimit--;
//
//                     // if counter reaches 0, then the pawn cannot make any more moves
//                     if (movelimit == 0) {
//                         break;
//                     }
//                 }
//             // write move to log
//
//             //WriteMove(boardlist, currentx, currenty, endx, endy, fptr);
//
//                 break;
//
//             default:
//                 printf("Error getting bot move... \n");
//                 break;
//         }
//         //end switch case
//         printf("out of switch case\n");
//     }
//     // end while
//     printf("out of initial while loop\n");
// }


// bot calculates all of the possible moves it can make with the peices available
// bot makes a best move using minimax algorithm with depth 1
int botmove(BOARD *board, BLIST *boardlist, FILE *fptr, LastMove *lastMove) {
    // Announce the current player's turn
    if (board->Turn == 1) {
        printf("White Turn\n");
    } else {
        printf("Black Turn\n");
    }

    // Get the best move for the current player
    MOVE *bestMove = bestmove(board, board->Turn, lastMove);

    // Handle the case where no moves are available
    if (bestMove == NULL) {
        printf("No possible move left\n");
        return 7;  // Return code indicating no moves left
    }

    int pieceType = -1;
    // Check if the move ends on a square with a piece, specifically a king
    PIECE *piece = board->squares[bestMove->endX][bestMove->endY];
    if (piece && piece->type == King)
        pieceType = King;

    // Attempt to make the move and validate it
    if (makeAndValidateMove(boardlist->Last->Board, bestMove->startX, bestMove->startY, bestMove->endX, bestMove->endY)) {
        // Write the move to a file
        WriteMove(boardlist, bestMove->startX, bestMove->startY, bestMove->endX, bestMove->endY, fptr);
        if (pieceType == King) {
            printf("King is captured\n");
            return 5;  // Return code indicating a king has been captured
        }
    } else {
        // Log failure if the move was illegal
        fprintf(fptr, "Bot Failed: Made an Illegal Move\n");
    }

    // Free the memory allocated for the best move
    free(bestMove);

    return 4;  // Standard return code indicating normal operation
}

// Function to determine the best possible move for a given player
MOVE *bestmove(BOARD *board, int turn, LastMove *lastMove) {
    MOVE *allPossibleMoves = malloc(sizeof(MOVE) * 256);  // Allocate memory for all possible moves
    int moveCount = 0;
    // Generate all legal moves for the player
    generateAllMoves(board, allPossibleMoves, &moveCount, turn, lastMove);

    int baseScore = evaluateBoard(board, turn);  // Evaluate the current board score
    int maxScore = -1000;

    MOVE *bestMoves[moveCount];
    int bestMoveCount = 0;

    // Evaluate each move based on the resulting board score
    for (int i = 0; i < moveCount; ++i) {
        MOVE *move = &allPossibleMoves[i];
        PIECE *piece = board->squares[move->endX][move->endY];
        int score = baseScore;
        // Add the value of the captured piece to the score
        if (piece)
            score += piece->weight;

        if (score > maxScore) {
            maxScore = score;
            bestMoveCount = 0;
        }

        if (score == maxScore)
            bestMoves[bestMoveCount++] = move;
    }

    MOVE *move = NULL;
    if (bestMoveCount > 0) {
        move = malloc(sizeof(MOVE));
        *move = *bestMoves[rand() % bestMoveCount];  // Select one of the best moves at random
    }

    free(allPossibleMoves);

    return move;
}

// Function to evaluate the overall score of the board from a player's perspective
int evaluateBoard(BOARD *board, int turn) {
    int whiteScore = 0, blackScore = 0;

    // Calculate scores based on the sum of piece values
    for (int x = 0; x < BOARDSIZE; x++) {
        for (int y = 0; y < BOARDSIZE; y++) {
            PIECE *piece = board->squares[x][y];
            if (piece) {
                if (piece->color == 1) { // 1 is White
                    whiteScore += piece->weight;
                } else if (piece->color == 2) { // 2 is Black
                    blackScore += piece->weight;
                }
            }
        }
    }

    // Return the score difference depending on whose turn it is
    return turn == 1 ? whiteScore - blackScore : blackScore - whiteScore;
}

// Function to generate all legal moves for a given player
void generateAllMoves(BOARD *board, MOVE *moves, int *moveCount, int turn, LastMove *lastMove) {
    *moveCount = 0;
    // Iterate over all board positions
    for (int x = 0; x < BOARDSIZE; x++) {
        for (int y = 0; y < BOARDSIZE; y++) {
            PIECE *piece = board->squares[x][y];
            if (piece && piece->color == turn) {
                // Generate potential moves for each piece
                for (int dx = 0; dx < BOARDSIZE; dx++) {
                    for (int dy = 0; dy < BOARDSIZE; dy++) {
                        if (isMoveLegal(piece, x, y, dx, dy, board, lastMove)) {
                            // Check if the move puts own king in check
                            PIECE *temp = board->squares[dx][dy];
                            board->squares[x][y] = NULL;
                            board->squares[dx][dy] = piece;

                            int willBeInCheck = isKingInCheck(board, turn);

                            board->squares[x][y] = piece;
                            board->squares[dx][dy] = temp;

                            if (willBeInCheck)
                                continue;

                            moves[(*moveCount)++] = (MOVE) {x, y, dx, dy};  // Add move to the list if valid
                        }
                    }
                }
            }
        }
    }
}
