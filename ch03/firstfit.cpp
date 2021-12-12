#include <stdio.h>
#include <stdlib.h>

#define N 7
float item[] = { 0.2, 0.5, 0.4, 0.7, 0.1, 0.3, 0.8 };
float box[N] = { 1, 1, 1, 1, 1, 1, 1 };
int flags[N] = { 0 };

void binningFirst() {
	int index = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (box[j] >= item[i]) {
				box[j] -= item[i];
				flags[i] = j + 1;
				break;
			}
		}
	}
}

int main()
{
	binningFirst();
	for (int i = 0; i < N; i++) 
		printf("box[%d]: %5.2f, flags:%d\n", i, box[i], flags[i]);
	
	return 0;
}

