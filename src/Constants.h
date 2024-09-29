/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Constants.h: macros header file									 */
/*********************************************************************/
#ifndef CONSTANTS_H
#define CONSTANTS_H

// Size of conventional board
#define BOARDSIZE 8
//#define MAX_MSGLEN  200 
// Constants for Gui.c
#define SQUARE_SIZE 10  //size of the individual squares
#define BOARD_BORDER 190 //heigh of the board
#define BOARD_WIDTH  (2*SQUARE_SIZE)
#define BOARD_HEIGHT (2*SQUARE_SIZE)
#define WINDOW_WIDTH  (BOARD_WIDTH + 2*BOARD_BORDER)
#define WINDOW_HEIGHT (BOARD_HEIGHT + 2*BOARD_BORDER)

#endif