#ifndef BCURSES_INTERN_API
#define BCURSES_INTERN_API
//############################
//			WARNING
//############################
// DO NOT IMPORT defs.h HERE OR ANY HEADER FILES. IT WILL FUCKING BREAK
//############################
//
void getmaxyx();
int add_change(char* text);
void debug_print(char* err);
void move_cursor(int x, int y);
void refresh();
int eval_coords(int x, int y);
void hex_to_rgb(char* hex, RGB* color);

#endif
