#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#define NUM_OF_VALUE 100 //XXX 値変えるとsegfaultする
#define NUM_OF_GEEN 20

typedef struct {
	double fitness;//遺伝子の適応度
	double x[NUM_OF_VALUE];
	double y[NUM_OF_VALUE];
}GEEN;
GEEN geen[NUM_OF_GEEN];

int comp (const void *a, const void *b);
int calc_fitness(void);

int main(void) {

	int i, j, tmp;
	int cross_start, cross_end;
	int parent1, parent2;
	int mutation; //突然変異するためのトリガー
	double optimum_solution = 0;

	/*TODO selectionが奇数の時にバグが起こらないか調べる*/
	const int selection = 16; //淘汰する遺伝子の数＝交配する遺伝子の数×２

	srand(time(NULL));

	mutation = ((double)rand() / RAND_MAX) * 100;

	for(i = 0; i < NUM_OF_GEEN; i++)
		for(j = 0; j < NUM_OF_VALUE; j++) {
			geen[i].x[j] = (double)rand() / RAND_MAX;
			geen[i].y[j] = (double)rand() / RAND_MAX;
	}

	calc_fitness();

	for(;;) {
		qsort(geen, NUM_OF_GEEN, sizeof(GEEN), comp);

		printf("M_PIとの差：%.15lf\n", geen[1].fitness);
		sleep(1);
/*		if(optimum_solution == 0) {
			printf("初期最適解：%.15lf\n", geen[1].fitness);
		}

		if(optimum_solution != geen[1].fitness) {
			optimum_solution = geen[1].fitness;
			printf("最適解が変更されました。M_PIとの差：%.15lf\n", optimum_solution);
		}
*/
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

	int within_circle; //円内に点があるか
	int i, j;

	for(i = 0; i < NUM_OF_GEEN; i++) {

		within_circle = 0;

		/*円内に点があるかの判定*/
		for(j = 0; j < NUM_OF_VALUE; j++) {
			if((pow(geen[i].x[j], 2) + pow(geen[i].y[j], 2)) < 1) {
				within_circle++;
			}
		}
		//遺伝子からの結果がどのぐらい円周率に近いか（適応度）を計算
		geen[i].fitness = fabs(M_PI - ((4 * (double)within_circle) / NUM_OF_VALUE));
	}

	printf("円周率：%.15lf\n",(4 * (double)within_circle) / NUM_OF_VALUE);

	return 0;
}


