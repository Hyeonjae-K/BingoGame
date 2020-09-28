#define _CRT_SECURE_NO_WARNINGS
#define N 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Board {
	int B[N][N] = { 0 };
};

struct Random {
	int a = rand();
	int b = rand();
	int c = rand();
	int d = rand();
};

struct Condition {
	int size;
	int level;
	int bingo;
};

void swap(int* a, int* b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

int main() {
	srand(time(NULL));

	struct Board player, computer;
	struct Condition condition;

	while (1) {
		system("cls");
		printf("Enter the size(3 <= size <= 10): ");
		scanf("%d", &condition.size);

		if (3 <= condition.size && condition.size <= 10) {
			break;
		}
	}

	while (1) {
		system("cls");
		printf("Enter the level(0: EASY, 1: NORMAL, 2: HARD): ");
		scanf("%d", &condition.level);

		if (0 <= condition.level && condition.level <= 2) {
			break;
		}
	}

	int cnt = 1;
	for (int i = 0; i < condition.size; i++) {
		for (int j = 0; j < condition.size; j++) {
			player.B[i][j] = cnt;
			computer.B[i][j] = cnt;
			cnt++;
		}
	}

	for (int i = 0; i < condition.size * 20; i++) {
		struct Random pRand, cRand;

		swap(&player.B[pRand.a % condition.size][pRand.b % condition.size], &player.B[pRand.c % condition.size][pRand.d % condition.size]);
		swap(&computer.B[cRand.a % condition.size][cRand.b % condition.size], &computer.B[cRand.c % condition.size][cRand.d % condition.size]);
	}

	return 0;
}