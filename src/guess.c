#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>

#include "guess.h"
#include "main.h"

// safe letter input
char input(){
	char letter = getch(); 
	letter = toupper(letter); // get char to uppercase

	//check if the character is a letter
	if (letter >= 65 && letter <= 90){
		return letter; 
	}
	return 0; 
}	


// return 1 if player has won and 0 if not
int won(const bool *letterGuessed, int const lenWord){
	for (int count = 0; count < lenWord; count++){
		if (letterGuessed[count] == 0){ // if a letter hasn't been discovered yet
			return 0; 
		}
	}

	return 1; 
}


// print * for letters not discovered 
void printWordToGuess(char const *wordToGuess, bool const *letterGuessed, int const lenWord){ 
	char *wordToPrint = NULL; 

	wordToPrint = malloc(lenWord * sizeof(char)); 
	if (wordToPrint == NULL){ // if malloc didn't worked 
		clear(); 
		printw("ERREUR RAM DANS guess.c\n");
		refresh(); 
		sleep(1); 
		exit(0); // exit program 
	}

	for (int count = 0; count < lenWord; count++){
		if (letterGuessed[count]){ // if the letter has been discovered 
			wordToPrint[count] = wordToGuess[count]; // add it clearly to wordToPrint
		}
		else {
			wordToPrint[count] = '*'; 
		}
	}
	mvprintw(1, COLUMN, "Le mot à trouver est : %s\n", wordToPrint); 
	refresh(); 

	free(wordToPrint); // free dynamically allocated space 
}


// check if the letter gived is in the word
int isInWord(char const letter, char const *wordToGuess, bool *letterGuessed, int const lenWord){
	int inWord = 0; 
	for (int count = 0; count < lenWord; count++){
		if (letter == wordToGuess[count]){
			letterGuessed[count] = true; 
			inWord = 1; // don't return immediately in case there is multiple times the letter in the word
		}
	}
	return inWord; 
}


// add letter to the array of false-tried letters
int addLetterTried(int const letter, char *lettersTried){
	for (int count = 0; count < LETTERS_IN_ALPHABET; count++){
		if (lettersTried[count] == letter){ // if the letter is already in the array 
			return 1; // don't add it 2 times
		}
	}

	for (int count = LETTERS_IN_ALPHABET-1; count > 0; count--){
		lettersTried[count] = lettersTried[count-1]; // gives space for the letter to add
	}
	lettersTried[0] = letter; // add the last letter to the 1st box
	return 0; 
}


// draw a hangman based on attempts
void drawHangman(int try) {
   	// Define the different stages of the hangman
	char *hangman[] = {         
		"            ____\n           |    |\n           O    |\n          /|\\   |\n          / \\   |\n                |\n          =======",
		"            ____\n           |    |\n           O    |\n          /|\\   |\n          /     |\n                |\n          =======",         
		"            ____\n           |    |\n           O    |\n          /|\\   |\n                |\n                |\n          =======",         
       		"            ____\n           |    |\n           O    |\n          /|    |\n                |\n                |\n          =======",         
       		"            ____\n           |    |\n           O    |\n           |    |\n                |\n                |\n          =======",
       		"            ____\n           |    |\n           O    |\n                |\n                |\n                |\n          =======",
		"            ____\n           |    |\n                |\n                |\n                |\n                |\n          ======="
   	};     
	// Display the appropriate hangman stage
	mvprintw(2, 0, "%s\n", hangman[try]); 
	refresh(); 
}
