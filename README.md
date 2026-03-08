# bettercurses
bettercurses is an attempt at making an easier to use option for making cli's similar to the ncurses library. 

It provides easier color support, easy to use support for partial screens, and a stricter error handling which helps you detect problems easier and earlier. 

# Usage
The coordinate system is the exact same as most other libraries including curses. The collumns being vertical rows being horizontal. Here's an example:

TODO: ADD IMAGE

The library has to main systems for initialization of a screen

Partial

TODO: ADD IMAGE

And Fullscreen

TODO: ADD IMAGE

To initialize a Fullscreen just use the

add later with the code thing

To initialize a partial screen do:

add later with the code thing

The initialization is by how many lines to do below the users prompt box. It is reccomended to set this to a ratio to make it scale with varying sizes by doing:

do the code thing marker
init_partial_screen(cols / 5)
// initializes a partial screen the height of 20% of the users terminals height


Note that while you aren't forced to initialize a screen as you can still use functions with a... warying amount of success.
(You probably should just initialize a screen)












