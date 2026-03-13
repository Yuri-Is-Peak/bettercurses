/*
##########################
###       TODO         ###
##########################
//
INTERN 
// 			   NOTDONE
########################################
initialize_buffer(char* buf, int size)
resize_buffer(char* buf int addsize)


//				DONE
########################################
add_debug_print(char* err)
getmaxyx()


USR API
//				NOTDONE
########################################


//				DONE
########################################
bcurses_getmaxyx(int* maxx, int* maxy)


*/

#include <asm-generic/ioctls.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <string.h>

#define OCTAL_ESC "\033["
/* This code has a [
 * some escape sequences do not have this. 
 * However most do. Having a [ is a lot more common.
 * But we still need the other version, albeit rarely
 * This is why there is a seperate macro for that. */
#define OCTAL_ESC_ALT "\033"
#define SAVE_SCR "?1049h"
#define RESTORE_SCR "?1049l"
#define VISIBLE_CURSOR "?25h"
#define INVISIBLE_CURSOR "?25l"

/* 1: block blinking
 * 2: block not blink 
 * 3: underline blink 
 * 4: underline not blink 
 * 5: blinking line 
 * 6: not blinking line */
#define CURSOR_MODE " q"
/* SAVE_CURSOR
 * OCTAL_ESC_ALT7 to save cursor pos
 * OCTAL_ESC_ALT8 to load the saved cursor pos */


static struct dimensions 
{
	int maxx;
	int maxy;
};


static struct buffer 
{
	char* pointer;
	int capacity;
	int len;
};

struct dimensions intern;
struct buffer errorlist;
struct buffer canvas;



// temp global
char err_list[1000];



/*##################
 *##  INTERNAL    ##
 *################## */

void getmaxyx()
{
	// Updates the global variables for values
	struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
	intern.maxy = max.ws_row;
	intern.maxx = max.ws_col;
}


void add_debug_print(char* err)
{
	strcat(err_list, err);
}


void initialize_buffer()
{
	// Initialize initial buffer which should be enough for most things
	// Make it expand later but for now fixed size.
}





/*#########################
 *##      USER API      ##
 *######################### */

// Naming: These functions must be prefixed with "bcurses_" for organization

void bcurses_getmaxyx(int* usr_maxx, int* usr_maxy)
{
	// Updates the global variables for values
	struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
	*usr_maxy = max.ws_row;
	*usr_maxx = max.ws_col;
	intern.maxy = max.ws_row;
	intern.maxx = max.ws_col;
}


// only debugging
int main()
{
	add_debug_print("this is an error");
	getmaxyx();
	printf("%d  %d",intern.maxx,intern.maxy);
	printf("%s",err_list);
	return 0;
}


// not used yet
void runtime_update()
{
	getmaxyx();
}







