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
	int cnt = 1, n = condition.size;

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
		if (bingo.pColumn == condition.size) {
			bingo.pBingo++;
		}
		if (bingo.cRow == condition.size) {
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

int normalMode(int A[], int length) {
	int maxBingo = 0, num = 0;

	for (int k = 0; k < length; k++) {
		struct Bingo bingo;

		for (int i = 0; i < condition.size; i++) {
			bingo.cRow = 0;
			bingo.cColumn = 0;

			for (int j = 0; j < condition.size; j++) {
				if (board.computer[i][j] == 0 || board.computer[i][j] == A[k]) {
					bingo.cRow++;
				}
				if (board.computer[j][i] == 0 || board.computer[j][i] == A[k]) {
					bingo.cColumn++;
				}
			}

			if (bingo.cRow == condition.size) {
				bingo.cBingo++;
			}
			if (bingo.cColumn == condition.size) {
				bingo.cBingo++;
			}
		}

		for (int i = 0; i < condition.size; i++) {
			if (board.computer[i][i] == 0 || board.computer[i][i] == A[k]) {
				bingo.cLeftCross++;
			}
			if (board.computer[i][condition.size - i - 1] == 0 || board.computer[i][condition.size - i - 1] == A[k]) {
				bingo.cRightCross++;
			}
		}

		if (bingo.cLeftCross == condition.size) {
			bingo.cBingo++;
		}
		if (bingo.cRightCross == condition.size) {
			bingo.cBingo++;
		}

		if (maxBingo < bingo.cBingo) {
			maxBingo = bingo.cBingo;
			num = A[k];
		}
	}

	return num;
}

int hardMode(int A[], int length) {
	int num = normalMode(A, length);

	if (num == 0) {
		int maxSum = 0;

		for (int k = 0; k < length; k++) {
			struct Bingo bingo;

			for (int i = 0; i < condition.size; i++) {
				if (board.computer[i][i] == 0 || board.computer[i][i] == A[k]) {
					bingo.cLeftCross++;
				}
				if (board.computer[i][condition.size - i - 1] == 0 || board.computer[i][condition.size - i - 1] == A[k]) {
					bingo.cRightCross++;
				}
			}

			for (int i = 0; i < condition.size; i++) {
				int sum;
				bingo.cRow = 0;
				bingo.cColumn = 0;

				for (int j = 0; j < condition.size; j++) {
					if (board.computer[i][j] == 0 || board.computer[i][j] == A[k]) {
						bingo.cRow++;
					}
					if (board.computer[j][i] == 0 || board.computer[j][i] == A[k]) {
						bingo.cColumn++;
					}
				}

				sum = bingo.cRow + bingo.cColumn + bingo.cLeftCross + bingo.cRightCross;
				if (maxSum < sum) {
					maxSum = sum;
					num = A[k];
				}
			}
		}
	}

	return num;
}

int findWinner(Bingo bingo) {
	if (bingo.pBingo >= condition.bingo || bingo.cBingo >= condition.bingo) {
		system("cls");

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
		printf("\n");

		printf("Player: %d Bingo\n", bingo.pBingo);
		printf("Computer: %d Bingo\n", bingo.cBingo);

		return 1;
	}

	return 0;
}

void computerTurn() {
	int remainNums[N * N] = { 0 }, length = 0, num;

	for (int i = 0; i < condition.size; i++) {
		for (int j = 0; j < condition.size; j++) {
			if (board.computer[i][j] != 0) {
				remainNums[length] = board.computer[i][j];
				length++;
			}
		}
	}

	if (condition.level == 0) {
		num = check(remainNums[rand() % length]);
	}
	else if (condition.level == 1) {
		num = normalMode(remainNums, length);

		if (num == 0) {
			num = check(remainNums[rand() % length]);
		}
	}
	else {
		num = hardMode(remainNums, length);
	}

	check(num);
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

			if (findWinner(bingo)) {
				return 0;
			}

			computerTurn();
			bingo = findBingo();

			if (findWinner(bingo)) {
				return 0;
			}
		}
	}

	return 0;
}