#include <stdio.h>
#include <stdlib.h>

#define N 7
float item[] = { 0.2, 0.5, 0.4, 0.7, 0.1, 0.3, 0.8 };
float box[N] = { 1, 1, 1, 1, 1, 1, 1 };
int flags[N] = { 0 };


//数据的类型要设置对， 索引设置为int， 数据类型设置为float
void binningFirst() {
	for (int i = 0; i < 6; i++) {
		float min = 1;
		int index = 0;
		for (int j = 0; j < N; j++) {
			float tmp = box[j] - item[i];
			if (tmp >= 0 && tmp < min) {
				min = tmp;
				index = j;
			}
		}
		box[index] -= item[i];
		flags[i] = index + 1;
	}
}

int main()
{
	binningFirst();
	for (int i = 0; i < N; i++) 
		printf("box[%d]: %5.2f, flags:%d\n", i, box[i], flags[i]);
	
	return 0;
}

