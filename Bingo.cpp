#define _CRT_SECURE_NO_WARNINGS
#define N 100
#include <stdio.h>
#include <stdlib.h>

int main() {
	int size, level;

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
		printf("Enter the level(0: EASY, 1: NORMAL, 2: HARD): ");
		scanf("%d", &level);

		if (0 <= level && level <= 2) {
			break;
		}
	}

	return 0;
}