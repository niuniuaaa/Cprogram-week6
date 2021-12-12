//头文件  #include "fatal.h"
 
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
 
#define		Error(str)        FatalError(str)
#define		FatalError(str)	  fprintf(stderr,"%s\n",str),exit(1)
 
//定义的二叉树头文件  #include "binary_tree"
 
#ifndef _Tree_H
 
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
typedef double ElementType;
 
SearchTree MakeEmpty( SearchTree T );
Position Find( ElementType X, SearchTree T );
Position FindMax( SearchTree T );
Position FindMin( SearchTree T );
SearchTree Insert( ElementType X, SearchTree T );
SearchTree Delete( ElementType X, SearchTree T );
ElementType DeleteMax( SearchTree T );
void PrintTree(SearchTree T);
void Assign_Judge(SearchTree T);
int Compare_Judge_Count(SearchTree T);
void Transleve(SearchTree T);
#endif
 
struct TreeNode{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
	int count;
	int judge;   //用在Compare_Judge中，在Check_Exist时比较实际的count与多记的数，来排除错误，看代码体会。
};
 
#define False 0
#define True 1
#define POINT_NUM 6
#define DIS_NUM 15
// 对二叉树的操作

 
SearchTree 
MakeEmpty( SearchTree T ){
	if(T != NULL){
		MakeEmpty(T->Left);	
		MakeEmpty(T->Right);	
		free(T);
	}
	return NULL;
}
 
Position 
Find( ElementType X, SearchTree T ){
	if(T == NULL)
		return NULL;
	if(X < T->Element)
		return Find(X, T->Left);
	else if(X > T->Element)
		return Find(X, T->Right);
	else 
		return T;
}
 
Position 
FindMax( SearchTree T ){
	if(T != NULL)
		while(T->Right != NULL)
			T = T->Right;
	return T;
}
 
