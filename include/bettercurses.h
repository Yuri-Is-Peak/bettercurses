#ifndef BETTERCURSES
#define BETTERCURSES


// init 
#include <init.h>
int bcurses_init_screen();
void bcurses_destroy_scr();


// shared api
#include <shared_api.h>
void bcurses_refresh();
void bcurses_move_cursor(int x, int y);


// user_api
#include <usr_api.h>
void bcurses_set_fullscreen();
void bcurses_set_partial_screen(int lines, bool mode);
void bcurses_getmaxyx(int* usr_maxx, int* usr_maxy);
void bcurses_addstr(int x, int y, char* text);






#endif
