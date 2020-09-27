#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x, y, t) (t = x, x = y, y = t)
#define N 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int player[N][N], computer[N][N], size;

struct randomNums {
	int a = rand() % size;
	int b = rand() % size;
	int c = rand() % size;
	int d = rand() % size;
};

void inputSize() {
	while (1) {
		printf("Enter the Board size(3 <= size <= 10): ");
		scanf("%d", &size);
		
		if (2 < size && size < 11) {
			return;
		}
	}
}

void makeBoard() {
	int cnt = 1;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			player[i][j] = cnt++;
			computer[i][j] = cnt++;
		}
	}

	for (int i = 0; i < size * 20; i++) {
		struct randomNums A1, A2;
		int temp;

		SWAP(player[A1.a][A1.b], player[A1.c][A1.d], temp);
		SWAP(player[A2.a][A2.b], player[A2.c][A2.d], temp);
	}
}

int main() {
	srand(time(NULL));

	inputSize();
	makeBoard();

	return 0;
}