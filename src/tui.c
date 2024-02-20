#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <stdbool.h>
#include <unistd.h>

#include "main.h"

void initCurses(){
	setlocale(LC_ALL, ""); // use default system's locale
	initscr(); 
	cbreak(); 
	keypad(stdscr, TRUE); 
	noecho(); 
	curs_set(0); 
}

bool replay(){
	clear(); 
	mvprintw(1, COLUMN, "Press Q to quit"); 
	mvprintw(3, COLUMN, "Press any other key to replay"); 

	char quit = getch(); 

	if (quit == 'Q' || quit == 'q'){
		return false; 
	}
	refresh(); 

	clear(); 
	return true; 
}
