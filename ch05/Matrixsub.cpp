#include <stdio.h>
#include <stdlib.h>

#define MAX_MATRIXNUM 100
#define MAX_VALUE 32767

int p[MAX_MATRIXNUM+1], m[MAX_MATRIXNUM+1][MAX_MATRIXNUM+1], s[MAX_MATRIXNUM+1][MAX_MATRIXNUM+1];
static void matrix_chain(int num);
static void traceback(int i, int j);

int main()
{
        int i, num;

        printf("Input matrix num: ");
        scanf("%d", &num);
        getchar();

        printf("Input matrix subscript: ");
        for(i = 0; i <= num; i++){
                scanf("%d", &p[i]);
        }
        getchar();

        matrix_chain(num);
        traceback(1, num);
        printf("\n");

        return 0;
}

static void matrix_chain(int num)
{
        int i, j, l, k, n, temp;

        n = num;
        for(i = 1; i <= n; i++){
                m[i][i] = 0;
        }

        for(l = 2; l <= n; l++){
                for(i = 1; i <= n-l+1; i++){
                        j = i + l - 1;
                        m[i][j] = MAX_VALUE;
                        for(k = i; k < j; k++){
                                temp = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                                if(temp < m[i][j]){
                                        m[i][j] = temp;
                                        s[i][j] = k;
                                }
                        }
                }
        }
        printf("The lowest compute times = %d\n", m[1][num]);
}

static void traceback(int i, int j)
{
        if(i == j){
                printf("A%d", i);
        }
        if(i < j){
                printf("(");
                traceback(i, s[i][j]);
                traceback(s[i][j]+1, j);
                printf(")");
        }
}
