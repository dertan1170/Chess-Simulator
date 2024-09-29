/*********************************************************************/
/* Chess , for EECS 22L, Spring 2024                     			 */
/* Gui.c: Gui functions definitions									 */
/*********************************************************************/
#include "Gui.h"

/*Global Variables */
GtkWidget *window ;  
GtkWidget *fixed ; 
GtkWidget *chess_icon; 
GtkWidget *table ; 

enum GRID Board[BOARDSIZE][BOARDSIZE];

void InitBoard()
{
	int x, y;
	for(x = 0; x < BOARDSIZE; x++){
		for(y = 0; y < BOARDSIZE; y++){
		if((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1)){
			Board[x][y] = BLACK;
		}
		else{
			Board[x][y] = WHITE;
		}
		}
	}
	Board[0][0] = BROOK;
	Board[1][0] = BKNIGHT;
	Board[2][0] = BBISHOP;
	Board[3][0] = BQUEEN;
	Board[4][0] = BKING;
	Board[5][0] = BBISHOP;
	Board[6][0] = BKNIGHT;
	Board[7][0] = BROOK;
	
	Board[0][1] = BPAWN;
	Board[1][1] = BPAWN;
	Board[2][1] = BPAWN;
	Board[3][1] = BPAWN;
	Board[4][1] = BPAWN;
	Board[5][1] = BPAWN;
	Board[6][1] = BPAWN;
	Board[7][1] = BPAWN; 
	
	Board[0][7] = WROOK;
	Board[1][7] = WKNIGHT;
	Board[2][7] = WBISHOP;
	Board[3][7] = WQUEEN;
	Board[4][7] = WKING;
	Board[5][7] = WBISHOP;
	Board[6][7] = WKNIGHT;
	Board[7][7] = WROOK;

	Board[0][6] = WPAWN;
	Board[1][6] = WPAWN;
	Board[2][6] = WPAWN;
	Board[3][6] = WPAWN;
	Board[4][6] = WPAWN;
	Board[5][6] = WPAWN;
	Board[6][6] = WPAWN;
	Board[7][6] = WPAWN; 
}

void ResetBoard()
{
  	InitBoard();
}


void DrawBoard()
{
	int i, j;

    for(i = 0; i < BOARDSIZE; i ++)
	{
		for(j = 0; j < BOARDSIZE; j ++)
		{
			switch(Board[i][j])
			{
				case BLACK:
					chess_icon = gtk_image_new_from_file("./chess_icons/Bsquare.jpg") ;
					break;
				case WHITE:
					chess_icon = gtk_image_new_from_file("./chess_icons/Wsquare.jpg") ;
					break;
				case WKING:
					chess_icon = gtk_image_new_from_file("./chess_icons/WKing.png") ;
					break;
       			case WQUEEN:
					chess_icon = gtk_image_new_from_file("./chess_icons/WQUEEN.png") ;
					break;
				case WKNIGHT:
					chess_icon = gtk_image_new_from_file("./chess_icons/WKnight.png") ;
					break;
        		case WBISHOP:
					chess_icon = gtk_image_new_from_file("./chess_icons/WBishop.png") ;
					break;
        		case WROOK:
					chess_icon = gtk_image_new_from_file("./chess_icons/WRook.png") ;
					break;
        		case WPAWN:
					chess_icon = gtk_image_new_from_file("./chess_icons/WPawn.png") ;
					break;
        		case BKING:
					chess_icon = gtk_image_new_from_file("./chess_icons/BKING.png") ;
					break;
        		case BQUEEN:
					chess_icon = gtk_image_new_from_file("./chess_icons/BQUEEN.png") ;
					break;
				case BKNIGHT:
					chess_icon = gtk_image_new_from_file("./chess_icons/BKnight.png") ;
					break;
        		case BBISHOP:
					chess_icon = gtk_image_new_from_file("./chess_icons/BBishop.png") ;
					break;
        		case BROOK:
					chess_icon = gtk_image_new_from_file("./chess_icons/BRook.png") ;
					break;
        		case BPAWN:
					chess_icon = gtk_image_new_from_file("./chess_icons/BPawn.png") ;
					break; 
        		default:
					break;
				
			}
			gtk_table_attach(GTK_TABLE(table), chess_icon, i, i + 1, j, j + 1, GTK_FILL, GTK_FILL, 0, 0) ;
		}
	}
}



