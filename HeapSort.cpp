#include <iostream>
using namespace std;

// this heap sort time complexity is O(NlogN) space complexity is O(N)


void swap(int&, int&);
void HeapSort(int*, int);
void MaxHeapify(int*, int, int);
void PrintArray(int*, int);

int main(){
	
	int N=10;
	int A[N] = {7,5,3,6,1,8,9,4,2,0};
	PrintArray(A,N);
	HeapSort(A,N);
	PrintArray(A,N);
		
	return 0;
}


void swap(int& a, int& b){
	int c  = b;
	b = a;
	a = c;
}

void HeapSort(int* arr, int N){
	int total=N+1;
	int *temp = new int[total];
	for(int i=0; i<N; i++){
		temp[i+1]=arr[i];
	}

	//build max heap
	for (int i=(total-1)/2;i>=1;i--){
		MaxHeapify(temp,i,total-1);
	}

	// do heapsort
	for(int i=total-1; i>1;){
		swap(temp[i],temp[1]);
		i--;
		MaxHeapify(temp,1,i);
	}
	
	// copy back to original array
	for (int i=0; i<N; i++){
		arr[i]=temp[i+1];
	}
	
	delete [] temp; // avoid memory leak
}

void MaxHeapify(int* arr, int start, int total){
	int i = start,
		j = 2*start;
		
	while(j<=total){
		if (j+1<=total){ // make sure it would not check overflow
			if (arr[j+1]>arr[j]){
				j++;
			}
		}
		if (arr[i]<arr[j]){
			swap(arr[i],arr[j]);
		}
		i = j;
		j *=2;
	}
}

void PrintArray(int* arr, int N){
	cout<< "Array content: ";
	for (int i=0; i<N; i++){
		cout<< arr[i]<<" ";
	}
	cout <<endl;
}


