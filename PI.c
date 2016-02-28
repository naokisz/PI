#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_OF_VALUE 100
#define NUM_OF_GEEN 20

typedef struct {
	unsigned double fitness;//遺伝子の適応度
	unsigned double x[NUM_OF_VALUE];
	unsigned double y[NUM_OF_VALUE];
}GEEN;

int comp (const void *a, const void *b);

int main(void) {

	GEEN geen[NUM_OF_GEEN];
	int i,j,within_circle;

	srand(time(NULL));

	for(i = 0; i < NUM_OF_GEEN; i++)
		for(j = 0; j < NUM_OF_VALUE; j++) {
			geen[i].x[j] = (double)rand() / RAND_MAX;
			geen[i].y[j] = (double)rand() / RAND_MAX;
	}

	for(i = 0; i < NUM_OF_GEEN; i++) {

		within_circle = 0;

		/*円内に点があるかの判定*/
		for(j = 0; j < NUM_OF_VALUE; j++) {
			if((geen[i].x[j]^2 + geen[i].y[j]^2) < 1) {
				within_circle++;
			}
		}
		//遺伝子からの結果がどのぐらい円周率に近いか（適応度）を計算
		fitness[i] = fabs(M_PI - ((4 * within_circle) / NUM_OF_VALUE));
	}

	qsort(geen, NUM_OF_GEEN, sizeof(GEEN), comp);

	return 0;
}

int comp(const void *a, const void *b) {

	GEEN test1 = *(GEEN*)a;
	GEEN test2 = *(GEEN*)b;

	double tmp1 = test1.fitness;
	double tmp2 = test2.fitness;

	if(tmp1 < tmp2) return -1;
	if(tmp1 == tmp2) return 0;
	if(tmp1 > tmp2) return 1;
}

