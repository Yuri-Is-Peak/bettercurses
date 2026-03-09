#ifndef BETTERCURSES_H
#define BETTERCURSES_H


// Globals
int maxy;
int maxx;


void init_fullscreen();
void getmaxyx();;
void cursor_visibility(bool value);
void move_cursor(int x, int y);
void cursor_mode(int mode, bool Blink);
void exit_cleanup();
char* get_key();

// "add_x" functions
void add_int(int x, int y, int num);
void add_float(int x, int y, float flt);
void add_str(char text[], int x, int y);
void add_colored_str(char text[], int x, int y, int red, int green, int blue);


#endif
