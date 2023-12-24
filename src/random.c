#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int genRandomNumber(int maxRange){
	srand(time(NULL)); // init rand function
	
	return rand() % maxRange; // return a random number between 0 and maxRange
}
