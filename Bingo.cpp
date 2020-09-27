#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#define SWAP(x, y, t) (t = x, x = y, y = t)

using namespace std;

int inputLevel() {
	int level;

	while (1) {
		system("cls");
		cout << "0: Easy Mode" << endl;
		cout << "1: Hard Mode" << endl;
		cout << "Enter the level(0 or 1): ";
		cin >> level;
		if (level == 0 || level == 1) {
			return level;
		}
	}
}

void printBoard(int A[][5]) {
	system("cls");

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
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

int countBingo(int A[][5]) {
	int bingo = 0, column, row, leftcross, rightcross;

	for (int i = 0; i < 5; i++) {
		column = 0;
		row = 0;

 		for (int j = 0; j < 5; j++) {
			if (A[i][j] == 0) {
				column++;
			}
			if (A[j][i] == 0) {
				row++;
			}
		}

		if (column == 5) {
			bingo++;
		}
		if (row == 5) {
			bingo++;
		}
	}

	leftcross = 0;
	rightcross = 0;

	for (int i = 0; i < 5; i++) {
		if (A[i][i] == 0) {
			leftcross++;
		}
		if (A[i][4 - i] == 0) {
			rightcross++;
		}
	}

	if (leftcross == 5) {
		bingo++;
	}
	if (rightcross == 5) {
		bingo++;
	}

	return bingo;
}

int checker(int player[][5], int com[][5], int num) {
	int flag = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (player[i][j] == num) {
				player[i][j] = 0;
				flag++;
			}
			if (com[i][j] == num) {
				com[i][j] = 0;
				flag++;
			}
			if (flag == 2) {
				return flag;
			}
		}
	}
}

int findWinner(int player, int com) {
	if (player >= 5 || com >= 5) {
		if (player == com) {
			cout << "Draw" << endl;
		}
		else if (player > com) {
			cout << "Player Win!" << endl;
		}
		else {
			cout << "Computer Win!" << endl;
		}
		return 1;
	}
	return 0;
}

void startGame(int player[][5], int com[][5], int level) {
	int num, bingop = 0, bingoc = 0;

	while (1) {
		system("cls");
		printBoard(player);
		printBoard(com);
		cout << "Bingo: " << bingop << endl;
		cout << "Enter the number(Enter 0 to exit): ";
		cin >> num;

		if (num == 0) {
			return;
		}
		else if (num < 1 || num > 25) {
			continue;
		}
		else {
			int flag;

			flag = checker(player, com, num);

			if (flag == 2) {
				bingop = countBingo(player);
				bingoc = countBingo(com);
				if (findWinner(bingop, bingoc)) {
					return;
				}
			}
		}
	}
}

void mixBoard(int A[][5]) {
	for (int i = 0; i < 100; i++) {
		int x1, y1, x2, y2, temp;

		x1 = rand() % 5;
		y1 = rand() % 5;
		x2 = rand() % 5;
		y2 = rand() % 5;

		SWAP(A[y1][x1], A[y2][x2], temp);
	}
}

void makeBoard(int board[][5]) {
	srand(time(NULL));
	int cnt = 1;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			board[i][j] = cnt++;
		}
	}

	mixBoard(board);
}

int main() {
	int computer[5][5], player[5][5], level;

	level = inputLevel();

	makeBoard(player);
	makeBoard(computer);
	startGame(player, computer, level);

	return 0;
}