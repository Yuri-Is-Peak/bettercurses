# bettercurses
bettercurses is an attempt at making an easier to use option for making cli's similar to the ncurses library. It provides an improvement over ncurses in the following areas:
### Easy color support
### Partial screens
### Stricter error handling 

# Usage
The coordinate system is a standard X, Y system. X is the collumns and Y is the rows. The library provides you with globals called maxx and maxy which are updated when you call:
```c
getmaxyx(); // updates global maxx and maxy variables
```
Note that these variables are not the internal ones used for error validation and other things. You can do anyting you want with them and it shouldn't break anything.

The library *currently* has to main systems for initialization of a screen:
### Fullscreen

To initialize a Fullscreen just use the init_fullscreen() function:
```C
init_fullscreen(); // Clears the screen and sets up the coordinate grid
```

### Partial_Screen

To initialize a partial screen do:
```C
init_partial_screen(num); // sends num amount of newlines and sets internal variables
// num must be a positive integer larger then zero.
```
The initialization is by how many lines to do below the users prompt box. It is reccomended to set this to a ratio to make it scale with varying sizes by doing:
```C
init_partial_screen(round(cols / 5))
// initializes a partial screen the height of 20% of the users terminals height
```
Please avoid initializing more then one screen before the previous one has been discarded. This will lead to unwanted consequences.

Note that while you aren't forced to initialize a screen as you can still use functions with a... warying amount of success. Something like:
```C
getmaxyx();
```
Will still work, however a lot of functions like add_str depend on the screen being initialized, as the error handling is embedded in most functions and it relies on internal variables which wont exist if a screen isnt initialized.
