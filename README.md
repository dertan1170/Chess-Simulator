# Chess-Simulator

This project, coded in C, allows the user to play chess in three different ways: Player vs Bot, Bot vs Bot, and Player vs Player.

**Version:** 1.0.0  
**Release Date:** 4/28/24  
**Authors:** Derek Tang, Anna Ahn, Ishika Narain, Filiberto Alvarez, Bilal Malik, Christian Zeidan
<br />
© 1987 - 2024 B-Chess. All Rights Reserved

---

## General Instructions

- Follow the instructions stated in the `INSTALL.TXT` to download the program.
- To run the program, navigate to the `bin/` directory and execute `./Chess`.
- After executing `./Chess`, use the ASCII interface to interact with the program.
- You can select a game mode, piece color (if applicable), and move pieces to play chess.
- Valid inputs for moving pieces are in the format `a1`, `H7`, `C8`, while invalid inputs include `12`, `z4`, `I9`.
- Navigate to the settings menu in the `./Chess` executable for more detailed information on the ASCII interface and rules.

---

## Extra Features

- Chess Simulator Info/Rules in Settings
- Random Color Selection
- Undo
- Bot vs Bot
- Player vs Player

---

## README for Users

For more details, see `Chess_UserManual.pdf` located in the `doc/` directory.

### Contents of `Chess_V1.0.tar.gz`

- **bin/**: Directory containing all the executables
  - `Chess`: Main chess executable
  - `Log.txt`: Log of chess moves made
- **doc/**: Directory with user and software documentation
  - `Chess_UserManual.pdf`: Detailed user manual
- `INSTALL.TXT`: Installation directions
- `LICENSE.TXT`: Licensing by B-Chess Studios & BBB Software Inc.
- `README`: README for the chess simulator

---

## README for Programmers

For more details, see `Chess_SoftwareSpec.pdf` located in the `doc/` directory.

### Make Commands

- `make all`: Create the main executable `Chess` and place it in the `bin/` directory.
- `make test`: Create the test executables like `testboarddisplay`, place them in the `bin/` directory, and run them.
- `make clean`: Remove all `.o` files in the `src/` directory and any `.tar.gz` files.
- `make tar`: Generate the `.tar.gz` files for the user/programmer.

### Contents of `Chess_V1.0_src.tar.gz`

- **bin/**: Directory containing all the executables
  - `Chess`: Main chess executable
  - `Log.txt`: Log of chess moves made
- **doc/**: Directory with user and software documentation
  - `Chess_SoftwareSpec.pdf`: Detailed software specifications for the Chess.c program
  - `Chess_UserManual.pdf`: Detailed user manual
- **src/**: Directory containing all the C files along with a Makefile
  - `Board.c`: Functions for the board structures
  - `Board.h`: Header file for `Board.c`
  - `Bot.c`: Functions for the bot
  - `Bot.h`: Header file for `Bot.c`
  - `Chess.c`: Main program file
  - `Constants.h`: File with all macros
  - `Gui.c`: Functions for the GUI
  - `Gui.h`: Header file for `Gui.c`
  - `Makefile`: Makefile to create the executables
  - `Pieces.c`: Functions for the pieces structures
  - `Pieces.h`: Header file for `Pieces.c`
  - `Rules.c`: Functions for chess rules
  - `Rules.h`: Header file for `Rules.c`
  - `test_rulecheck.c`: Unit test for the rules
  - `test_boarddisplay.c`: Unit test for the board display
- `INSTALL.TXT`: Installation directions
- `LICENSE.TXT`: Licensing by B-Chess Studios & BBB Software Inc.
- `Makefile`: Top-level Makefile that builds/cleans executables
- `README`: README for the chess simulator
