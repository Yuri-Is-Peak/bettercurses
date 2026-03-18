/*####################
 *###	USR_API    ###
 *####################*/


// Remember that "" includes mean to search the project directory
// also: add bcurses_ before functions here.
#include "defs.h"
#include "intern_api.h"
#include "init.h"
#include <stdbool.h>
#include <stdint.h>
#include <termio.h>


//##################################//
// 		abstraction over init.c
//##################################//
int bcurses_init_fullscreen() 
{
	bool success = false;

	if (!mainscr->screen_mode.fullscreen && !mainscr->screen_mode.partial_screen) 
	{
		init_screen();
		mainscr->screen_mode.partial_screen = true;
		success = true;
	}

	else {debug_print("init_fullscreen failed - a screen has already been initialized. Destroy the current screen to initialize a new one");}

	return success;
}

int bcurses_init_partial_screen(int lines, bool restore) 
{
	bool success;
	if (!mainscr->screen_mode.fullscreen && !mainscr->screen_mode.partial_screen) 
	{
		mainscr->screen_mode.partial_screen = true;
		mainscr->partial_info.restore_full = restore;
		mainscr->partial_info.restore_full = restore;
		mainscr->partial_info.lines = lines;
		for (int i=0;i<lines;i++)
		add_change("\n");
		success = true;
	}
	else {debug_print("init_partial_screen failed - a screen has already been initialized. Destroy the current screen to initialize a new one"); success = false;}
	return success;
}


//##################################//
// abstraction on intern_api.c
//##################################//
void bcurses_add_str(int x, int y, char* text)
{
	add_change(OCTAL_ESC_ALT " 7");
	move_cursor(x, y);
	add_change(text);
	add_change(OCTAL_ESC_ALT " 8");
}


void bcurses_move_cursor(int x, int y)
{
	move_cursor(x, y);
}


void bcurses_getmaxyx(int *maxx, int *maxy)
{
	// Updates the global variables for values
	struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
	mainscr->dimensions.maxy = max.ws_row-1;
	mainscr->dimensions.maxx = max.ws_col-1;
	*maxy = max.ws_row-1;
	*maxx = max.ws_col-1;
}

int bcurses_kill_scr()
{
	bool success;
	success = destroy_scr();
	return success;
}



