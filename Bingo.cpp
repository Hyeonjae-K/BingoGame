#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#define SWAP(x, y, t) (t = x, x = y, y = t)

using namespace std;

void printBoard(int A[][5]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%3d", A[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void mixBoard(int A[][5]) {
	int temp;
	srand(time(NULL));

	for (int i = 0; i < 100; i++) {
		int x1, y1, x2, y2;
		x1 = rand() % 5;
		y1 = rand() % 5;
		x2 = rand() % 5;
		y2 = rand() % 5;

		SWAP(A[y1][x1], A[y2][x2], temp);
	}
}

void makeBoard(int A[][5]) {
	int cnt = 1;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			A[i][j] = cnt;
			cnt++;
		}
	}

	mixBoard(A);
}

int main() {
	int Board[5][5];
	
	makeBoard(Board);
	printBoard(Board);

	return 0;
}