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

struct Bingo {
	int row = 0;
	int column = 0;
	int leftCross = 0;
	int rightCross = 0;
	int bingo = 0;
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
	
	while (1) {
		struct Bingo p, c;
		int num;

		system("cls");

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				printf("%3d", player.B[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		printf("Bingo: %d", p.bingo);
		printf("Enter the number(Enter 0 to exit): ");
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

			if (cnt == 0) {
				continue;
			}
			else {
				p.bingo = 0;
				c.bingo = 0;

				for (int i = 0; i < size; i++) {
					p.row = 0;
					p.column = 0;
					c.row = 0;
					c.column = 0;

					for (int j = 0; j < size; j++) {
						if (player.B[i][j] == 0) {
							p.row++;
						}
						if (player.B[j][i] == 0) {
							p.column++;
						}
						if (computer.B[i][j] == 0) {
							c.row++;
						}
						if (computer.B[j][i] == 0) {
							c.column++;
						}
					}

					if (p.row == size) {
						p.bingo++;
					}
					if (p.column == size) {
						p.bingo++;
					}
					if (c.row == size) {
						c.bingo++;
					}
					if (c.column == size) {
						c.bingo++;
					}
				}

				p.leftCross = 0;
				p.rightCross = 0;
				c.leftCross = 0;
				c.rightCross = 0;

				for (int i = 0; i < size; i++) {
					if (player.B[i][i] == 0) {
						p.leftCross++;
					}
					if (player.B[i][size - i - 1] == 0) {
						p.rightCross++;
					}
					if (computer.B[i][i] == 0) {
						c.leftCross++;
					}
					if (computer.B[i][size - i - 1] == 0) {
						c.rightCross++;
					}
				}

				if (p.leftCross == size) {
					p.bingo++;
				}
				if (p.rightCross == size) {
					p.bingo++;
				}
				if (c.leftCross == size) {
					c.bingo++;
				}
				if (c.rightCross == size) {
					c.bingo++;
				}
			}
		}
	}

	return 0;
}