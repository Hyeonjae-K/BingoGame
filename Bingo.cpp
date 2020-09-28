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

void swap(int* a, int* b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

int main() {
	srand(time(NULL));

	struct Board player, computer;
	int size, bingo, level;

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
		printf("Enter the number of bingo(1 <= bingo <= %d): ", size * 2 + 2);
		scanf("%d", &bingo);

		if (1 <= bingo && bingo <= size * 2 + 2) {
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
		struct Random pRand, cRand;

		swap(&player.B[pRand.a % size][pRand.b % size], &player.B[pRand.c % size][pRand.d % size]);
		swap(&computer.B[cRand.a % size][cRand.b % size], &computer.B[cRand.c % size][cRand.d % size]);
	}

	int num;
	while (1) {
		system("cls");

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				printf("%3d", player.B[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		printf("Enter the number: ");
		scanf("%d", &num);

		if (num == 0) {
			return 0;
		}
		else if (1 <= num && num <= size * size) {
			int cnt = 0;

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (player.B[i][j] == num) {
						player.B[i][j] = 0;
						cnt++;
					}
					if (computer.B[i][j] == num) {
						computer.B[i][j] = 0;
						cnt++;
					}
					if (cnt == 2) {
						break;
					}
				}
				if (cnt == 2) {
					break;
				}
			}

			if (cnt != 2) {
				continue;
			}
		}
	}

	return 0;
}