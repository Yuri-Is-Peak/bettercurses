#include <stdbool.h>
#include <stddef.h>

// search for "tdoo" in the src path to find unfinished parts which need to get done

/*
##########################
###       TODO         ###
##########################
//
INTERN 
// 			   NOTDONE
########################################



//				DONE
########################################
void add_debug_print(char* err)
void getmaxyx()
void add_change(char* text)


USR API
//				NOTDONE
########################################



//				DONE
########################################
void bcurses_set_partial_screen(int lines)
void bcurses_set_fullscreen()
void bcurses_refresh()
void bcurses_move_cursor(int x, int y)
void bcurses_getmaxyx(int* maxx, int* maxy)
void bcurses_init_screen()
void bcurses_destroy_scr()
void bcurses_addstr(int x, int y, char* text)

*/

#define OCTAL_ESC "\033["
/* This code has a [
 * some escape sequences do not have this. 
 * However most do. Having a [ is a lot more common.
 * But we still need the other version, albeit rarely
 * This is why there is a seperate macro for that. */
#define OCTAL_ESC_ALT "\033"
#define SAVE_SCR "?1049h"
#define RESTORE_SCR "?1049l"
#define VISIBLE_CURSOR "?25h"
#define INVISIBLE_CURSOR "?25l"

/* 1: block blinking
 * 2: block not blink 
 * 3: underline blink 
 * 4: underline not blink 
 * 5: blinking line 
 * 6: not blinking line */
#define CURSOR_MODE " q"
/* SAVE_CURSOR
 * OCTAL_ESC_ALT7 to save cursor pos
 * OCTAL_ESC_ALT8 to load the saved cursor pos */

//#########################################
// Global tracking for state
typedef struct {
	struct {
		int maxx;
		int maxy;
		} dimensions;

	struct {
		char* pointer;
		int capacity; 
		int len;
		} err_list;
	
	struct {
		char* pointer;
		int capacity;
		int len;
	} changes;

	struct {
		char* pointer;
		int capacity; 
		int len;
		} screen;

	struct {
		bool fullscreen;
		bool partial_screen;
	} screen_mode;

	struct {
		int lines;
		bool restore_full;
		} partial_info;

} ScreenState;

extern ScreenState* mainscr;


