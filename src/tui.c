#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void initCurses(){
	initscr(); 
	cbreak(); 
	keypad(stdscr, TRUE); 
	echo(); 
}

void quitCurses(){
	getch(); 
	endwin(); 
}
