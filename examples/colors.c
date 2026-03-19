#include <bettercurses.h>
#include <stdio.h>


void update_draw()
{
	CELL yellow;
	yellow.cell_bg = "1e1e1e";
	yellow.cell_fg = "fff700";
	bcurses_add_colored_str(0, 0, "hello", "45005e");
	bcurses_add_colored_cell(0, 1, "hello", &yellow);
	bcurses_refresh();
}





int main()
{
	bcurses_init_fullscreen();
	int maxx, maxy;
	bcurses_getmaxyx(&maxx, &maxy);
	
	update_draw();

	getchar();
	bcurses_kill_scr();
	return 0;
}
