#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "guess.h"
#include "word.h"


// safe input
int setDifficulty(){
	int difficulty = 1; 
	printf("Difficulté (1 = facile, 2 = moyenne, 3 = difficile) : ");  
	scanf("%d", &difficulty); 
	while (getchar() != '\n'); // clear the buffer 

	return difficulty; 
}


int main(int argc, char argv[]){
	int difficulty = setDifficulty(); 

	int lenWord = calculateLenWord(difficulty); 

	char *wordToGuess = NULL; 
	wordToGuess = malloc(lenWord * sizeof(char)); 

	bool *letterGuessed = NULL; 
	letterGuessed = malloc(lenWord * sizeof(bool)); 

	// if allocation didn't worked 
	if (wordToGuess == NULL || letterGuessed == NULL){
		printf("ERREUR RAM DANS main.c\n"); 
		exit(0); // quit program 
	}

	chooseWord(wordToGuess, lenWord, difficulty); // choose a random word 

	char lettersTried[LETTERS_IN_ALPHABET] = {0}; 
	
	int try = 7; // initial number of tries 
	char letter = 0; 
	while (try > 0 && !won(letterGuessed, lenWord)){ // if there is at least 1 try and the user hasn't won
		printWordToGuess(wordToGuess, letterGuessed, lenWord); 

		printf("Ta lettre : "); 
		letter = input(); // safe letter input 
		printf("\n\n"); 
		if (isInWord(letter, wordToGuess, letterGuessed, lenWord)){
			printf("La lettre %c est dans le mot !\n", letter); 
		}
		else {
			printf("La lettre %c n'est pas dans le mot ...\n", letter); 
			if (!addLetterTried(letter, lettersTried)){ // if the letter hasn't been tried previously
				try--;
			}
			printf("Plus que %d essais\n", try); 
		}
		printf("\n"); 
		printf("Lettres pas dans le mot : %s\n", lettersTried); 
	}

	// end of the game
	if (try == 0){
		printf("Perdu ... le mot était %s\n", wordToGuess); 
	}
	else {
		printf("Gagné ! le mot était %s\n", wordToGuess); 
	}

	// free dynamically allocated ram 
	free(wordToGuess);
	free(letterGuessed); 
	return 0; 
}
