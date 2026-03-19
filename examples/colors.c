#include <bettercurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UP_LINE "┃"
#define LEFT_LINE "━"
#define UP_RIGHT_TURN_LINE "┗"
#define UP_LEFT_TURN_LINE "┛"
#define DOWN_LEFT_TURN_LINE "┓"
#define DOWN_RIGHT_TURN_LINE "┏"



typedef struct {
	struct {
		int maxx, maxy;
	} dimensions;

char* pipelist[100];

} screendata;

enum direction {
	DOWN = 0,
	UP = 1,
	RIGHT = 2,
	LEFT = 3
};


//red = "";
	//char* purple = ";
	//char* yellow = "";


typedef struct {

	struct {
		int x, y;
	} initpos;
	struct {
		int x, y;
	} pos;
} PIPE;


void makepipe(PIPE* pipe, screendata *screeninfo)
{
srand(time(NULL));
char *colors[] = {
    "#FF0000", // red
    "#00FF00", // green
    "#0000FF", // blue
    "#FFFF00", // yellow
    "#FFA500", // orange
    "#800080", // purple
    "#000000", // black
    "#FFFFFF", // white
    "#00FFFF", // cyan
    "#FFC0CB"  // pink
};
int temp = rand() % 10;
	char* color = colors[temp];

	int len;
	PIPE *ptr = malloc(sizeof(PIPE));
	int direction = rand() % 4;
	if (direction == DOWN)
	{
		int initx = rand() % (screeninfo->dimensions.maxx+1);
		ptr->initpos.x = initx;
		bcurses_add_colored_str(initx, screeninfo->dimensions.maxy, UP_LINE, color);
	}
	else if (direction == UP)
	{
		int initx = rand() % (screeninfo->dimensions.maxx+1);
		ptr->initpos.x = initx;
		bcurses_add_colored_str(initx, 0, UP_LINE, color);

	}
	else if (direction == RIGHT)
	{
		int inity = rand() % (screeninfo->dimensions.maxy+1);
		ptr->initpos.y = inity;
		bcurses_add_colored_str(screeninfo->dimensions.maxx, inity, LEFT_LINE, color);
	}
	else if (direction == LEFT)
	{
		int inity = rand() % (screeninfo->dimensions.maxy+1);
		ptr->initpos.y = inity;
		bcurses_add_colored_str(0, inity, LEFT_LINE, color);
	}

	bcurses_refresh();
}




int main()
{
	bcurses_init_fullscreen();
	screendata *screeninfo = malloc(sizeof(screendata));
	bcurses_getmaxyx(&screeninfo->dimensions.maxx, &screeninfo->dimensions.maxy);
	
	PIPE pipe1;
	makepipe(&pipe1, screeninfo);

	getchar();
	bcurses_kill_scr();
	return 0;
}
