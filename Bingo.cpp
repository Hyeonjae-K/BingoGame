#define _CRT_SECURE_NO_WARNINGS
#define N 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct board {
	int B[N][N] = { 0 };
};

struct random {
	int a = rand();
	int b = rand();
	int c = rand();
	int d = rand();
};

void swap(int* a, int* b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

int main() {
	srand(time(NULL));

	struct board player, computer;
	int size, level;

	while (1) {
		system("cls");
		printf("Enter the size(3 <= size <= 10): ");
		scanf("%d", &size);

		if (3 <= size && size <= 10) {
			break;
		}
	}

	while (1) {
		system("cls");
		printf("Enter the level(0: EASY, 1: NORMAL, 2: HARD): ");
		scanf("%d", &level);

		if (0 <= level && level <= 2) {
			break;
		}
	}

	int cnt = 1;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			player.B[i][j] = cnt;
			computer.B[i][j] = cnt;
			cnt++;
		}
	}

	for (int i = 0; i < size * 20; i++) {
		struct random pRand, cRand;

		swap(&player.B[pRand.a % size][pRand.b % size], &player.B[pRand.c % size][pRand.d % size]);
		swap(&computer.B[cRand.a % size][cRand.b % size], &computer.B[cRand.c % size][cRand.d % size]);
	}

	return 0;
}