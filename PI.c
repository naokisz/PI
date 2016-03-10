#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_OF_VALUE 10000
#define NUM_OF_GEEN 20

typedef struct {
	double fitness;//遺伝子の適応度
	double x[NUM_OF_VALUE];
	double y[NUM_OF_VALUE];
	int within_circle;//点が円内に入ったか
	double pi;
}GEEN;
GEEN geen[NUM_OF_GEEN];

int comp (const void *a, const void *b);
int calc_fitness(void);

int main(void) {

	int i, j;

	srand(time(NULL));

	for(i = 0; i < NUM_OF_GEEN; i++)
		for(j = 0; j < NUM_OF_VALUE; j++) {
			geen[i].x[j] = (double)rand() / RAND_MAX;
			geen[i].y[j] = (double)rand() / RAND_MAX;
	}

	calc_fitness();

	for(;;) {
		qsort(geen, NUM_OF_GEEN, sizeof(GEEN), comp);

		printf("M_PIとの差：%.15lf\n", geen[0].fitness);
		printf("within_circle:%d\n", geen[0].within_circle);
		printf("pi:%.15lf\n", geen[0].pi);

		for(i = 1; i < NUM_OF_GEEN - 1; i++) {
			for(j = 0; j < NUM_OF_VALUE; j++) {
				geen[i].x[j] = (double)rand() / RAND_MAX;
				geen[i].y[j] = (double)rand() / RAND_MAX;
			}
		}

		calc_fitness();
	}

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

int calc_fitness(void) {

	int i, j;

	for(i = 0; i < NUM_OF_GEEN; i++) {

		geen[i].within_circle = 0;

		/*円内に点があるかの判定*/
		for(j = 0; j < NUM_OF_VALUE; j++) {
			if((pow(geen[i].x[j], 2) + pow(geen[i].y[j], 2)) < 1) {
				geen[i].within_circle++;
			}
		}

		//遺伝子からの結果がどのぐらい円周率に近いか（適応度）を計算
		geen[i].fitness = fabs(M_PI - ((4 * (double)geen[i].within_circle) / (double)NUM_OF_VALUE));
		geen[i].pi = ((4 * (double)geen[i].within_circle) / (double)NUM_OF_VALUE);
	}

	return 0;
}


