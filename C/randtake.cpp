#include <stdio.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

int* take(int*,int,int);
void print(int*,int);
void swap(int*,int*);

int main(){
	srand(time(NULL));
	int arr[500];
	for(int i=0;i<500;i++){
		arr[i]=i+1;
	}
	
	int* res = take(arr,10,500);
	print(res,10);
}

void print(int* arr,int size){
	for(int i=0;i<size;i++)
	printf("%d ",arr[i]);
}

int* take(int* arr, int num, int size){
	int *re = (int*)malloc(num*sizeof(int));
	for(int i=0;i<num;i++){
		int g=rand()%size;
		re[i]=arr[g];
		swap(&arr[g],&arr[size-1]);
		size--;
	}
	return re;
}

void swap(int* a,int *b){
	if(*a!=*b) *a^=*b^=*a^=*b;
}
