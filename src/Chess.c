/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Chess.c: Source file for the main function						 */
/*********************************************************************/
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "Constants.h"
#include "Board.h"
#include "Pieces.h"
#include "Rules.h"
#include "Bot.h"
// #include "Gui.h"
#include "Log.h"

// Function Declarations
static void printMenu(void);
static void printSettingsMenu(void);
static void printRules(void);
static void printColorSelectionMenu(void);
static void printGameMenu(void);
static void enterToContinue(void);
void printGameBoard(BOARD *board);
char printPieceType(BOARD *board, int i, int j);
char printPieceColor(BOARD *board, int i, int j);
int Conversion(char input);
void PickWin(int turn, char winner[6]);

int main(void)
{
	// Variable Declaration
	// Used to determine current and next states
	int state = 1;			// start at state 1 (main menu)
	int prevState = 1;		// start at state 1 (main menu)
	int choice = -1;		// no choice has been made yet
	// Determines the user's color: 1 - White; 2 - Black
	int userColor = -1;		// no color has been chosen
	int Turn = -1;			// no turn has been executed yet
	char winner[6];			// char array which will output
	// Pointers needed to operate functions in Board.c & Pieces.c
	BLIST *BoardList = NULL;
	BOARD *CURBOARD = 0, *NEXTBOARD = 0;
	// Pointer for file
	FILE *fptr = NULL;
	// Determines the game mode
	int Playerf, botf;
	int randColor; 
	// Start of Program
    printf("\nWelcome to Chess Simulator!\n");

	// Initialize Board
	BoardList = InitializeBoard();
	srand(time(NULL));

	// Finite-State Machine / Main program
	while (state != -1)
	{
		// State 1: Main Menu
		if (state == 1)
		{
			printMenu();
			printf("Choose an Option: ");
			scanf("%d", &choice);

			// Moves to the next state as chosen by the user
			switch (choice)
			{
			case 1:
				// Moves menu to the Player Vs Bot color selection menu
				state = 3;
				botf = 0;
				Playerf = 0;
				break;
			case 2:
				// Moves menu to the Bot vs Bot mode
				// Skips color selection menu
				state = 4;
				botf = 1;
				Playerf = 0;
				break;
			case 3:
				// Moves menu to the Player vs Player
				// Skips color selection menu
				state = 4;
				Playerf = 1;
				botf = 0;
				break;
			case 4:
				// Saves current state
				prevState = state;
				// Moves menu to settings menu
				state = 2;
				break;
			case 5:
				// Exits the game
				state = -1;
				printf("\nQuitting...\n");
				break;
			default:
				printf("Not a valid option please try again.\n");
				break;
			}
		}
		// State 2: Settings Menu
		else if (state == 2)
		{
			printSettingsMenu();
			printf("Choose an Option: ");
			scanf("%d", &choice);
			// Moves to the next state as chosen by the user
			switch (choice)
			{
			case 1:
				// Prints Rules for Chess Simulator
				printRules();
				enterToContinue();
				break;
			case 2:
				// Returns to previous state menu
				state = prevState;
				break;
			default:
				printf("Not a valid option please try again.\n");
				break;
			}
		}
		// State 3: Color Selection
		else if (state == 3)
		{
			printColorSelectionMenu();
			printf("Choose an Option: ");
			scanf("%d", &choice);

			// Moves to the next state as chosen by the user
			switch (choice)
			{
			case 1:
				// Sets color to White
				userColor = 1;
				Turn = 1;

				// White starts the game first
				printf("You will now start the game as White!\n");
				state++;
				break;
			case 2:
				// Randomly sets color
				// To be implemented
				randColor = rand() % 2;
				if(randColor == 1){
					userColor = 1;
				}
				else{
					userColor = 2;
				}
				Turn = 1;
				PickWin(userColor, winner);
				printf("You will now start the game as "); 
				for(int x = 0; x <= 5; x++)
				{	
					printf("%c",winner[x]);
				}
				printf("\n");
				state++;
				break;
			case 3:
				// Sets color to Black
				userColor = 2;
				Turn = 1;
				printf("You will now start the game as Black!\n");
				state++;
				break;
			case 4:
				// Saves current state
				prevState = state;
				// Moves menu to settings menu
				state = 2;
				break;
			case 5:
				// Returns to main menu
				state = 1;
				break;
			default:
				printf("Not a valid option please try again.\n");
				break;
			}
		}
		// State 4: Game
		else if (state == 4)
		{
			// If there doesn't exist a file already then create one
			if(fptr == NULL)
			{
				// Create files for log
				fptr = CreateFile(); 
			}
			// Does the following if the the boards don't match 
			if(CURBOARD == 0 || NEXTBOARD == 0 || Matching(CURBOARD, NEXTBOARD) != 1)
			{
				CURBOARD = BoardList -> Last -> Board;
				Turn = CURBOARD -> Turn;
				// If turn is 2 then player is White
				if(Turn == 1)
				{
					NEXTBOARD = CreateBoard(BoardList,2);
				}
				// If turn is 2 then player is Black
				if(Turn == 2)
				{
					NEXTBOARD = CreateBoard(BoardList,1);
				}
				Duplicate(CURBOARD, NEXTBOARD);
			}

			// Prints the current board
			printGameBoard(CURBOARD);

			// Player Vs Player mode
			if((Playerf == 1) ||((Turn == userColor) && botf == 0))
			{
				printGameMenu();
				printf("Choose an Option: ");
				scanf("%d", &choice);
				int startX, startY, endX, endY;  // Variables to store user input for move coordinates
				char input[3], output[3];
				// Moves to the next state as chosen by the user
				switch (choice)
				{
				case 1:
					// Move Piece
					// Keep prompting user to enter a poistion until a valid input is entered
					do
					{
						printf("Enter start position: ");
						// Only take in the first two characters of the position
						scanf("%2s", input);	//input[3] - char array of length 3
						// Uppercase the first character of the input
						input[0] = toupper(input[0]);
					}
					// Checks that the first char between A-H and that the second char is between 1-8
					while (!((input[0] >= 'A' && input[0] <= 'H') && (input[1] >= '1' && input[1] <= '8')));
					// A is mapped to 0; B to 1; etc.
					startX = input[0] - 'A';
					// 1 is mapped to 0; 2 to 1; etc.
					startY = input[1] - '1';
					// Get the piece at the starting position
					PIECE *selectedPiece = CURBOARD->squares[startX][startY];

					// Check if there's a piece at the given start position
					if (selectedPiece != NULL)
					{
						// Print out the selected piece type and color
						printf("Selected piece: %c%c\n",
						selectedPiece->color == White ? 'W' : 'B', // Adjust 'W' and 'B' based on how you're representing colors

						getPieceChar(selectedPiece->type)); // You'll need to implement getPieceChar to return the character representing the piece type

						if(CheckPieceColor(selectedPiece) != Turn)
						{
							printf("Invalid Piece Color, Please try again\n");
							break;
						}
					}
					else
					{
						printf("No piece at the selected position.\n");
						break;
					}

					// Keep prompting user to enter a poistion until a valid output is entered
					do
					{
						printf("Enter end position: ");
						// Only take in the first two characters of the position
						scanf("%2s", output);	//output[3] - char array of length 3
						// Uppercase the first character of the output
						output[0] = toupper(output[0]);
					}
					// Checks that the first char between A-H and that the second char is between 1-8
					while (!((output[0] >= 'A' && output[0] <= 'H') && (output[1] >= '1' && output[1] <= '8')));
					// A is mapped to 0; B to 1; etc.
					endX = output[0] - 'A';
					// 1 is mapped to 0; 2 to 1; etc.
					endY = output[1] - '1';

					if (makeAndValidateMove(NEXTBOARD, startX, startY, endX, endY))
					{
						// Checks if there is a checkmate
						printf("Checking if there's a Checkmate...\n");
						if(isKingInCheck(CURBOARD, NEXTBOARD -> Turn ))
						{
						printf("checking if king is in check\n");
							if(isCheckMate(CURBOARD, (NEXTBOARD -> Turn)))
							{
						printf("checking for checkmate\n"); 
								state = 5;
							}
						}
						printf("out of isKingInCheck\n");
						if (isStalemate(CURBOARD, CURBOARD->Turn))
						{
						//printf("check if in stalemate\n");
							state = 7;
							printf("check if in stalemate\n");
						}
						printf("out of isStalemate\n");

						startX++;
						startY++;
						endX++;
						endY++;
						WriteMove(BoardList, startX, startY, endX, endY, fptr); //write in the move 
						printf("Move successful!\n");
						// printGameBoard(board);
					}
					else
					{
						printf("Invalid move, Please try again.\n");
					}
					break;
				case 2:
					// Undos last move
					// To be implemented
					// Check that the structure is not length 1
					if (BoardList->Length == 1)
					{
						printf("Start of board. Unable undo the last move.\n");
						break;
					}
					if(Playerf == 1)
					{
						printf("Feature not available in Player Vs. Player mode");
						break;
					}
					else
					{
						// Delete last board
						UnAppendBoardEntry(BoardList);
						UnAppendBoardEntry(BoardList);
						UnAppendBoardEntry(BoardList);
						
						CURBOARD = BoardList -> Last -> Board;
						Turn = CURBOARD -> Turn;
						// If turn is 2 then player is White
						if(Turn == 1)
						{
							NEXTBOARD = CreateBoard(BoardList,2);
						}
						// If turn is 2 then player is Black
						if(Turn == 2)
						{
							NEXTBOARD = CreateBoard(BoardList,1);
						}
						Duplicate(CURBOARD, NEXTBOARD);

						printf("The last move has been undone!\n");
						break;
					}
				case 3:
					// User Resigns
					printf("You have resigned!\n");
					state = 6;
					break;
				case 4:
					// Log
					printf("\nLog:\nThe log is automatically generated while the game is played into a file named Log.txt\n");
					break;
				case 5:
					// Moves menu to settings menu
					prevState = state;
					state = 2;
					break;
				default:
					printf("Not a valid option please try again.\n");
					break;
				}
			}
			// Bot move
			else if((botf == 1) ||(Turn != userColor && botf == 0))
			{
				state = botmove(CURBOARD, BoardList, fptr, &lastMove);
			}
			
		//	printf("bot has made move, out of if statement\n");
			
			// Checks if there is a checkmate
		//	printf("Checking if there's a Checkmate...\n");
			if(isCheckMate(CURBOARD, NEXTBOARD -> Turn))
			{
			//	printf("checking for checkmate\n");
				state = 5;
			}
			
		//	printf("out of isKingInCheck\n");
			if (isStalemate(CURBOARD, CURBOARD -> Turn))
			{
			//printf("check if in stalemate\n");
				state = 7;
			//	printf("check if in stalemate\n");
			}
		//	printf("out of isStalemate\n");

		}	
		// State 5: Checkmate
		else if (state == 5)
		{
			printf("\nCheckmate!\n");

			PickWin(CURBOARD -> Turn, winner);

			for(int x = 0; x <= 5; x++)
			{
				printf("%c",winner[x]);
			}

			printf(" Wins\n");

			enterToContinue();
			state = 1;
			ResetList(BoardList);

		}
		// State 6: Resigned
		else if (state == 6)
		{
			printf("\nResigned!\n");
			PickWin(NEXTBOARD -> Turn, winner);

			for(int x = 0; x <= 5; x++)
			{
				printf("%c",winner[x]);
			}

			printf(" Wins\n");
			enterToContinue();
			state = 1;
			ResetList(BoardList);
		}
		// State 7: Draw
		else if (state == 7)
		{
			printf("\nDraw!\n");
			printf("No Winner\n");
			enterToContinue();
			state = 1;
			ResetList(BoardList);

		}
	}

	printf("Thank you for playing Chess Simulator!\n\n");

	DeleteBoardList(BoardList);

	// Return Code 0 - No Errors
    return 0;
}

