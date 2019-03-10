#include <stdio.h>
using namespace std;

int binarysearch(int*, int, int);

int main(){
	
	int arr[10]={0,1,2,3,4,5,6,7,8,9};
	printf("%d\n",binarysearch(arr,10,6));
	
	return 0;
}


int binarysearch(int* arr, int size, int target){
	int min=0, max=size-1, mid;
	while(min<=max){
		mid = (min+max)/2;
		if(arr[mid]==target) return mid;
		else if (arr[mid]<target) min=mid+1;
		else max=mid-1;
	}
	return -1;
}
