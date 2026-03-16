#include <defs.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



void bcurses_refresh()
{
	// tdoo: Add tracking of the screen here too, but fine for now.
	write(STDOUT_FILENO,mainscr->changes.pointer,mainscr->changes.len);
	memset(mainscr->changes.pointer, 0, mainscr->changes.len);
	mainscr->changes.len = 0;
}


int add_change(char* text)
{
	if (mainscr->changes.capacity - mainscr->changes.len > strlen(text))
	{
		mainscr->changes.len += strlen(text);
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
				strcat(mainscr->changes.pointer, text);  // finally add to the pointer
				mainscr->changes.len += strlen(text);
			}
	}
}


void bcurses_move_cursor(int x, int y)
{
	char temp[20];
	sprintf(temp, OCTAL_ESC"%d;%dH", y, x);
	add_change(temp);
}


