#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_OF_GEEN 20

typedef struct {
	double fitness;//遺伝子の適応度
	double *x;
	double *y;
	int within_circle;//点が円内に入ったか
	double pi;
}GEEN;
GEEN geen[NUM_OF_GEEN];

int num_of_point;

int comp (const void *a, const void *b);
int calc_fitness(void);

int main(int argc, char *argv[]) {

	int i, j;
	double previous_pi;
	int previous_pi_count = 0;

	srand(time(NULL));

	printf("\n円周率計算！\n\n");

	if(argv[1] == "--help") {
		printf("ヘルプ\n\n");
		printf("このプログラムについて\n");
		printf("モンテカルロ法の改良版みたいな方法で円周率を求めます。\n\n");
		printf("オプション\n");
		printf("-n 数字 ：数字で指定された点の数で計算を開始します。\n");
		printf("--help ：このヘルプを表示します\n");
	}

	for(;;) {

		if(argv[1] == "-n") {
			num_of_point = atoi(argv[2]);
			break;
		}

		printf("円周率を求めるために使う点の数を入力してください。\n");
		printf("大きすぎる数字を入力した場合、パソコンがフリーズする可能性があります。\n＞");
		scanf("%d", &num_of_point);
		while(getchar() != '\n') { }
		if(num_of_point == 0) {
			printf("もう一度入力してください。\n");
		} else break;
	}
	
	for(i = 0; i < NUM_OF_GEEN; i++) {

		geen[i].x = (double*)malloc(sizeof(double) * num_of_point);
		geen[i].y = (double*)malloc(sizeof(double) * num_of_point);

		if(geen[i].x == NULL || geen[i].y == NULL) {
			printf("メモリ確保に失敗しました。プログラムを終了します。\n");
			return -1;
		}
	}

	for(i = 0; i < NUM_OF_GEEN; i++)
		for(j = 0; j < num_of_point; j++) {
			geen[i].x[j] = (double)rand() / RAND_MAX;
			geen[i].y[j] = (double)rand() / RAND_MAX;
	}

	calc_fitness();

	for(;;) {
		qsort(geen, NUM_OF_GEEN, sizeof(GEEN), comp);

		printf("\n円周率:%.15lf\n", geen[0].pi);
		printf("正しい円周率との差：%.15lf\n", geen[0].fitness);
		printf("円周率の計算式：%d * 4 / %d\n", geen[0].within_circle, num_of_point);

		if(previous_pi == geen[0].pi && previous_pi_count < 5) {
			previous_pi_count++;
		}

		if(previous_pi == geen[0].pi && previous_pi_count == 4) {
			printf("\n5回同じ計算結果が出たので計算が収束しました。\n");
			break;
		}
		
		if(previous_pi != geen[0].pi) {
			previous_pi = geen[0].pi;
			previous_pi_count = 0;
		}
		
		for(i = 1; i < NUM_OF_GEEN - 1; i++) {
			for(j = 0; j < num_of_point; j++) {
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
		for(j = 0; j < num_of_point; j++) {
			if((pow(geen[i].x[j], 2) + pow(geen[i].y[j], 2)) < 1) {
				geen[i].within_circle++;
			}
		}

		//遺伝子からの結果がどのぐらい円周率に近いか（適応度）を計算
		geen[i].fitness = fabs(M_PI - ((4 * (double)geen[i].within_circle) / (double)num_of_point));
		geen[i].pi = ((4 * (double)geen[i].within_circle) / (double)num_of_point);
	}

	return 0;
}

