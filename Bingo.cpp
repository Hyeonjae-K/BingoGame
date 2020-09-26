#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#define SWAP(x, y, t) (t = x, x = y, y = t)

using namespace std;

void mixBoard(int A[][5]) {
	int temp;
	srand(time(NULL));

	for (int i = 0; i < 100; i++) {
		SWAP(A[rand() % 25][rand() % 25], A[rand() % 25][rand() % 25], temp);
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


	return 0;
}