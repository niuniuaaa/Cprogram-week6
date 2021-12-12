#include<stdio.h>
#include<stdlib.h>

double **w;
double **e;
int **s;
double *p;
double *q;
int n;

void init() {
	printf("请输入结点数");
	scanf("%d", &n);
	w = (double**)malloc(sizeof(double*) * (n + 2));	
	e = (double**)malloc(sizeof(double*) * (n + 2));		
	s = (int**)malloc(sizeof(int*) * (n + 1));	
	for (int i = 0; i <= n; ++i) {
		w[i] = (double*)malloc(sizeof(double) * (n + 2));
		e[i] = (double*)malloc(sizeof(double) * (n + 2));
		s[i] = (int*)malloc(sizeof(int) * (n + 1));
	}
	w[n + 1] = (double*)malloc(sizeof(double) * (n + 2));
	e[n + 1] = (double*)malloc(sizeof(double) * (n + 2));
	p = (double*)malloc(sizeof(double) * (n + 1));
	q = (double*)malloc(sizeof(double) * (n + 1));
	printf("请输入小于1号结点的概率");
	scanf("%lf", &q[0]);
	for (int i = 1; i <= n; ++i) {
		printf("请输入%d号结点的概率", i);
		scanf("%lf", &p[i]);
		printf("请输入%d到%d号结点的概率", i, i + 1);
		scanf("%lf", &q[i]);
	}	
}

void buildtree() {
	for (int i = 1; i <= n + 1; ++i) {
		int o = w[i][i - 1];
		w[i][i - 1] = q[i - 1];
		e[i][i - 1] = q[i - 1];
	}
	for (int r = 1; r <= n; ++r) {
		for (int i = 1; i <= n - r + 1; ++i) {
			int j = i + r - 1;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			e[i][j] = INT_MAX;
			for (int k = i; k <= j; ++k) {
				double temp = e[i][k - 1] + e[k + 1][j] + w[i][j];
				if (temp < e[i][j]) {
					s[i][j] = k;
					e[i][j] = temp;
				}
			}
		}
	}
	printf("最小的值为%f\n", e[1][n]);
}

int root(int a, int b) {
	if (a == b) return s[a][b];
	if (a == s[a][b]) {
		printf("%d的右子树为%d\n", a, root(a + 1, b));
		return s[a][b];
	}
	if (b == s[a][b]) {
		printf("%d的左子树为%d\n", b, root(a, b - 1));
		return s[a][b];
	}
	printf("%d的左子树为%d\n", s[a][b], root(a, s[a][b] - 1));
	printf("%d的右子树为%d\n", s[a][b], root(s[a][b] + 1, b));
}

int main() {
	init();
	buildtree();
	root(1, n);
	return 0;
} 

