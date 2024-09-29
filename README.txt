README.txt
Version: 1.0.0 / Release
Authors:
	-Anna Ahn, Ishika Narain, Filiberto Alvarez, Bilal Malik, Christian Zeidan, Derek Tang
Date:
	-4/28/24
© 1987 - 2024 B-Chess. All Rights Reserved

General Instructions:
	- Follow the instructions stated in the INSTALL.TXT to download the program.
	- To run the program go into the "bin/" directory and type ./Chess to execute the chess program.
	- After executing ./Chess use the ASCII interface to use the program.
	- You can select a gamemode, piece color if applicable, and move pieces to play chess.
	- To move pieces valid inputs are a1/H7/C8, invalid inputs are 12/z4/I9.
	- Navigate to the settings menu in the ./Chess executable for more detailed information of the ASCII/Rules.

Extra Features:
	- Chess Simulator Info/Rules In Settings
	- Random Color Selection
	- Undo
	- Bot vs Bot
	- Player vs Player

README FOR USERS:
[For more details see Chess_UserManual.pdf located in the "doc/" directory]
Chess_V1.0.tar.gz Contents:
bin/							- Directory which stores copies of all the executables
	Chess						- Main chess executable
	Log.txt						- Log of chess moves made
doc/							- Directory with the user and software documentation
	Chess_UserManual.pdf		- Detailed user manual for the user
INSTALL.TXT						- Installation directions
LICENSE.TXT						- Licensing by B-Chess Studios & BBB Software Inc.
README							- README for chess simulator


README	FOR PROGRAMERS:
[For more details see Chess_SoftwareSpec.pdf located in the "doc/" directory]
Make Commands:
	- make all - create the main executable Chess and places it in the bin/ directory
	- make test - create the test executables like testboarddisplay, places it in the bin/ directory, and runs it
	- make clean - removes all the .o files in the src/ directory and any tar.gz files
	- make tar - generates the .tar.gz files for the user/programer 

Chess_V1.0_src.tar.gz Contents:
bin/							- Directory which stores copies of all the executables
	Chess						- Main chess executable
	Log.txt						- Log of chess moves made
doc/							- Directory with the user and software documentation
	Chess_SoftwareSpec.pdf		- Detailed software specifications for the Chess.c program
	Chess_UserManual.pdf		- Detailed user manual for the user
scr/							- Directory which contains all the c files along with a Makefile
	Board.c						- Functions for the board structures
	Board.h						- Board.c header file
	Bot.c						- Functions for the bot
	Bot.h						- Bot.c header file
	Chess.c						- File where the main program is located
	Constants.h					- File with all the macros
	Gui.c						- Functions for the Gui
	Gui.h						- Gui.c header files
	Makefile					- Makefile to create the executables
	Pieces.c					- Function for the pieces structures
	Pieces.h					- Pieces.c header file
	Rules.c						- Functions for chess rules
	Rules.h						- Rules.c header file
	test_rulecheck.c			- Unit test for the rules
	test_boarddisplay.c			- Unit test for the board display
INSTALL.TXT						- Installation directions
LICENSE.TXT						- Licensing by B-Chess Studios & BBB Software Inc.
Makefile						- Top level Makefile that builds/cleans executables
README							- README for chess simulator

