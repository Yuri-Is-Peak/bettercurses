#include <asm-generic/ioctls.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/ioctl.h>

#define OCTAL_ESC "\033["
/* This code has a [
 * some escape sequences do not have this. 
 * However most do. Having a [ is a lot more common.
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
 * add handling of character input (progress)
 * add a border draw function, taking the dimensions and the characters to draw it with
 *
 * DONE
 * add getmaxyx for grabbing terminal dimensions (partially done: havent finished the correct return format)
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
// GLOBALS
int maxy;
int maxx;
static int partial_maxy;
static int internal_maxx;
static int internal_maxy;
static bool partial_screen;
static volatile sig_atomic_t resize_flag = 0;

void init_fullscreen()
{
	partial_screen = false;
	printf("%s%s",OCTAL_ESC,SAVE_SCR);
}


static void sigwinch_handler(int sig) {
    resize_flag = 1;
}


void getmaxyx()
{
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    maxx = ws.ws_col;
    maxy = ws.ws_row;
	internal_maxx = ws.ws_col;
    internal_maxy = ws.ws_row;
}



void cursor_visibility(bool value)
{
	if (value){printf("%s?25h",OCTAL_ESC);}
	else {printf("%s?25l",OCTAL_ESC);}
}

// rant below
// Temporarily commented out. Implementing turned out to be a lot harder,
// Due to some terminals not accepting an older escape sequence to save only the screen
// We will have to manually track the cursor and delete the newlines made by partial screen. 
// This is a PAIN IN THE ASS
// hence why i am not doing it yet and trying to get a functional state first.
/* void init_partial_screen(int y, bool restore)
{
    partial_screen = true;
    partial_maxy = internal_maxy - y;
    for (int i = 0; i < y; i++) printf("\n");
    printf("%s%dA", OCTAL_ESC, y);  // move cursor back up
    if (restore) printf("%s7", OCTAL_ESC_ALT);  // save position after scroll
}
*/

static int validate_coordinates(int x, int y)
{
	if (x < internal_maxx && y < internal_maxy) {return 1;}
	else {return 0;}
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
//this no work for some reason
void cursor_mode(int mode, bool Blink)
{
	if (mode < 0 || mode > 2) {printf("Incorrect mode");}
	int real_mode = (mode * 2) + (Blink ? 1 : 2);
	printf("%s%d q",OCTAL_ESC,real_mode);
    fflush(stdout);
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
	move_cursor(x,y);
	printf("%d",num);
	printf("%s8",OCTAL_ESC_ALT);
}


void add_float(int x, int y, float flt)
{
	y++;
	x++;
	printf("%s7",OCTAL_ESC_ALT);
	move_cursor(x,y);
	printf("%f",flt);
	printf("%s8",OCTAL_ESC_ALT);
}


void add_str(char text[], int x, int y)
{
	y++;
	x++;
	printf("%s7",OCTAL_ESC_ALT);
	move_cursor(x,y);
	printf("%s",text);
	printf("%s8",OCTAL_ESC_ALT);
}


void add_colored_str(char text[], int x, int y, int red, int green, int blue)
{
	y++;
	x++;
	printf("%s7",OCTAL_ESC_ALT);
	move_cursor(x,y);
	printf("%s38;2;%d;%d;%dm",OCTAL_ESC,red,green,blue);
	printf("%s",text);

	// Reset styles and colors
	printf("%s0m",OCTAL_ESC);

	printf("%s8",OCTAL_ESC_ALT);
}
// end of "add" functions


void exit_cleanup()
{
	if (!partial_screen) 
	{
		printf("%s%s",OCTAL_ESC,RESTORE_SCR);
	}
	else 
	{
		printf("%s8",OCTAL_ESC_ALT);
	}
	printf("%s0 q",OCTAL_ESC);
	// echo_input(true)
	cursor_visibility(true);
	// kills the signal handling the resizing
	signal(SIGWINCH, SIG_DFL);
    fflush(stdout);  // add this as the very last thing
}


bool resize_check()
{
	if (resize_flag) {resize_flag= 0; return true;}
	else {return false;}
}


// TODO
char* get_key() 
{
	if (resize_check()) {return "RESIZE";}
	else {return 0;}
}
