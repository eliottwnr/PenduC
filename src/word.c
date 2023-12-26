#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>

#include "word.h"
#include "random.h"


// return the length of the word by the difficulty
int calculateLenWord(int const difficulty){ 
	switch (difficulty){
		case 1: 
			return 5; 
			break; 
		case 2: 
			return 7; 
			break; 
		case 3: 
			return 10; 
			break; 
	}
}


// calculate the number of lines in the file 
int fileLen(FILE *file){
	char character = 0; 
	int numberOfLines = 0; 

	while ((character = fgetc(file)) != EOF){ // while character isn't the end of the file
		if (character == '\n'){ // if the caracter is an end of line
			numberOfLines++;
		}
	}
	return numberOfLines; 
} 


// choose the word to guess randomly
void chooseWord(char *wordToGuess, int const lenWord, int const difficulty){
	FILE *file = NULL; 

	// open the right file by the difficulty
	switch (difficulty){
		case 1: 
			file = fopen("files/easy.wrd", "r"); 
			break; 
		case 2: 
			file = fopen("files/medium.wrd", "r"); 
			break; 
		case 3: 
			file = fopen("files/hard.wrd", "r"); 
			break; 
	}

	if (file == NULL){ // if the file couldn't be opened 
		printw("IMPOSSIBLE D'OUVRIR LE FICHIER\n"); 
		refresh(); 
		exit(0); // quit program 
	}

	// generate a random integer between 0 and the number of lines in the file
	int randomNumber = genRandomNumber(fileLen(file)); 

	fseek(file, (randomNumber * (lenWord+1)), SEEK_SET); // place the cursor in the beginning of the corresponding word
	fscanf(file, "%s", wordToGuess); // put the word in the array 
}	