// Function Definitions
// Prints Main Menu Options
static void printMenu(void)
{
	printf("\nChess Simulator Main Menu:\n");
	printf("  1. Player Vs Bot\n");
	printf("  2. Bot Vs Bot\n");
	printf("  3. Player Vs Player\n");
	printf("  4. Settings\n");
	printf("  5. Quit\n");
}
// Prints Settings Menu Options
static void printSettingsMenu(void)
{
	printf("\nSettings:\n");
	printf("  1. Rules\n");
	printf("  2. Back\n");
}
// Prints Rules for Chess Simulator
static void printRules(void)
{
	printf("\nChess Rules:\n");
	printf("This is a player vs bot Chess simulator.\n");
	printf("  W=White;B=Black\n");
	printf("  P=Pawn;N=Knight;B=Bishop;R=Rook;Q=Queen;K=King\n");
	printf("  Example: WP=White Pawn\n");
	printf("All valid chess moves in this simulator are based on the FIDE LAWS of CHESS.\n");
	printf("https://www.fide.com/FIDE/handbook/LawsOfChess.pdf\n");
}		
// Prints Color Selection Menu Options
static void printColorSelectionMenu(void)
{
	printf("\nColor Selection:\n");
	printf("  1. White\n");
	printf("  2. Random\n");
	printf("  3. Black\n");
	printf("  4. Settings\n");
	printf("  5. Back\n");
}
// Prints Game Menu Options
static void printGameMenu(void)
{
	printf("Game Options:\n");
	printf("  1. Move Piece\n");
	printf("  2. Undo\n");
	printf("  3. Resign\n");
	printf("  4. Log\n");
	printf("  5. Settings\n");
}
// Creates the Enter to continue effect
static void enterToContinue(void)
{
	char tempChar;
	printf("Press ENTER to continue...");
	// Clear Newline Buffer
	do
	{
		tempChar = getchar();
	}
	while (tempChar != '\n');
	// Waits for the user to input any char including the newline key
	getchar();
}
// Prints the chess board in ASCII given the board strucuture
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

int Conversion(char input)
{
	switch(input)
	{
		case 'A':
			return 1;
		case 'B':
			return 2;
		case 'C':
			return 3;
		case 'D':
			return 4;
		case 'E':
			return 5;
		case 'F':
			return 6;
		case 'G':
			return 7;
		case 'H':
			return 8;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		default:
			return 100;

	}
}


void PickWin(int turn, char winner[6])
{
	if(turn == 1)
	{
		winner[0] = 'W';
		winner[1] = 'h';
		winner[2] = 'i';
		winner[3] = 't';
		winner[4] = 'e';
	}
	if(turn == 2)
	{
		winner[0] = 'B';
		winner[1] = 'l';
		winner[2] = 'a';
		winner[3] = 'c';
		winner[4] = 'k';
	}
}
