#include "bettercurses.h"
#include <stdio.h>
int main() 
{
	init_fullscreen();
	add_colored_str(10, 10, "color", 174, 20, 207);
	move_cursor(10, 10);
	getchar();
	exit_cleanup();
}
