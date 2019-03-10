#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

int* getrand1();
int* getrand2();
int* getrand3();
void printrand(int*);


int comp(const void* a,const void* b){
	int c= *((int*)a);
	int d= *((int*)b);
	return c>d;
}


int main(){
    int a[]={8,1,7,3,5,4,2,6};
	qsort(a,sizeof(a)/sizeof(*a),sizeof(*a),comp);
	for(int i=0;i<8;i++){
		printf("%d ",a[i]);
	}
	
	
	
	
	int b=0;
	srand(time(NULL));
	b=rand()%10;
	//printf("%d\n",a);
	int arr1[500];
	int *arr = arr1;
	arr=getrand1();
	//printrand(arr);
	
	return 0;
}

int* getrand1(){
	
	int* result = (int*)malloc(500*sizeof(int));
	
	for(int i=0;i<500;i++){
		result[i]=i+1;
		//printf("%d ",result[i]);
	}
	for(int i=0,g;i<500;i++){
		g=rand()%500;
		int temp=result[i];
		result[i]=result[g];
		result[g]=temp;
	}
	return result;
}

void printrand(int* arr){
	for(int i=0;i<500;i++){
		printf("%d ",arr[i]);
	}
}
