# bettercurses
bettercurses is an attempt at making an easier to use option for making cli's similar to the ncurses library. It provides an improvement over ncurses in the following areas:
### Easy color support
### Partial screens
### Stricter error handling 

# Usage
The coordinate system is a standard X, Y system. X is the collumns and Y is the rows. To fetch the max size you need to pass pointers to the integers to store them. (size_t is preffered if you dont want compiler to scream at you):
```c
size_t maxx, maxy;
getmaxyx(&maxx, &maxy);
```
The library *currently* has two main systems for initialization of a screen:
### Fullscreen

To initialize a Fullscreen just use the bcurses_init_fullscreen() function:
```C
init_fullscreen(); // Enables the alternate buffer, clearing the screen
```

### Partial_Screen

To initialize a partial screen do:
```C
init_partial_screen(num, mode); // sends num amount of newlines and sets internal variables
// num must be a positive integer larger then zero.
// mode specifies whether you want the screen to restore perfectly or keep the input like in neofetch.
```
The initialization is by how many lines to do below the users prompt box. It is reccomended to set this to a ratio to make it scale with varying sizes by doing:
```C
init_partial_screen(round(cols / 5))
// initializes a partial screen the height of 20% of the users terminals height
```
Please avoid initializing more then one screen before the previous one has been discarded. This will lead to unwanted consequences.

### Hello world
```C
#include <bettercurses.h>
#include <stdio.h>

int main()
{
	// MANDITORY
	bcurses_init_fullscreen(); // initialization

	
	// Main output system is bcurses_add_str. It takes three arguments: the x, y, and the text to be printed.
	bcurses_add_str(0, 0, "Hello world");
	bcurses_refresh(); // actually print the changes

	getchar(); // keep program running
	// MANDITORY
	bcurses_kill_scr(); // reverts users terminal to previous state
	return 0;
}
```

By default, the coordinate system is indexed, meaning 0, 0 are the first valid coordinates. if you want it to be based on count (1, 1 first valid coordinates) you can specify so by calling this function BEFORE initialization:
```C
bcurses_set_count();
```