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


// abstraction over init.c
int bcurses_init_fullscreen() {
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

int bcurses_init_partial_screen(int lines) 
{
	if (!mainscr->screen_mode.fullscreen && !mainscr->screen_mode.partial_screen) 
	{
		mainscr->screen_mode.partial_screen = true;
		for (int i=0;i<lines;i++)
		add_change("\n");
	}
	else {debug_print("init_partial_screen failed - a screen has already been initialized. Destroy the current screen to initialize a new one");}
}


// abstraction on intern_api.c
void bcurses_add_str(int x, int y, char* text)
{
	add_change("");
}










