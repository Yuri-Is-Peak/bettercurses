#include <defs.h>
#include <stdlib.h>
#include <intern_api.h>


ScreenState* mainscr = NULL;


int init_screen()
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




int destroy_scr() 
{
	bool success = false;

	if (mainscr->screen_mode.fullscreen)
	{
		// Resets the screen for fullscreen
		add_change(OCTAL_ESC"?1049l");
		refresh();
		mainscr->screen_mode.fullscreen = false;
		success = true;
	}
	else if (mainscr->screen_mode.partial_screen && mainscr->partial_info.restore_full)
	{
		move_cursor(mainscr->dimensions.maxx, mainscr->dimensions.maxy);
		for (int i =0; i < mainscr->partial_info.lines; i++)
		{
			add_change(OCTAL_ESC"1M");
		}
		//
		// PLACEHOLDER
		move_cursor(10, 10);
		// PLACEHOLDER
		//
		mainscr->screen_mode.partial_screen = false;
		mainscr->partial_info.lines = 0;
		mainscr->partial_info.restore_full = false;
		refresh();
		success = true;
	}
	else if (!mainscr->partial_info.restore_full)
	{
		mainscr->screen_mode.partial_screen = false;
		mainscr->partial_info.lines = 0;
		success = true;
	}

	free(mainscr->screen.pointer);
	free(mainscr->err_list.pointer);
	free(mainscr);
	mainscr = NULL;
	return success;
}
