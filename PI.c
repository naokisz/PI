#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_SEED 100
#define NUM_OF_GEEN 20

struct geen {
	unsigned int seed1[NUM_OF_SEED];
	unsigned int seed2[NUM_OF_SEED];
	unsigned int value1[NUM_OF_SEED];
	unsigned int value2[NUM_OF_SEED];
};

int main(void) {

	struct geen geen[NUM_OF_GEEN];
	int i,j;
	

	srand(time(NULL));
	for(i = 0; i < NUM_OF_GEEN; i++)
		for(j = 0; j < NUM_OF_SEED; j++) {
			geen[i].seed1[j] = rand();
			geen[i].seed2[j] = rand();
			geen[i].value[i] = 
	}

	for(i = 0; i < NUM_OF_SEED; i++) {
		if(rand() {
			
