#include <defs.h>
#include <unistd.h>
#include <stdlib.h>
#include <termio.h>
#include <string.h>

/*##################
 *##  INTERNAL    ##
 *################## */

void getmaxyx()
{
	// Updates the global variables for values
	struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
	mainscr->dimensions.maxy = max.ws_row;
	mainscr->dimensions.maxx = max.ws_col;
}






void add_debug_print(char* err)
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



