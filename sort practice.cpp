#include <iostream>
using namespace std;

void print (int* , int );
void swap (int &, int &);
void bubblesort(int * , int );
void selectionsort(int* , int );
void heapsort(int* , int );
int deletefront(int* , int );  // use to delete the min value on heap, the front value
int* buildheap(int* , int );  // use to construct a minheap, pass origin array and which total element:N, then return a min heap.

void merge(int* arr, int front, int mid, int end){
	int* temp = new int[end+1];  // use to store merge result
	int ai = front, bi=mid+1;
	int begint=0;
	while (ai!=mid||bi!=end ){
		if (arr[ai]<arr[bi]){
			temp[begint]=arr[ai];
			begint++;
			ai++; 
		}
		else{
			temp[begint]=arr[bi];
			begint++;
			bi++ ;
		}
	}
	if (ai==mid&&bi==end&&bi-ai==1){
		if (arr[ai]>arr[bi]){
			swap (arr[ai],arr[bi]);
			return;
		}
	}
	
	if (ai==mid&&bi==end){
		int j=0;
		for (int i=front; i<=end;i++,j++){
			arr[i]=temp[j];
		}
		delete temp;
		return;
	}
	if(ai==mid&&bi!=end){
		for (int i = bi; i<=end;i++){
			begint++;
			temp[begint]=arr[i];
		}
		for (int i=front, k=0; i<=end;i++,k++){
			arr[i]=temp[k];
		}
		delete temp;
		return;
	}
	
	if(ai!=mid&&bi==end){
		for (int i = ai; i<=mid;i++){
			begint++;
			temp[begint]=arr[i];
		}
		for (int i=front, k=0; i<=end;i++,k++){
			arr[i]=temp[k];
		}
		delete temp;
		return;
	}
}

void mergesort(int * arr, int front, int end){
	cout<<"c";
	if (front<end){
		int mid = (front + end)/2;
		mergesort(arr, front, mid);
		mergesort(arr, mid+1, end);
		merge(arr, front, mid, end);
		cout<<"d";
	}
}


int main(){
	
	int ptr[8]={8,5,3,4,2,6,7,0};
	int N =8;
	cout <<"origin ptr: ";
	print(ptr,N);
	cout<< endl << "after sort: ";
	
	mergesort(ptr,0,N);
	//heapsort(ptr,N);
	//insertionsort(ptr,N);
	//selectionsort(ptr,N);
	//bubblesort(ptr,N);
	print(ptr,N);
		
}


void swap (int &a, int &b){
	int c =b;
	b=a;
	a=c;
}

void bubblesort(int * arr, int N){
	for ( int i=0 ; i < N; i ++){
		for (int j=i+1;j<N;j++)
			if (arr[j]<arr[i])
			swap(arr[i],arr[j]);
	} 
}

void insertionsort(int* arr, int N){
	for (int i =1; i<N;i++){
		int min= arr[i];
		int j=i-1;
		for (;j>=0;j--){
			if (min<arr[j]){
				arr[j+1]=arr[j];
			}
			else{
				break;
			}
		}
		arr[j+1]=min;
	}
}

void selectionsort(int* arr, int N){
	for (int i = 0; i < N ; i++ ){
		int min = i;
		for (int j = i+1; j<N;j++){
			if (arr[j]<arr[min]){
				min=j; 
			}
		}
		swap(arr[i],arr[min]);
	} 
}



int deletefront(int* arr, int N){  // sent in array which want to delete, and total node number
	int popitem = arr[1];  // use to pop
	int shiftone = arr[N]; // use to sort
	N--;
	int i =1, j=2; 
	while (j<=N){ 		//this place seems to have a bug that j=N+1 
		if (arr[j]>arr[j+1])j++;
		if (arr[j]<shiftone){ 	// but this condition would avoid bug happend
			arr[i]=arr[j];
			i=j;
			j=j*2;
		}
		else{
			break;
		}
	}
	arr[i]=shiftone;
	return popitem;	
} 

int* buildheap(int* arr, int N){
	int* heap= new int[N+1]; // minheap strat at arr["1"] not arr["0"]
	int total=1;
	for (int i=0; i<N;i++){
		int current = total;
		heap[current] = arr[i];
		while (current>1){				// bottom up method
			if (heap[current]<heap[current/2]){
				swap(heap[current],heap[current/2]);
				current=current/2;
			}
			else{
				break;
			}
		}
		total++; 
	}

	return heap;
}

void heapsort(int* arr, int N){
	int *heapsortitem;
	heapsortitem= buildheap(arr,N);
	for (int i =0; i <N;i++){
		arr[i]=deletefront(heapsortitem,N-i); //arr = arr[0]~arr[N-1] ; heapsortitem is arr[1] ~ arr[N]
	}	
	delete heapsortitem; // return dynamic allocate minheap array, avoid memory leak
}

void print (int* arr, int N){
	for(int i =0; i < N; i ++){
		cout<< arr[i]<<" ";
	}
	cout << endl;
}


