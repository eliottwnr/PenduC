#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>

#include "main.h"
#include "guess.h"
#include "word.h"
#include "tui.h"


// safe input
int setDifficulty(){
	char difficulty = 0; 
	do {
		mvprintw(2, COLUMN, "(1 = facile, 2 = moyenne, 3 = difficile)");  
		mvprintw(1, COLUMN, "Entrer la difficulté");  
		difficulty = getch(); 
		refresh(); 


		switch (difficulty){
			case '1': 
				return 1; 
			case '2': 
				return 2; 
			case '3': 
				return 3; 
			default: 
				clear(); 
				mvprintw(1, COLUMN, "Ceci n'est pas une lettre ! "); 
				refresh(); 
				sleep(1); 
				clear(); 
		}
	} while (difficulty > '3' || difficulty < '1'); 

	clear(); 
}

int main(int argc, char argv[]){
	initCurses(); 

	int difficulty = setDifficulty(); 

	int lenWord = calculateLenWord(difficulty); 

	char *wordToGuess = NULL; 
	wordToGuess = malloc(lenWord * sizeof(char)); 

	bool *letterGuessed = NULL; 
	letterGuessed = malloc(lenWord * sizeof(bool)); 

	// if allocation didn't worked 
	if (wordToGuess == NULL || letterGuessed == NULL){
		clear(); 
		mvprintw(1, COLUMN, "ERREUR RAM DANS main.c"); 
		refresh(); 
		sleep(1); 
		exit(0); // quit program 
	}

	// init the letterGuessed array to false
	for (int count = 0; count < lenWord; count++){
		letterGuessed[count] = false; 
	}

	chooseWord(wordToGuess, lenWord, difficulty); // choose a random word 

	char lettersTried[LETTERS_IN_ALPHABET] = {0}; 
	
	int try = 6; // initial number of tries 
	char letter = 0; 

	while (!won(letterGuessed, lenWord)){ // if there is at least 1 try and the user hasn't won
		printWordToGuess(wordToGuess, letterGuessed, lenWord); 
		drawHangman(try); 

		mvprintw(10, COLUMN, "Lettres pas dans le mot : %s", lettersTried); 
		refresh(); 

		do {
			letter = input(); 

			if (!letter){
				move(12, COLUMN); 
				mvprintw(12, COLUMN, "Ceci n'est pas une lettre ! "); 
				refresh(); 

				sleep(1); 
				move(12, COLUMN); 
				clrtoeol(); 
				refresh(); 
			}
		} while (!letter); // while the character given isn't a letter
		
		if (!isInWord(letter, wordToGuess, letterGuessed, lenWord)){
			if (!addLetterTried(letter, lettersTried)){ // if the letter hasn't been tried previously
				try--;
			}
			if (try == 0){
				break; 
			}	
		}
	}

	// end of the game
	clear(); 
	drawHangman(try); 

	if (try == 0){
		mvprintw(12, COLUMN, "Perdu ... le mot était %s", wordToGuess); 
	}
	else {
		mvprintw(12, COLUMN, "Gagné ! le mot était %s", wordToGuess); 
	}
	refresh(); 

	sleep(1); 
	mvprintw(14, COLUMN, "Appuyer sur une touche pour quitter..."); 
	refresh(); 

	// free dynamically allocated ram 
	free(wordToGuess);
	free(letterGuessed); 

	quitCurses(); 
	return 0; 
}
