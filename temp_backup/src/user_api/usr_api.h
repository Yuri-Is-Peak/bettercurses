#ifndef USR_API
#define USR_API

#include <stdbool.h>

void bcurses_set_fullscreen();
void bcurses_set_partial_screen(int lines, bool mode);
void bcurses_getmaxyx(int* usr_maxx, int* usr_maxy);
void bcurses_addstr(int x, int y, char* text);


#endif
