#include<stdio.h>
using namespace std;

void swap(int*,int*);
void bubblesort(int*,int);
void insertionsort(int*,int);
void selectionsort(int*,int);
void print(int*,int);

int main(){
	int size=10;
	int arr[size]={5,7,8,3,4,1,2,6,9,0};
	print(arr,size);
	//bubblesort(arr,size);
	//insertionsort(arr,size);
	selectionsort(arr,size);
	print(arr,size);
	
	return 0;
}

void swap(int* a, int* b){
	if (*a!=*b) *a^=*b^=*a^=*b;
}

void bubblesort(int* arr, int size){
	for(int i=0;i<size-1;i++)
	for(int j=0;j<size-1-i;j++)
	if(arr[j]>arr[j+1]) swap(&arr[j],&arr[j+1]);
}

void insertionsort(int* arr, int size){
	int i,j,temp;
	for(i=1;i<size;i++){
		temp=arr[i];
		for(j=i-1;j>=0&&arr[j]>temp;j--)
		arr[j+1]=arr[j];
		arr[j+1]=temp;
	}
}

void selectionsort(int* arr,int size){
	for(int i=0;i<size;i++){
		int min=i;
		for(int j=i+1;j<size;j++)
		if(arr[j]<arr[min]) min=j;
		if(min!=i) swap(&arr[min],&arr[i]);
	}
}

void print(int* arr, int size){
	for(int i=0;i<size;i++)
	printf("%d ",arr[i]);
	printf("\n");
}
