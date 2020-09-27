#define _CRT_SECURE_NO_WARNINGS
#define N 10
#include <stdio.h>

int player[N][N], computer[N][N], size;

void inputSize() {
	while (1) {
		printf("Enter the Board size(3 <= size <= 10): ");
		scanf("%d", &size);
		
		if (2 < size && size < 11) {
			return;
		}
	}
}

int main() {
	inputSize();

	return 0;
}