#include <stdbool.h>
#include <stddef.h>



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
		size_t capacity; 
		size_t len;
		} err_list;
	
	struct {
		char* pointer;
		size_t capacity;
		size_t len;
	} changes;

	struct {
		char* pointer;
		size_t capacity; 
		size_t len;
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


