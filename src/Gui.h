/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Gui.h: Gui functions header file									 */
/*********************************************************************/
#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include <string.h>
#include "Constants.h"

enum GRID
{
	BLACK,
	WHITE,
	WKING,
	WQUEEN,
	WKNIGHT,
	WBISHOP,
	WROOK,
	WPAWN,
	
	BKING,
	BQUEEN,
	BKNIGHT,
	BBISHOP,
	BROOK,
	BPAWN
};

void InitBoard();
void ResetBoard();
void DrawBoard();
static void createPieceGui(int pieceColor, int pieceType);
static gboolean on_delete_event (GtkWidget *widget, GdkEvent  *event, gpointer   data);
void create_gui();

#endif