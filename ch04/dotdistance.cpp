#include <stdio.h>
#include <math.h> 

//Point ��һ����Ľṹ�壬x��y��ʾ�������� 
typedef struct Point{
	double x;	
	double y;
}Point;
//���������ĺ��� 
float distance(Point a,Point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

//���� 
int partition(Point a[],int begin,int end){
	Point key = a[end];
	int i = begin-1;
	for(int j=begin;j<end;j++){
		if(a[j].x<=key.x){
			i++;
			Point temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	i++;
	a[end] = a[i];
	a[i] = key;
	return i;
}
void quiksort(Point a[],int begin,int end){
	if(begin<end){
		int middle = partition(a,begin,end);
		quiksort(a,begin,middle-1);
		quiksort(a,middle+1,end);
	}
}
//���η������� 
float closest (Point* points,int n,Point &a, Point &b){
	//�ݹ麯������,������ֱ�ӷ��ؾ��룬һ���㷵��һ�����ֵ 
	if(n==2){
		a = points[0];
		b = points[1];
		return distance(a,b);
	} 
	else if(n<2){
		return 99999;
	}
	//���� 
	else{
		int n1 = n/2;
		int n2 = n-n1;
		float d1,d2,dis,mid;
		Point points1 [n1];
		Point points2 [n2];
		Point a1,a2,b1,b2;
		//��x�����ŵ�� 
		quiksort(points,0,n-1);
		mid = points[n1].x;
		for(int i=0;i<n1;i++){
			points1[i] = points[i];
		}
		for(int i=0;i<n2;i++){
			points2[i] = points[i+n1];
		}
		//������������ 
		d1 = closest(points1,n1,a1,b1);
		d2 = closest(points2,n2,a2,b2);
		if(d1<=d2){
			a = a1;
			b = b1;
			dis = distance(a,b);
		}
		else{
			a = a2;
			b = b2;
			dis = distance(a,b);
		}
		//�м�����
		Point points3[n];
		int k = -1;
		for(int i=0;i<n;i++){
			if(abs(points[i].x-mid)<=dis){
				points3[++k] = points[i];
			}
		}
		for(int i=0;i<n;i++){
			for(int j=i+1;j<i+7&&j<k;j++){
				if(distance(points3[i],points3[j])<dis){
					a = points3[i];
					b = points3[j];
					dis = distance(a,b);
				}
			}
		} 
		return dis;
		
	}
}
int main(void){
	Point points[7] = {{1.0,2.0},{1.1,6.2},{5.0,7.0},{15.0,12.5},{2.6,2.5},{5.9,4.6},{9.1,15.8}};
	for(int i=0;i<7;i++){
		printf("(%f,%f)\n",points[i].x,points[i].y);
	}

	Point a,b;
	float dis = closest(points,7,a,b);
	printf("����%f����a��%f��%f������b��%f��%f��",dis,a.x,a.y,b.x,b.y);
}

