#ifndef BCURSES_INTERN_API
#define BCURSES_INTERN_API

void getmaxyx();
int add_change(char* text);
void debug_print(char* err);
void move_cursor(int x, int y);
void refresh();

#endif
