#ifndef GUESS_H
#define GUESS_H

#define LETTERS_IN_ALPHABET 26 // number of letters in the alphabet

char input(); 
int won(const bool *letterGuessed, int const lenWord); 
void printWordToGuess(char const *wordToGuess, bool const *letterGuessed, int const lenWord); 
int isInWord(char const letter, char const *wordToGuess, bool *letterGuessed, int const lenWord); 
int addLetterTried(int const letter, char *lettersTried); 

#endif
