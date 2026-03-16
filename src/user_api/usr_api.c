#include <defs.h>
#include <termio.h>
#include <unistd.h>
#include <intern_api.h>
#include <shared_api.h>

//#########################################
/*#########################
 *##      USER API      ##
 *######################### */

// Naming: These functions must be prefixed with "bcurses_" for organization


void bcurses_set_fullscreen()
{
	{
		mainscr->screen_mode.fullscreen = true;
		add_change(OCTAL_ESC"?1049h");
	}
}


void bcurses_set_partial_screen(int lines, bool mode)
{
	mainscr->partial_info.lines = lines;
	mainscr->screen_mode.partial_screen = true;
	if (mode) {mainscr->partial_info.restore_full = true;}

	for (int i=0; i < lines; i++)
	{
		add_change("\n");
	}

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




void bcurses_addstr(int x, int y, char* text)
{
	if (mainscr->screen_mode.fullscreen)
	{
		add_change(OCTAL_ESC_ALT"7");
		bcurses_move_cursor(x, y);
		add_change(text);
		add_change(OCTAL_ESC_ALT"8");
	}

	// tdoo: make partial screen x n y be relative
	else if (mainscr->screen_mode.partial_screen)
	{
		add_change(OCTAL_ESC_ALT"7");
		bcurses_move_cursor(x, y);
		add_change(text);
		add_change(OCTAL_ESC_ALT"8");
	}

}



// TEMPORARY, tdoo TO MAKE IT WORK FOR DISABLING
void enable_raw_mode()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);        // get current settings
    raw.c_lflag &= ~(ECHO | ICANON);     // disable echo and canonical mode
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode()
{
    struct termios cooked;
    tcgetattr(STDIN_FILENO, &cooked);
    cooked.c_lflag |= (ECHO | ICANON);   // re-enable echo and canonical mode
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &cooked);
}