Position 
FindMin( SearchTree T ){
	if(T == NULL)
		return NULL;
	else if(T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}
 
SearchTree 
Insert( ElementType X, SearchTree T ){
	if(T == NULL){
		T = (SearchTree)malloc(sizeof(struct TreeNode));
		if(T == NULL)
			FatalError("Out of space !");
		else{
			T->Element = X;
			T->Left = T->Right = NULL;
			T->count=1;
		}
	}else if(X < T->Element)
		T->Left = Insert(X, T->Left);
	else if(X > T->Element)
		T->Right = Insert(X, T->Right);
	else
		T->count++;
 
	return T;
}
 
SearchTree 
Delete( ElementType X, SearchTree T ){
	Position TmpCell;
 
	if(T == NULL)
		Error("Element of Delete not found !");
	else if(X < T->Element)
		T->Left = Delete(X, T->Left);
	else if(X > T->Element)
		T->Right = Delete(X, T->Right);
	else if(T->Left && T->Right){
		if(T->count == 1){
			TmpCell = FindMin(T->Right);
			T->Element = TmpCell->Element;
			T->count = TmpCell->count;
			TmpCell->count = 1;
			T->Right = Delete(T->Element, T->Right);
		}else
			T->count--;
	}else{
		if(T->count == 1){
			TmpCell = T;
			if(T->Right == NULL)
				T = T->Left;
			else if(T->Left == NULL)
				T = T->Right;
			free(TmpCell);
		}else
			T->count--;
	}
	return T;
}
 
void
PrintTree(SearchTree T){
	if(T != NULL){
		PrintTree(T->Left);
		printf("Node number: %f , count number: %d, judge number: %d\n",T->Element,T->count,T->judge);
		PrintTree(T->Right);
	}
}
 
ElementType DeleteMax(SearchTree T){
	Position Tmp_Position;
	ElementType Tmp_Mem;
 
	if(T == NULL)
		Error("Element of DeleteMax not found !");
	
	Tmp_Position = FindMax(T);
	
	Tmp_Mem = Tmp_Position->Element;
	printf("DMax is: %f\n",Tmp_Mem);
	Delete(Tmp_Mem, T);
 
	return Tmp_Mem;
}
 
void 
Assign_Judge(SearchTree T){
	if(T != NULL){
		Assign_Judge(T->Left);
		T->judge = 0;
		Assign_Judge(T->Right);
	}
}
 
int 
Compare_Judge_Count(SearchTree T){
	Position Queue[DIS_NUM];
	Position Ptr;
	int front,rear;
	int Flag = True;
 
	front = rear = -1;
	Queue[++rear]=T;
 
	while(front != rear){
		front = (front+1)%DIS_NUM;
		Ptr = Queue[front];
		if(Ptr->count < Ptr->judge){
			Flag = False;
			break;
		}
 
		if(Ptr->Left != NULL){
			rear = (rear+1)%DIS_NUM;
			Queue[rear]=Ptr->Left;
		}
 
		if(Ptr->Right != NULL){
			rear = (rear+1)%DIS_NUM;
			Queue[rear]=Ptr->Right;
		}
	}
	return Flag;
}
 
void 
Transleve(SearchTree T){
	Position Queue[DIS_NUM];
	Position Ptr;
	int front,rear;
	int Flag = True;
 
	front = rear = -1;
	Queue[++rear]=T;
 
	while(front != rear){
		front = (front+1)%DIS_NUM;
		Ptr = Queue[front];
 
		printf("Node is: %f\n",Ptr->Element);
 
		if(Ptr->Left != NULL){
			rear = (rear+1)%DIS_NUM;
			Queue[rear]=Ptr->Left;
		}
 
		if(Ptr->Right != NULL){
			rear = (rear+1)%DIS_NUM;
			Queue[rear]=Ptr->Right;
		}
	}
}
 
 
//算法的实现部分


 
int Check_Exist(ElementType X[], ElementType DMax, SearchTree D, int Left, int Right, int N, int Mark){
	int Flag = True;
	int i,j;
	Position Ptr;
	Assign_Judge(D);
	if(Mark == 0){
		for(i=1,j=Right+1; i<Left || j<=N; i++,j++){
			if(i < Left){
				if(!(Ptr=Find(fabs(X[i]-DMax), D))){
					Flag = False;
					break;
				}else
					Ptr->judge++;
			}
			if(j <= N){
				if(!(Ptr=Find(fabs(X[j]-DMax), D))){
					//printf("j is: %d when Mark==0\n",j);
					Flag = False;
					break;
				}else
					Ptr->judge++;
			}
			Flag = Compare_Judge_Count(D);
			if(Flag == False)
				break;
		}
	}
	if(Mark == 1){
		for(i=1,j=Right+1; i<Left || j<=N; i++,j++){
			if(i < Left){
				printf("fabs(X[N]-X[i]-DMax) is: %f,i is:%d\n",fabs(X[N]-X[i]-DMax),i);
				if(!(Ptr=Find(fabs(X[N]-X[i]-DMax), D))){
					Flag = False;
					break;
				}else
					Ptr->judge++;
			}
			if(j <= N){
				printf("fabs(X[N]-X[j]-DMax) is: %f,j is: %d\n",fabs(X[N]-X[j]-DMax),j);
				if(!(Ptr=Find(fabs(X[N]-X[j]-DMax), D))){
					Flag = False;
					break;
				}else
					Ptr->judge++;
			}
 
 
			Flag = Compare_Judge_Count(D);
			if(Flag == False)
				break;
		}
	}
	return Flag;
}
 
 
int Place(ElementType X[], SearchTree D, int N, int Left, int Right){
	printf("**************now  in Place(X,D,%d,%d,%d)****************\n",N,Left,Right);
	ElementType DMax;
	int Found = False;
	int i,j;
 
	if(D == NULL || Left>Right)
		return True;
	DMax = FindMax(D)->Element;
	if(Check_Exist(X, DMax, D, Left, Right, N, 0)){
		X[Right] = DMax;
 
		for(i=1,j=Right+1; i<Left || j<=N; i++,j++){
			printf("N is:%d now in D,delete x[i,j]\n",N);
			if(i < Left){
				printf("i,X[%d]-DMax is: %f\n",i,fabs(X[i]-DMax));
				Delete(fabs(X[i]-DMax), D);
			}
			if(j <= N){
				printf("j,X[%d]-DMax is: %f\n",j,fabs(X[j]-DMax));
				Delete(fabs(X[j]-DMax), D);
			}
		}
		Found=Place(X, D, N, Left, Right-1);
		if(!Found){
			for(i=1,j=Right+1; i<Left || j<=N; i++,j++){				
				if(i < Left)
					Insert(fabs(X[i]-DMax), D);
				if(j <= N)
					Insert(fabs(X[j]-DMax), D);
			}
		}
	}
 
 
	if(!Found && Check_Exist(X, DMax, D, Left, Right, N, 1)){
		X[Left] = X[N]-DMax;
 
		printf("X[Right] is  X[%d]: %f\n",Right,X[Right]);
		printf("X[Left] is X[%d]: %f\n",Left,X[Left]);
 
 
		for(i=1,j=Right+1; i<Left || j<=N; i++,j++){
			if(i < Left)
				Delete(fabs(X[N]-X[i]-DMax), D);
			if(j <= N)
				Delete(fabs(X[N]-X[j]-DMax), D);
		}
 
 
		Found=Place(X, D, N, Left+1, Right);
		if(!Found){
			for(i=1,j=Right+1; i<Left || j<=N; i++,j++){
				if(i < Left)
					Insert(fabs(X[N]-X[i]-DMax), D);
				if(j <= N)
					Insert(fabs(X[N]-X[j]-DMax), D);
			}
		}
	}
	return Found;
}
 
 
int Turnpike(ElementType X[], SearchTree D,int N){
	X[1]=0;	
	X[N]=FindMax(D)->Element;
	Delete(X[N], D);
 
	X[N-1]=FindMax(D)->Element;
	Delete(X[N-1], D);
 
	if(Find((X[N]-X[N-1]),D)){
		Delete((X[N]-X[N-1]), D);
		printf("***come in Place(X,D,%d,2,%d)***\n",N,N-2);
		
		return Place(X, D, N, 2, N-2);
	}else
		return False;
}
 
 
int main(){
	ElementType Distance[]={3,3,3,8,6,4,5,5,5,2,2,2,1,7,10};
	ElementType X[POINT_NUM+1]={0};
	SearchTree D=NULL;
	int i;
	
	for(i=0; i<15; i++){
		D=Insert(Distance[i], D);	
	}
 
	if(Turnpike(X,D,POINT_NUM)){
		for(i=1; i<=POINT_NUM; i++)
			printf("X[%d]: %f\n",i,X[i]);
		return 0;
	}else
		return 1;
}
