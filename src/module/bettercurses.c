#include <defs.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <termio.h>
#include <unistd.h>



ScreenState* mainscr = NULL;

//#########################################


/*#########################
 *##      USER API      ##
 *######################### */

// Naming: These functions must be prefixed with "bcurses_" for organization


void bcurses_refresh()
{
	// tdoo: Add tracking of the screen here too, but fine for now.
	write(STDOUT_FILENO,mainscr->changes.pointer,mainscr->changes.len);
	memset(mainscr->changes.pointer, 0, mainscr->changes.len);
	mainscr->changes.len = 0;
}


int bcurses_init_screen()
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
			mainscr->screen_mode.fullscreen = flag_default;
			mainscr->screen_mode.partial_screen = flag_default;
		}
	return init_success;
}


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


void bcurses_move_cursor(int x, int y)
{
	char temp[20];
	sprintf(temp, OCTAL_ESC"%d;%dH", y, x);
	add_change(temp);
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


void bcurses_destroy_scr() 
{
	if (mainscr->screen_mode.fullscreen)
	{
		// Resets the screen for fullscreen
		add_change(OCTAL_ESC"?1049l");
		bcurses_refresh();
	}
	else if (mainscr->screen_mode.partial_screen && mainscr->partial_info.restore_full)
	{
		bcurses_move_cursor(mainscr->dimensions.maxx, mainscr->dimensions.maxy);
		for (int i =0; i < mainscr->partial_info.lines; i++)
		{
			add_change(OCTAL_ESC"1M");
		}
		bcurses_move_cursor(10, 10);
	/*	for (int i =0; i < mainscr->partial_info.lines; i++)
		{
			add_change(OCTAL_ESC_ALT" M");
			bcurses_addstr(0, 0, "a");
		} */

		bcurses_refresh();
	}

	free(mainscr->screen.pointer);
	free(mainscr->err_list.pointer);
	free(mainscr);
	mainscr = NULL;
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



// only debugging
int main()
{
	bcurses_init_screen();
	bcurses_set_partial_screen(4, true);
	bcurses_refresh();
	enable_raw_mode();

	add_debug_print("this is an error");
	bcurses_addstr(0, 0, "Hello world");
	bcurses_refresh();

	char x;
	for (int i=0; i < 1;)
	{
		x = getchar();
		if (x == 10) {bcurses_destroy_scr(); break;}
		else {x = 0;}
	}
	disable_raw_mode();
	return 0;
}



