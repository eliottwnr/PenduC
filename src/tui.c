#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>

void initCurses(){
	setlocale(LC_ALL, ""); // use default system's locale
	initscr(); 
	cbreak(); 
	keypad(stdscr, TRUE); 
	noecho(); 
	curs_set(0); 
}

void quitCurses(){
	getch(); 
	endwin(); 
}
