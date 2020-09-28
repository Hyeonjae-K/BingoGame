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

		printf("Enter the number of bingo(1 <= bingo <= %d): ", size * 2 + 2);
		scanf("%d", &bingo);

		if (0 < bingo && bingo < size * 2 + 3) {
			return;
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
			printf("%3d", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	srand(time(NULL));

	inputSize();
	inputBingo();
	makeBoard();

	return 0;
}