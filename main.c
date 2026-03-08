#include <asm-generic/ioctls.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/ioctl.h>

// THIS ISNT HEX XDDDD
// ITS OCTAL
#define HEX_ESC "\033["
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
	printf("%s%s",HEX_ESC,SAVE_SCR);
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
	if (value){printf("%s?25h",HEX_ESC);}
	else {printf("%s?25l",HEX_ESC);}
}


void init_partial_screen(int row)
{
	partial_screen = true;
	partial_rows = rows - row;
	printf("%s%s",HEX_ESC,SAVE_SCR);
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
	printf("%s%d;%dH",HEX_ESC,y,x);
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
	printf("%s%d q",HEX_ESC,real_mode);
}

// print x things
void add_int(int x, int y, int num)
{
	printf("%s%d;%dH",HEX_ESC,y,x);
	printf("%d",num);
}


void add_float(int x, int y, float flt)
{
	printf("%s%d;%dH",HEX_ESC,y,x);
	printf("%f",flt);
}


void add_str(char text[], int x, int y)
{
	printf("%s%d;%dH",HEX_ESC,y,x);
	printf("%s",text);
}


void add_colored_str(char text[], int x, int y, int red, int green, int blue)
{
	printf("%s%d;%dH",HEX_ESC,y,x);
	printf("%s38;2;%d;%d;%dm",HEX_ESC,red,green,blue);
	printf("%s",text);
	// Reset styles and colors
	printf("%s0m",HEX_ESC);
}
//


void exit_cleanup()
{
	printf("%s0 q",HEX_ESC);
	printf("%s%s",HEX_ESC,RESTORE_SCR);
	// echo_input(true)
	cursor_visibility(true);
}


int main() 
{
	//init_partial_screen(4);
	init_fullscreen();
	getmaxyx();
	cursor_mode(2, true);
	move_cursor(20, 2); 


	// Keep program running until enter for testing
	char X = getchar();
	exit_cleanup();
return 0;
}
