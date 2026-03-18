#include <bettercurses.h>
#include <stdio.h>


int main()
{
	// MANDITORY
	// initialization
	bcurses_init_fullscreen();

	// Uses function to get the maximum x and y values in the terminal
	int maxx, maxy;
	bcurses_getmaxyx(&maxx, &maxy);
	
	// Main output system is bcurses_add_str it takes three arguments: the x, y, and the text to be printed.
	bcurses_add_str(1, 1, "Hello world");
	bcurses_add_str(0, maxy, "press enter to quit");
	bcurses_refresh();

	getchar();
	// MANDITORY
	// reverts users terminal to previous state
	bcurses_kill_scr();
	return 0;
}
