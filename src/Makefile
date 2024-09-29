# Makefile: Chess
# Date Created: 4/9/2024
# Modifications:
# 	4/5/24 Derek ~ Created Makefile and made a basic outline
#	4/20/24 Derek ~ Updated Makefile with all the current files

# GTK 2.0 Makefile Variables
GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`
INC	= $(GTKINC)
LIBS = $(GTKLIBS)
OPTS = -g

# Variables
CC = gcc
DEBUG = -g -DDEBUG
# DEBUG = -O2
CFLAGS = -Wall -std=c11 -pedantic $(DEBUG) -c
LFLAGS = -Wall -std=c11 -pedantic $(DEBUG) -lm
MAIN = -DMAIN

# Default target
all: Chess
testboarddisplay: boarddisplay
testrulecheck: rulecheck

######################### Generate object files #######################
# Target for Chess.o
Chess.o: Chess.c Constants.h Board.h Pieces.h Rules.h Bot.h Log.h
	$(CC) $(CFLAGS) Chess.c -o Chess.o
# Gui - Gui.h & $(LIBS) $(OPTS)

# Target for Board.o
Board.o: Board.c Board.h Constants.h Pieces.h
	$(CC) $(CFLAGS) Board.c -o Board.o

# Target for Bot.o
Bot.o: Bot.c Bot.h Constants.h Board.h Pieces.h Rules.h Log.h
	$(CC) $(CFLAGS) Bot.c -o Bot.o

# Target for Pieces.o
Pieces.o: Pieces.c Pieces.h
	$(CC) $(CFLAGS) Pieces.c -o Pieces.o

# Target for Rules.o
Rules.o: Rules.c Rules.h Constants.h Board.h Pieces.h
	$(CC) $(CFLAGS) Rules.c -o Rules.o

# Target for Gui.o
# Gui.o: Gui.c Gui.h Constants.h
# 	$(CC) $(CFLAGS) $(INC) $(OPTS) Gui.c -o Gui.o

#Target for Log.o
Log.o: Log.c Log.h Board.h
	$(CC) $(CFLAGS) Log.c -o Log.o

######################### Generate the executable #####################
# Target for Chess
Chess: Chess.o Board.o Bot.o Pieces.o Rules.o Log.o
	$(CC) $(LFLAGS) Chess.o Board.o Bot.o Pieces.o Rules.o Log.o -o Chess
# Gui - Gui.h & $(LIBS) $(OPTS)

###############################  cleam  ###############################
# Target for clean-up
clean:
	rm -f *.o Chess TestChess testboarddisplay unitTestGui Log.txt Test rulecheck

###############################  Unit Tests ############################
# BoardDisplayTest
test_boarddisplay.o: test_boarddisplay.c Constants.h
	$(CC) $(CFLAGS) $(MAIN) test_boarddisplay.c -o test_boarddisplay.o
boarddisplay: test_boarddisplay.o Board.o Pieces.o
	$(CC) $(LFLAGS) test_boarddisplay.o Board.o Pieces.o -o testboarddisplay

# BoardDisplayTest
test_rulecheck.o: test_rulecheck.c Constants.h Board.h Pieces.h Rules.h
	$(CC) $(CFLAGS) $(MAIN) test_rulecheck.c -o test_rulecheck.o
rulecheck: test_rulecheck.o Board.o Pieces.o Rules.o
	$(CC) $(LFLAGS) test_rulecheck.o Board.o Pieces.o Rules.o -o rulecheck

# GUI Unit Test
# unitTestGui.o: Gui.c Gui.h Constants.h
# 	$(CC) $(CFLAGS) $(INC) $(OPTS) Gui.c -o unitTestGui.o
# unitTestGui: unitTestGui.o
# 	$(CC) $(LFLAGS) $(LIBS) $(OPTS) unitTestGui.o -o unitTestGui
