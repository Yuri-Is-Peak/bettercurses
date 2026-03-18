/*##################
 *##  INTERNAL    ##
 *################## */
// THIS FILE IS IMPORTED BY BASSICALLY EVERYTHING
#include <defs.h>
#include <termio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


void hex_to_rgb(char* hex, RGB* color)
{
	sscanf(hex, "%02x%02x%02x", &color->red, &color->green, &color->blue);
}


void getmaxyx()
{
	// Updates the global variables for values
	struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
	mainscr->dimensions.maxy = max.ws_row-1;
	mainscr->dimensions.maxx = max.ws_col-1;
}



void debug_print(char* err)
{
	if (mainscr->err_list.capacity - mainscr->changes.len > strlen(err))
	{
		strcat(mainscr->err_list.pointer, err);
	}
	else 
	{
		// i is declared outside of for loop so that it doesnt get discarded after loop ends
		size_t i=mainscr->err_list.capacity;
		// double i until we get the required amount of size
		while (i + strlen(err) > mainscr->err_list.capacity - mainscr->err_list.len)
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


void refresh()
{
	// tdoo: Add tracking of the screen here too, but fine for now.
	write(STDOUT_FILENO,mainscr->changes.pointer,mainscr->changes.len);
	memset(mainscr->changes.pointer, 0, mainscr->changes.len);
	mainscr->changes.len = 0;
}


void add_change(char* text)
{
	if (mainscr->changes.capacity - mainscr->changes.len > strlen(text))
	{
		mainscr->changes.len += strlen(text);
		strcat(mainscr->changes.pointer, text);
	}
	else 
	{
		// i is declared outside of for loop so that it doesnt get discarded after loop ends
		size_t i=1;
		// double i until we get the required amount of size
		while (i + strlen(text) > mainscr->changes.capacity - mainscr->changes.len)
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
				strcat(mainscr->changes.pointer, text);  // finally add to the pointer
				mainscr->changes.len += strlen(text);
			}
	}
}


void move_cursor(int x, int y)
{
	char temp[30];
	sprintf(temp, OCTAL_ESC"%d;%dH", y+1, x+1);
	add_change(temp);
}

