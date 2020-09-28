#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x, y, t) (t = x, x = y, y = t)
#define N 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int player[N][N], computer[N][N], size, bingo;

struct randomNums {
	int a = rand() % size;
	int b = rand() % size;
	int c = rand() % size;
	int d = rand() % size;
};

void inputSize() {
	while (1) {
		system("cls");

		printf("Enter the Board size(3 <= size <= 10): ");
		scanf("%d", &size);
		
		if (2 < size && size < 11) {
			return;
		}
	}
}

void inputBingo() {
	while (1) {
		system("cls");

		printf("Enter the number of bingo(1 <= bingo <= %d): ", size * 2);
		scanf("%d", &bingo);

		if (0 < bingo && bingo < size * 2 + 1) {
			return;
		}
	}
}

int inputLevel() {
	int level;

	while (1) {
		system("cls");

		printf("Enter the level(0: EASY, 1: NORMAL): ");
		scanf("%d", &level);

		if (level == 0 || level == 1) {
			return level;
		}
	}
}

void makeBoard() {
	int cnt = 1;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			player[i][j] = cnt;
			computer[i][j] = cnt++;
		}
	}

	for (int i = 0; i < size * 20; i++) {
		struct randomNums A1, A2;
		int temp;

		SWAP(player[A1.a][A1.b], player[A1.c][A1.d], temp);
		SWAP(computer[A2.a][A2.b], computer[A2.c][A2.d], temp);
	}
}

void printBoard(int A[][N]) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
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

int countBingo(int board[][N], int num) {
	int row, column, leftCross, rightCross, Bingo = 0;

	for (int i = 0; i < size; i++) {
		row = 0;
		column = 0;

		for (int j = 0; j < size; j++) {
			if (board[i][j] == 0 || board[i][j] == num) {
				row++;
			}
			if (board[j][i] == 0 || board[j][i] == num) {
				column++;
			}
		}

		if (row == size) {
			Bingo++;
		}
		if (column == size) {
			Bingo++;
		}
	}

	leftCross = 0;
	rightCross = 0;

	for (int i = 0; i < size; i++) {
		if (board[i][i] == 0 || board[i][i] == num) {
			leftCross++;
		}
		if (board[i][size - i - 1] == 0 || board[i][size - i -1] == num) {
			rightCross++;
		}
	}

	if (leftCross == size) {
		Bingo++;
	}
	if (rightCross == size) {
		Bingo++;
	}

	return Bingo;
}

int check(int num) {
	int cnt = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (player[i][j] == num) {
				player[i][j] = 0;
				cnt++;
			}
			if (computer[i][j] == num) {
				computer[i][j] = 0;
				cnt++;
			}
			if (cnt == 2) {
				return cnt;
			}
		}
	}

	return cnt;
}

int findWinner(int playerBingo, int computerBingo) {
	if (playerBingo >= bingo || computerBingo >= bingo) {
		system("cls");

		if (playerBingo == computerBingo) {
			printf("Draw\n");
		}
		else if (playerBingo > computerBingo) {
			printf("Player Win!\n");
		}
		else {
			printf("Computer Win!\n");
		}
		printf("\n");

		printf("Player's Board\n");
		printBoard(player);
		printf("Computer's Board\n");
		printBoard(computer);

		printf("Player %d Bingo\n", playerBingo);
		printf("Computer %d Bingo\n", computerBingo);

		return 1;
	}
	
	return 0;
}

int playerTurn(int playerBingo) {
	int num;

	while (1) {
		printBoard(player);

		printf("Player Bingo: %d\n", playerBingo);
		printf("Enter the number(Enter 0 to exit): ");
		scanf("%d", &num);

		if (num == 0) {
			return num;
		}
		else if (num < 0 || num > size * size) {
			continue;
		}
		else {
			if (check(num) == 2) {
				return 1;
			}
		}
	}
}

void computerTurn(int level) {
	int A[N * N] = { 0 }, length = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (computer[i][j] != 0) {
				A[length] = computer[i][j];
				length++;
			}
		}
	}

	if (level == 0) {
		check(A[rand() % length]);
		return;
	}
	else if (level == 1) {
		int maxBingo = 0, num = 0;
		
		for (int i = 0; i < length; i++) {
			if (countBingo(computer, A[i]) > maxBingo) {
				maxBingo = countBingo(computer, A[i]);
				num = A[i];
			}
		}

		if (num == 0) {
			check(A[rand() % length]);
			return;
		}
		else {
			check(num);
			return;
		}
	}
}

void playGame() {
	int num, playerBingo = 0, computerBingo = 0, level;

	level = inputLevel();

	while (1) {
		system("cls");

		if (playerTurn(playerBingo)) {
			playerBingo = countBingo(player, 0);
			computerBingo = countBingo(computer, 0);

			if (findWinner(playerBingo, computerBingo)) {
				return;
			}

			computerTurn(level);

			if (findWinner(playerBingo, computerBingo)) {
				return;
			}
		}
		else {
			return;
		}
	}
}

int main() {
	srand(time(NULL));

	inputSize();
	inputBingo();
	makeBoard();
	playGame();

	return 0;
}