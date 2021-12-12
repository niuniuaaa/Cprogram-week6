#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OVERFLOW	-1
typedef struct {
	unsigned int weight;//Ȩ��
	unsigned int partent, lchild, rchild;
}HTNode,* HuffmanTree;
typedef int Status;
typedef char** HuffmanCode;

void Select(HuffmanTree* HT, int n, int* s1, int* s2) {
	int i;
	unsigned int min = 9999;
	int temp1 = 0, temp2 = 0;
	for (i = 1;i <= n;i++) {
		if ((*HT)[i].partent == 0 && (*HT)[i].weight < min) {
			min = (*HT)[i].weight;
			temp1 = i;
		}
	}
	*s1 = temp1;
	min = 9999;
	for (i = 1;i <= n;i++) {
		if ((*HT)[i].partent == 0 && (*HT)[i].weight < min && temp1 != i) {
			min = (*HT)[i].weight;
			temp2 = i;
		}
	}
	*s2 = temp2;
}
void HuffmanCoding(HuffmanTree* HT, HuffmanCode* HC, int w[], int n) {
	//w���n���ַ���Ȩֵ(��>0)�������������HT�������n���ַ��Ĺ���������HC��
	if (n <= 1)return;
	int m = 2 * n - 1;
	(*HT) = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	if (!(*HT))exit(OVERFLOW);
	int i;
	for (i = 1;i <= n;++i) {
		(*HT)[i].weight = w[i];//Ȩֵ
		(*HT)[i].partent = 0;
		(*HT)[i].lchild = 0;
		(*HT)[i].rchild = 0;
	}
	for (i=n+1;i <= m;++i) {
		(*HT)[i].weight = 0;
		(*HT)[i].partent = 0;
		(*HT)[i].lchild = 0;
		(*HT)[i].rchild = 0;
	}
	int s1, s2;
	for (i = n + 1;i <= m;++i) {	//����������
		//��HT[1...i-1]ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1��s2
		Select(HT, i - 1, &s1, &s2);
		(*HT)[s1].partent = i;(*HT)[s2].partent = i;
		(*HT)[i].lchild = s1;(*HT)[i].rchild = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
	}
	//---��Ҷ�ӵ���������ÿ���ַ��Ĺ���������---
	(*HC) = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	if (!(*HC))exit(OVERFLOW);
	char* cd = (char*)malloc(n * sizeof(char));
	if (!cd)exit(OVERFLOW);
	cd[n - 1] = '\0';
	for (int i = 1;i <= n;++i) {
		int start = n - 1;
		int f = 0;
		for (int c = i, f = (*HT)[i].partent;f != 0;c = f, f = (*HT)[f].partent)
			if ((*HT)[f].lchild == c)cd[--start] = '0';
			else cd[--start] = '1';
		(*HC)[i] = (char*)malloc((n - start) * sizeof(char));
		if (!(*HC)[i])exit(OVERFLOW);
		strcpy((*HC)[i], &cd[start]);
	}
	free(cd);
}


int main() {
	HuffmanTree HT;
	HuffmanCode HC;
	printf("������������ַ�����:");
	int n;
	scanf("%d", &n);
	int w[100];
	printf("�������Ӧ�ַ���Ȩֵ:");
	for (int i = 1;i <= n;i++) {
		scanf("%d", &w[i]);
	}
	HuffmanCoding(&HT, &HC, w, n);
	for (int i = 1;i <= 2 * n - 1;i++) {
		printf("%d:\t%d\t%d\t%d\t%d\n", i, HT[i].weight, HT[i].partent, HT[i].lchild, HT[i].rchild);
	}
	for (int i = 1;i <= n;i++) {
		printf("ȨֵΪ%d�Ĺ���������:%s\n", w[i],HC[i]);
	}
}

