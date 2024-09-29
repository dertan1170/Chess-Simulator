/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Log.h: Log creation and writing function definition				 */
/*********************************************************************/
#include "Log.h"

/* Create the file to write to */
FILE *CreateFile()
{

	FILE *fptr;
	fptr = fopen("Log.txt", "w+");
	fprintf(fptr,"Move#    Piece   Move\n");
	fclose(fptr);
	return fptr;
}

/* write to the log file */

void WriteMove(BLIST *BoardList, int f1, int y1, int f2, int y2, FILE *fptr)
{
	fptr = fopen("Log.txt", "a+");
	int Move = (BoardList -> Length) - 1;
	char startX;
	startX = numtochar(f1);
	char endX;
	endX = numtochar(f2);
	
	fprintf(fptr, " %d:       %c%d  ->  %c%d\n",Move, startX, y1, endX, y2); 
	fclose(fptr);
	return;
}

/* Delete last entry in log file 
void DeleteMove(BOARD *BoardList)
{
	File *fptr;
	fptr = fopen("Log.txt", "W")

// pull the length of the board list
//then iterate over the file and store it into another file except for the last value

	fclose(fptr);
	return;
}*/

char numtochar(int input)
{
	switch(input)
	{
		case 1:
			return 'A';
		case 2:
			return 'B';
		case 3:
			return 'C';
		case 4:
			return 'D';
		case 5:
			return 'E';
		case 6:
			return 'F';
		case 7:
			return 'G';
		case 8:
			return 'H';
		default:
			return 'Z';
	}
}
