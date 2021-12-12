#include <stdio.h>
#include <stdlib.h>

#define N 7
float item[] = { 0.2, 0.5, 0.4, 0.7, 0.1, 0.3, 0.8 };
float box[N] = { 1, 1, 1, 1, 1, 1, 1 };
int flags[N] = { 0 };

void binningNextFit() {
	int index = 0;
	for (int i = 0; i < N; i++) {
		if (item[i] <= box[index]) {
			box[index] -= item[i];
			flags[i] = index + 1;	
		}
		else {
			index++;
			box[index] -= item[i];
			flags[i] = index + 1;
		}
	}
}

int main()
{
	binningNextFit();
	for (int i = 0; i < N; i++) 
		printf("box[%d]: %5.2f, flags:%d\n", i, box[i], flags[i]);
	
	return 0;
}

