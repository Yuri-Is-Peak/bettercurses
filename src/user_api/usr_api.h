#ifndef BCURSES_USR_API
#define BCURSES_USR_API

// todo add macros
int bcurses_init_fullscreen();
int bcurses_init_partial_screen(int lines);
void bcurses_add_str(int x, int y, char* text);
void bcurses_move_cursor(int x, int y);
void bcurses_getmaxyx(int *maxx, int *maxy);


#endif
