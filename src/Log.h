/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Log.h: Log creation and writing header file						 */
/*********************************************************************/
#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include "Board.h"


FILE *CreateFile();	/* Create the file to write to  */

void WriteMove(BLIST *BoardList, int f1, int y1, int f2, int y2, FILE *fptr); /* write to the log file */

void DeleteMove(BOARD *BoardList);	/* Delete the last move in the log file */

char numtochar(int Turn); /*conversion */

#endif
