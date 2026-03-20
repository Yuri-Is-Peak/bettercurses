#include <bettercurses.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
	char* starting_pixels;
	int len;

} initinfo;

typedef struct {
	int x, y;
} coords;

coords *maxxmaxy = NULL;

void printpixel(int x, int y)
{
	bcurses_add_str(x, y, "██");

}



void init(char* init, int len)
{
	
}




int main()
{
	bcurses_init_fullscreen();
	maxxmaxy = malloc(sizeof(coords));
	initinfo start;
	bcurses_getmaxyx(&maxxmaxy->x, &maxxmaxy->y);
	if (maxxmaxy->y % 2)
	{
		maxxmaxy->y -=1;
	}
	if (maxxmaxy->x % 2)
	{
		maxxmaxy->x -=1;
	}
	maxxmaxy->x /= 2;
	printpixel(0, 0);

	getchar();

	bcurses_kill_scr();
	return 0;
}
