#ifndef BETTERCURSES
#define BETTERCURSES

#include <usr_api.h>
#include <init.h>

// init 
#include <init.h>
int bcurses_init_screen();
void bcurses_destroy_scr();


// shared api
#include <shared_api.h>
void bcurses_refresh();

// user_api
void bcurses_getmaxyx(int* usr_maxx, int* usr_maxy);
void bcurses_move_cursor(int x, int y);
void bcurses_addstr(int x, int y, char* text);


#endif
