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
bcurses_move_cursor
bcurses_addstr
bcurses_refresh
bcurses_set_screen_mode

//				DONE
########################################
bcurses_getmaxyx(int* maxx, int* maxy)
bcurses_init_screen()
bcurses_destroy_scr()

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

//#########################################
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
	} changes;

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
//#########################################


/*##################
 *##  INTERNAL    ##
 *################## */

static void getmaxyx()
{
	// Updates the global variables for values
	struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
	mainscr->dimensions.maxy = max.ws_row;
	mainscr->dimensions.maxx = max.ws_col;
}


static void add_change(char* text)
{
	if (mainscr->changes.capacity - mainscr->changes.len > strlen(text))
	{
		strcat(mainscr->changes.pointer, text);
	}
	else 
	{
		// i is declared outside of for loop so that it doesnt get discarded after loop ends
		int i;
		// double i until we get the required amount of size
		for (int i = 1; i + strlen(text) > mainscr->changes.capacity - mainscr->changes.len;)
		{
			i*=2;
		}

		// Backup pointer incase somehow fails
		char* temp_ptr = mainscr->changes.pointer;

		// Allocate the value we computed from the for loop
		mainscr->changes.pointer = realloc(mainscr->changes.pointer, i + mainscr->changes.capacity);

		// Check for errors in reallocation
		if (mainscr->changes.pointer == NULL)
		{mainscr->changes.pointer = temp_ptr;} // Need to add debug later
		else 
		{
			// Add to actual buffer (finally)
			strcat(mainscr->changes.pointer, text);

		}
	}
}



static void add_debug_print(char* err)
{
	if (mainscr->err_list.capacity - mainscr->changes.len > strlen(err))
	{
		strcat(mainscr->err_list.pointer, err);
	}
	else 
	{
		// i is declared outside of for loop so that it doesnt get discarded after loop ends
		int i;
		// double i until we get the required amount of size
		for (int i = 1; i + strlen(err) > mainscr->err_list.capacity - mainscr->err_list.len;)
		{
			i*=2;
		}

		// Backup pointer incase somehow fails
		char* temp_ptr = mainscr->err_list.pointer;

		// Allocate the value we computed from the for loop
		mainscr->err_list.pointer = realloc(mainscr->err_list.pointer, i + mainscr->err_list.capacity);

		// Check for errors in reallocation
		if (mainscr->err_list.pointer == NULL)
		{mainscr->err_list.pointer = temp_ptr;}
		else 
		{
			// Add to actual buffer (finally)
			strcat(mainscr->err_list.pointer, err);

		}
	}
}



/*#########################
 *##      USER API      ##
 *######################### */

// Naming: These functions must be prefixed with "bcurses_" for organization


void bcurses_refresh()
{
	write(STDOUT_FILENO,mainscr->changes.pointer,mainscr->changes.len);
	memset(mainscr->changes.pointer, 0, mainscr->changes.len);
	mainscr->changes.len = 0;
}

void bcurses_init_screen()
{
	bool init_success;

	// Initializes global tracking struct
	if (mainscr == NULL)
		{
		mainscr = malloc(sizeof(ScreenState));
		if (mainscr == NULL) {init_success = false;}
		else {init_success = true;}
		}

	else 
		{init_success = false;}

	if (init_success == true) 
		{
			getmaxyx(); // update the dimensions before using them

			// Allocate memory for tracking and update the things that we need to
			// Initialize screen buffer
			mainscr->screen.pointer = malloc(sizeof(char)*mainscr->dimensions.maxy*16*mainscr->dimensions.maxx);
			mainscr->screen.capacity = sizeof(char)*mainscr->dimensions.maxy*16*mainscr->dimensions.maxx;
			
			// Initialize changes buffer
			mainscr->changes.pointer = malloc(sizeof(char)*mainscr->dimensions.maxy*mainscr->dimensions.maxx);
			mainscr->changes.capacity = sizeof(char)*mainscr->dimensions.maxy*mainscr->dimensions.maxx;

			// Initialize error handling list
			mainscr->err_list.pointer = malloc(sizeof(char)*100);
			mainscr->err_list.capacity = sizeof(char)*100;

			// set flag defaults
			bool flag_default = false;
			mainscr->flag_list.fullscreen = flag_default;
			mainscr->flag_list.partial_screen = flag_default;
		}
}


void bcurses_set_screen_mode()
{

}


void bcurses_getmaxyx(int* usr_maxx, int* usr_maxy)
{
	// Updates the global variables for values
	struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
	*usr_maxy = max.ws_row;
	*usr_maxx = max.ws_col;
	mainscr->dimensions.maxy = max.ws_row;
	mainscr->dimensions.maxx = max.ws_col;
}


void bcurses_move_cursor(int x, int y)
{
	
}


void bcurses_addstr(int x, int y, char* text)
{
	bcurses_move_cursor(x, y);
}


void bcurses_destroy_scr() 
{
	free(mainscr->screen.pointer);
	free(mainscr->err_list.pointer);
	free(mainscr);
	mainscr = NULL;
}


// only debugging
int main()
{
	bcurses_init_screen();
	add_debug_print("this is an error");
	getmaxyx();
	return 0;
}

