#define _CRT_SECURE_NO_WARNINGS
#define N 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Board {
	int player[N][N] = { 0 };
	int computer[N][N] = { 0 };
}board;

struct Condition {
	int size = 0;
	int bingo = 0;
	int level = 0;
}condition;

struct Random {
	int a = rand();
	int b = rand();
	int c = rand();
	int d = rand();
};

struct Bingo {
	int pRow = 0, pColumn = 0, pLeftCross = 0, pRightCross = 0, pBingo = 0;
	int cRow = 0, cColumn = 0, cLeftCross = 0, cRightCross = 0, cBingo = 0;
};

void swap(int* a, int* b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

void inputCondition() {
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
		printf("Enter the number of bingo(1 <= bingo <= %d): ", condition.size * 2 + 2);
		scanf("%d", &condition.bingo);

		if (1 <= condition.bingo && condition.bingo <= condition.size * 2 + 2) {
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
}

void makeBoard() {
	int cnt = 0, n = condition.size;

	for (int i = 0; i < condition.size; i++) {
		for (int j = 0; j < condition.size; j++) {
			board.player[i][j] = cnt;
			board.computer[i][j] = cnt;
			cnt++;
		}
	}

	for (int i = 0; i < condition.size * 20; i++) {
		struct Random pRand, cRand;

		swap(&board.player[pRand.a % n][pRand.b % n], &board.player[pRand.c % n][pRand.d % n]);
		swap(&board.computer[cRand.a % n][cRand.b % n], &board.computer[cRand.c % n][cRand.d % n]);
	}
}

void printBoard(int A[N][N]) {
	for (int i = 0; i < condition.size; i++) {
		for (int j = 0; j < condition.size; j++) {
			if (A[i][j] == 0) {
				printf("  X");
			}
			else {
				printf("%3d", A[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

int inputNumber(int bingo) {
	int num;
	
	printf("Bingo: %d\n", bingo);
	printf("Enter the number(Enter 0 to exit): ");
	scanf("%d", &num);

	return num;
}

int check(int num) {
	int cnt = 0;

	if (num < 1 || condition.size * condition.size < num) {
		return 0;
	}

	for (int i = 0; i < condition.size; i++) {
		for (int j = 0; j < condition.size; j++) {
			if (board.player[i][j] == num) {
				board.player[i][j] = 0;
				cnt++;
			}
			if (board.computer[i][j] == num) {
				board.computer[i][j] = 0;
				cnt++;
			}
			if (cnt == 2) {
				return 1;
			}
		}
	}

	return 0;
}

Bingo findBingo() {
	struct Bingo bingo;

	for (int i = 0; i < condition.size; i++) {
		bingo.pRow = 0;
		bingo.pColumn = 0;
		bingo.cRow = 0;
		bingo.cColumn = 0;

		for (int j = 0; j < condition.size; j++) {
			if (board.player[i][j] == 0) {
				bingo.pRow++;
			}
			if (board.player[j][i] == 0) {
				bingo.pColumn++;
			}
			if (board.computer[i][j] == 0) {
				bingo.cRow++;
			}
			if (board.computer[j][i] == 0) {
				bingo.cColumn++;
			}
		}

		if (bingo.pRow == condition.size) {
			bingo.pBingo++;
		}
		if (bingo.cColumn == condition.size) {
			bingo.pBingo++;
		}
		if (bingo.pRow == condition.size) {
			bingo.cBingo++;
		}
		if (bingo.cColumn == condition.size) {
			bingo.cBingo++;
		}
	}

	for (int i = 0; i < condition.size; i++) {
		if (board.player[i][i] == 0) {
			bingo.pLeftCross++;
		}
		if (board.player[i][condition.size - i - 1] == 0) {
			bingo.pRightCross++;
		}
		if (board.computer[i][i] == 0) {
			bingo.cLeftCross++;
		}
		if (board.computer[i][condition.size - i - 1] == 0) {
			bingo.cRightCross++;
		}
	}

	if (bingo.pLeftCross == condition.size) {
		bingo.pBingo++;
	}
	if (bingo.pRightCross == condition.size) {
		bingo.pBingo++;
	}
	if (bingo.cLeftCross == condition.size) {
		bingo.cBingo++;
	}
	if (bingo.cRightCross == condition.size) {
		bingo.cBingo++;
	}

	return bingo;
}

int findWinner(Bingo bingo) {
	if (bingo.pBingo >= condition.bingo || bingo.cBingo >= condition.bingo) {
		if (bingo.pBingo == bingo.cBingo) {
			printf("Draw\n");
		}
		else if (bingo.pBingo > bingo.cBingo) {
			printf("Player Win\n");
		}
		else {
			printf("Computer Win\n");
		}
		printf("\n");

		printf("Player's Board\n");
		printBoard(board.player);
		printf("Computer's Board\n");
		printBoard(board.computer);

		return 1;
	}

	return 0;
}

int main() {
	srand(time(NULL));

	inputCondition();
	makeBoard();
	
	struct Bingo bingo;
	int num;
	while (1) {
		system("cls");

		printBoard(board.player);

		num = inputNumber(bingo.pBingo);

		if (num == 0) {
			return 0;
		}
		else {
			if (check(num) == 0) {
				continue;
			}
			bingo = findBingo();
		}




		else if (1 <= num && num <= size * size) {
			int cnt = 0;

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (B.player[i][j] == num) {
						B.player[i][j] = 0;
						cnt++;
					}
					if (B.computer[i][j] == num) {
						B.computer[i][j] = 0;
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
						if (B.player[i][j] == 0) {
							p.row++;
						}
						if (B.player[j][i] == 0) {
							p.column++;
						}
						if (B.computer[i][j] == 0) {
							c.row++;
						}
						if (B.computer[j][i] == 0) {
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
					if (B.player[i][i] == 0) {
						p.leftCross++;
					}
					if (B.player[i][size - i - 1] == 0) {
						p.rightCross++;
					}
					if (B.computer[i][i] == 0) {
						c.leftCross++;
					}
					if (B.computer[i][size - i - 1] == 0) {
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

				if (p.bingo >= bingo || c.bingo >= bingo) {
					system("cls");

					if (p.bingo == c.bingo) {
						printf("Draw\n");
					}
					else if (p.bingo > c.bingo) {
						printf("Player Win!\n");
					}
					else {
						printf("Computer Win!\n");
					}
					printf("\n");

					printf("Player's Board\n");
					for (int i = 0; i < size; i++) {
						for (int j = 0; j < size; j++) {
							if (B.player[i][j] == 0) {
								printf("  X");
							}
							else {
								printf("%3d", B.player[i][j]);
							}
						}
						printf("\n");
					}
					printf("\n");

					printf("Computer's Board\n");
					for (int i = 0; i < size; i++) {
						for (int j = 0; j < size; j++) {
							if (B.computer[i][j] == 0) {
								printf("  X");
							}
							else {
								printf("%3d", B.computer[i][j]);
							}
						}
						printf("\n");
					}
					printf("\n");

					printf("Player: %d Bingo\n", p.bingo);
					printf("Computer: %d Bingo\n", c.bingo);

					return 0;
				}

				int remainNums[N * N] = { 0 }, length = 0;
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < size; j++) {
						if (B.computer[i][j] != 0) {
							remainNums[length] = B.computer[i][j];
							length++;
						}
					}
				}

				if (level == 0) {
					num = remainNums[rand() % length];
				}
				else if (level == 1) {
					int maxBingo = 0, cNum = 0;

					for (int k = 0; k < length; k++) {
						c.bingo = 0;

						for (int i = 0; i < size; i++) {
							c.row = 0;
							c.column = 0;

							for (int j = 0; j < size; j++) {
								if (B.computer[i][j] == 0 || B.computer[i][j] == remainNums[k]) {
									c.row++;
								}
								if (B.computer[j][i] == 0 || B.computer[j][i] == remainNums[k]) {
									c.column++;
								}
							}

							if (c.row == size) {
								c.bingo++;
							}
							if (c.column == size) {
								c.bingo++;
							}
						}

						c.leftCross = 0;
						c.rightCross = 0;
						for (int i = 0; i < size; i++) {
							if (B.computer[i][i] == 0 || B.computer[i][i] == remainNums[k]) {
								c.leftCross++;
							}
							if (B.computer[i][size - i - 1] == 0 || B.computer[i][size - i - 1] == 0) {
								c.rightCross++;
							}
						}

						if (c.leftCross == size) {
							c.bingo++;
						}
						if (c.rightCross == size) {
							c.bingo++;
						}

						if (c.bingo > maxBingo) {
							maxBingo = c.bingo;
							cNum = remainNums[k];
						}
					}

					if (cNum == 0) {
						num = remainNums[rand() % length];
					}
					else {
						num = cNum;
					}
				}
				else {
					int maxBingo = 0, cNum = 0, maxSum = 0, x, y;

					for (int k = 0; k < length; k++) {
						int flag = 0, sum = 0, tx, ty;

						for (int i = 0; i < size; i++) {
							for (int j = 0; j < size; j++) {
								if (B.computer[i][j] == remainNums[k]) {
									ty = i;
									tx = j;
									flag = 1;
									break;
								}
							}

							if (flag != 0) {
								break;
							}
						}

						c.bingo = 0;
						c.leftCross = 0;
						c.rightCross = 0;
						for (int i = 0; i < size; i++) {
							if (B.computer[i][i] == 0 || B.computer[i][i] == remainNums[k]) {
								c.leftCross++;
							}
							if (B.computer[i][size - i - 1] == 0 || B.computer[i][size - i - 1] == remainNums[k]) {
								c.rightCross++;
							}
						}
						sum += c.leftCross;
						sum += c.rightCross;

						for (int i = 0; i < size; i++) {
							c.row = 0;
							c.column = 0;

							for (int j = 0; j < size; j++) {
								if (B.computer[i][j] == 0 || B.computer[i][j] == remainNums[k]) {
									if (j == tx) {
										sum++;
									}
									c.row++;
								}
								if (B.computer[j][i] == 0 || B.computer[j][i] == remainNums[k]) {
									if (j == ty) {
										sum++;
									}
									c.column++;
								}
							}

							if (c.row == size) {
								c.bingo++;
							}
							if (c.column == size) {
								c.bingo++;
							}
							if (c.leftCross == size) {
								c.bingo++;
							}
							if (c.rightCross == size) {
								c.bingo++;
							}
							if (c.bingo == 0) {
								if (maxSum < sum) {
									maxSum = sum;
									y = ty;
									x = tx;
								}
							}
							if (c.bingo > maxBingo) {
								maxBingo = c.bingo;
								cNum = remainNums[k];
							}
						}
					}

					if (maxBingo == 0) {
						num = B.computer[y][x];
					}
					else {
						num = cNum;
					}
				}

				cnt = 0;
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < size; j++) {
						if (B.player[i][j] == num) {
							B.player[i][j] = 0;
							cnt++;
						}
						if (B.computer[i][j] == num) {
							B.computer[i][j] = 0;
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

				p.bingo = 0;
				c.bingo = 0;
				for (int i = 0; i < size; i++) {
					p.row = 0;
					p.column = 0;
					c.row = 0;
					c.column = 0;

					for (int j = 0; j < size; j++) {
						if (B.player[i][j] == 0) {
							p.row++;
						}
						if (B.player[j][i] == 0) {
							p.column++;
						}
						if (B.computer[i][j] == 0) {
							c.row++;
						}
						if (B.computer[j][i] == 0) {
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
					if (B.player[i][i] == 0) {
						p.leftCross++;
					}
					if (B.player[i][size - i - 1] == 0) {
						p.rightCross++;
					}
					if (B.computer[i][i] == 0) {
						c.leftCross++;
					}
					if (B.computer[i][size - i - 1] == 0) {
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

				if (p.bingo >= bingo || c.bingo >= bingo) {
					system("cls");

					if (p.bingo == c.bingo) {
						printf("Draw\n");
					}
					else if (p.bingo > c.bingo) {
						printf("Player Win!\n");
					}
					else {
						printf("Computer Win!\n");
					}
					printf("\n");

					printf("Player's Board\n");
					for (int i = 0; i < size; i++) {
						for (int j = 0; j < size; j++) {
							if (B.player[i][j] == 0) {
								printf("  X");
							}
							else {
								printf("%3d", B.player[i][j]);
							}
						}
						printf("\n");
					}
					printf("\n");

					printf("Computer's Board\n");
					for (int i = 0; i < size; i++) {
						for (int j = 0; j < size; j++) {
							if (B.computer[i][j] == 0) {
								printf("  X");
							}
							else {
								printf("%3d", B.computer[i][j]);
							}
						}
						printf("\n");
					}
					printf("\n");

					printf("Player: %d Bingo\n", p.bingo);
					printf("Computer: %d Bingo\n", c.bingo);

					return 0;
				}
			}
		}
	}

	return 0;
}