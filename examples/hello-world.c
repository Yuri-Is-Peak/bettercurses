#include <bettercurses.h>


int main()
{
	// MANDITORY
	// initialization
	bcurses_init_screen();
	bcurses_set_fullscreen();

	// Uses function to get the maximum x and y values in the terminal
	int maxx, maxy;
	bcurses_getmaxyx(&maxx, &maxy);

	bcurses_addstr(0, 0, "Hello world!");
	bcurses_addstr(maxx, 10, "Press enter to continue");

	// MANDITORY
	// reverts users terminal to previous state
	bcurses_destroy_scr();
	return 0;
}
