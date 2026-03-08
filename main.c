#include <asm-generic/ioctls.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/ioctl.h>

#define OCTAL_ESC "\033["
/* This code has a [
 * some escape sequences do not have this. 
 * However most do. Having a [ is more common.
 * But we still need the other version, albeit rarely
 * This is why there is a seperate macro for that. */
#define OCTAL_ESC_ALT "\033"
#define SAVE_SCR "?1049h"
#define RESTORE_SCR "?1049l"


/* TODO:
 * functions:
 * INTERNAL ONLY
 * add validation of coordinates before printing
 *
 * EXTERNAL
 * add toggle for echoing text
 * add handling of character input
 * add getmaxyx for grabbing terminal dimensions
 *
 * DONE
 * add support for full screen initializing (done)
 * add suport for partial screen initializing (done)
 * add move_cursor (done)
 * add exit_cleanup partially done: might need to add more to function later
 * add_str (done)
 * add_float (done)
 * add_int (done)
 * add_float (done)
 * add_colored_str
 * add cursor_visibility toggle
 */

static int cols;
static int rows;
static int partial_cols;
static int partial_rows;
static bool partial_screen;
static struct {
	int cols;
	int rows;
} TermSize;


void init_fullscreen()
{
	partial_screen = false;
	printf("%s%s",OCTAL_ESC,SAVE_SCR);
}


int getmaxyx()
{
	struct winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	cols = ws.ws_col;
	rows = ws.ws_row;
	return 0;
}



void cursor_visibility(bool value)
{
	if (value){printf("%s?25h",OCTAL_ESC);}
	else {printf("%s?25l",OCTAL_ESC);}
}


void init_partial_screen(int row, bool restore)
{
	if (!restore) {printf("%s%s",OCTAL_ESC,SAVE_SCR);}
	partial_screen = true;
	partial_rows = rows - row;
	for (int i = 0; i < row; i++)
	{
		printf("\n");
	}
}


int validate_coordinates(int x, int y)
{
	// Placaholder
	return 0;
}


void move_cursor(int x, int y)
{
	printf("%s%d;%dH",OCTAL_ESC,y,x);
}


/* 1: block blinking
 * 2: block not blink 
 * 3: underline blink 
 * 4: underline not blink 
 * 5: blinking line 
 * 6: not blinking line
 */
void cursor_mode(float mode, bool Blink)
{
	if (mode < 0 || mode > 2) {printf("Incorrect mode");}
	int real_mode = (mode * 2) + (Blink ? 1 : 2);
	printf("%s%d q",OCTAL_ESC,real_mode);
}

/* EXPLANATION FOR THE "y/x++;"
 * The terminals coordinates are based on:
 * count of lines, not the index of lines. Example:
 * 1 is the first valid line for the count, while for the index its 0.
 * For the design, i ended up picking to have index based coordinates for the library.
 * It can be easily patched not to have index based coordinates by:
 * Removing all lines with "y++;" and "x++;"
 */
// start of "add" functions
void add_int(int x, int y, int num)
{
	y++;
	x++;
	printf("%s7",OCTAL_ESC_ALT);
	printf("%s%d;%dH",OCTAL_ESC,y,x);
	printf("%d",num);
	printf("%s8",OCTAL_ESC_ALT);
}


void add_float(int x, int y, float flt)
{
	y++;
	x++;
	printf("%s7",OCTAL_ESC_ALT);
	printf("%s%d;%dH",OCTAL_ESC,y,x);
	printf("%f",flt);
	printf("%s8",OCTAL_ESC_ALT);
}


void add_str(char text[], int x, int y)
{
	y++;
	x++;
	printf("%s7",OCTAL_ESC_ALT);
	printf("%s%d;%dH",OCTAL_ESC,y,x);
	printf("%s",text);
	printf("%s8",OCTAL_ESC_ALT);
}


void add_colored_str(char text[], int x, int y, int red, int green, int blue)
{
	y++;
	x++;
	printf("%s7",OCTAL_ESC_ALT);
	printf("%s%d;%dH",OCTAL_ESC,y,x);
	printf("%s38;2;%d;%d;%dm",OCTAL_ESC,red,green,blue);
	printf("%s",text);
	// Reset styles and colors
	printf("%s0m",OCTAL_ESC);
	printf("%s8",OCTAL_ESC_ALT);
}
// end of "add" functions


void exit_cleanup()
{
	printf("%s0 q",OCTAL_ESC);
	printf("%s%s",OCTAL_ESC,RESTORE_SCR);
	// echo_input(true)
	cursor_visibility(true);
}


int main() 
{
	//init_partial_screen(4, true);
	init_fullscreen();
	getmaxyx();
	cursor_mode(2, true);
	move_cursor(20, 2); 
	add_int(0, 0, cols);
	add_int(0, 1, rows);
// add restoring of cursor place when printing shit

	// Keep program running until enter for testing
	char X = getchar();
	exit_cleanup();
return 0;
}
