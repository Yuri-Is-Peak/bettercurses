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
#include <stdlib.h>
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

// Global tracking for state
typedef struct {
	struct {
		int maxx;
		int maxy;
		} dimensions;

	struct {
		char* pointer;
		int capacity; 
		int len;
		} err_list;


	struct {
		char* pointer;
		int capacity; 
		int len;
		} screen;

	struct {
		bool fullscreen;
		bool partial_screen;
	} flag_list;
	
} ScreenState;

ScreenState* mainscr = NULL;

/*##################
 *##  INTERNAL    ##
 *################## */

void getmaxyx()
{
	// Updates the global variables for values
	struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
	main.dimensions.maxy = max.ws_row;
	intern.maxx = max.ws_col;
}


void add_debug_print(char* err)
{
	strcat(errorlist.pointer, err);
}







/*#########################
 *##      USER API      ##
 *######################### */

// Naming: These functions must be prefixed with "bcurses_" for organization

int bcurses_init_screen()
{
	bool init_success;
	// Initialize global tracking
	if (mainscr == NULL)
		{mainscr = malloc(sizeof(ScreenState)); init_success = true;}
	else 
		{init_success = false;}
	if (init_success == true) 
		{
			getmaxyx();
			mainscr->screen.pointer = malloc();

		}

}


void bcurses_getmaxyx(int* usr_maxx, int* usr_maxy)
{
	// Updates the global variables for values
	struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
	*usr_maxy = max.ws_row;
	*usr_maxx = max.ws_col;
	main.maxy = max.ws_row;
	intern.maxx = max.ws_col;
}




// only debugging
int main()
{
	bcurses_init_fullscr();
	initialize_buffer(errorlist);
	add_debug_print("this is an error");
	getmaxyx();
	printf("%d  %d",intern.maxx,intern.maxy);
	printf("%s",err_list);
	return 0;
}