static void createPieceGui(int pieceColor, int pieceType)
{
	int x, y;
	/*pieceColor = 1; //WHITE
	pieceColor = 2; //BLACK
	pieceType = 1; //PAWN
	pieceType = 2; //KNIGHT
	pieceType = 3; //BISHOP
	pieceType = 4; //ROOK
	pieceType = 5; //QUEEN
	pieceType = 6; //KING */
  
	for(x = 0; x < BOARDSIZE; x ++)
	{
		for(y = 0; y < BOARDSIZE; y ++)
		{
			if(pieceColor == 1)
			{
				switch(Board[x][y])
				{
				case 1:
					chess_icon = gtk_image_new_from_file("./chess_icons/WPawn.png") ;
					break;
				case 2:
					chess_icon = gtk_image_new_from_file("./chess_icons/WKnight.png") ;
					break;
				case 3:
					chess_icon = gtk_image_new_from_file("./chess_icons/WBishop.png") ;
					break;
				case 4:
					chess_icon = gtk_image_new_from_file("./chess_icons/WRook.png") ;
					break;
				case 5:
					chess_icon = gtk_image_new_from_file("./chess_icons/WQUEEN.png") ;
					break;
				case 6:
					chess_icon = gtk_image_new_from_file("./chess_icons/WKing.png") ;
					break;
				default:
					break;
				} 
       		}
       		else if (pieceColor == 2)
			{
				switch(Board[x][y])
				{
				case 1:
					chess_icon = gtk_image_new_from_file("./chess_icons/BPawn.png") ;
					break;
				case 2:
					chess_icon = gtk_image_new_from_file("./chess_icons/BKnight.png") ;
					break;
				case 3:
					chess_icon = gtk_image_new_from_file("./chess_icons/BBishop.png") ;
					break;
				case 4:
					chess_icon = gtk_image_new_from_file("./chess_icons/BRook.png") ;
					break;
				case 5:
					chess_icon = gtk_image_new_from_file("./chess_icons/BQUEEN.png") ;
					break;
				case 6:
					chess_icon = gtk_image_new_from_file("./chess_icons/BKING.png") ;
					break;
				default:
					break;
				} 
       		}
		}
	}
}

static gboolean on_delete_event (GtkWidget *widget, GdkEvent  *event, gpointer   data){
  g_print ("delete event occurred\n"); 
  gtk_main_quit();
  return TRUE;
}

void create_gui()
{
	// Initialize GTK - testing
	// InitBoard();

	/*create a new window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
	gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT) ; 
	// gtk_container_set_border_width (GTK_CONTAINER(window), WINDOW_BORDER) ; 
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER) ; 
	gtk_window_set_title(GTK_WINDOW(window), "Let's play Chess!") ; 
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE) ; 


	/*register event handlers*/
	g_signal_connect(window, "delete_event", G_CALLBACK(on_delete_event), NULL) ; 
	gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK) ; 

	/*create a table and draw the board*/
	table = gtk_table_new (BOARDSIZE, BOARDSIZE, TRUE) ; 
	gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ; 
	DrawBoard();

	fixed = gtk_fixed_new() ; 
	gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ; 
	gtk_container_add(GTK_CONTAINER(window), fixed) ; 


	/*show the window*/
	gtk_widget_show_all(window) ; 

	// Start the GTK main loop - testing
	// gtk_main() ; 
}

// int main (int argc, char *argv[])
// {
// 	// Initialize GTK
// 	gtk_init(&argc, &argv) ;
// 	InitBoard();
// 	// ResetBoard();

// 	/*show the window*/
// 	create_gui();

// 	// Start the GTK main loop
// 	gtk_main() ; 

// 	return 0 ;
// }
