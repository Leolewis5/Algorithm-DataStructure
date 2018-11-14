#include <iostream>
using namespace std;


void bubblesort(int *, int );
void swap (int &, int &);
void print(int *, int);
void insertionsort (int *, int );
void quicksort (int *, int, int );
int partition (int *, int, int);
void selectionsort(int *, int);


int main(){
	int a[5]= {1,5,3,4,6};
	print(a,5);
	bubblesort(a,5);
	print(a,5);

return 0;
	
}



void bubblesort(int *ptr , int size){
	for (int j= size; j>=1; j--){
		for (int i =1; i < j; i ++){
			if (ptr[i-1]>ptr[i]) swap (ptr[i-1],ptr[i]);
			}
	}
}


void swap (int & a, int & b){
	int c = a;
	a = b;
	b = c;
}


void print(int *ptr, int size){
	cout <<"array conetent is: ";
	for (int i =0; i<size;i++){
		cout << ptr[i]<<" ";
	}
	cout << endl;
}



void insertionsort (int *ptr, int size){
	for (int i=1; i<size ; i++){
		int key = ptr[i];
		int j= 0;
		for (j=i-1; j>=0; j--){
			if (ptr[j]>key) ptr[j+1]=ptr[j];
			if (ptr[j]<=key)break;
		}
//		cout <<"currentj: "<< j <<endl;
		ptr[j+1]=key;
	}
}


void quicksort (int *array, int front, int end ){
	
	if (front<end) {
	int pivot= partition (array,  front,  end);
	//if (front==0) cout <<"pivot is:" <<pivot <<endl;
 	 quicksort (array, 0,  pivot-1  );
 	 quicksort (array, pivot+1, end );
}
}

int partition (int *array, int front, int end){
	int i = front -1;
	int pivot = array[end];
	for(int j=front ; j<=end-1; j++) {
		if (pivot>array[j]) {
		swap(array[j],array[1+i]);
	    i++;		
		}
	}
	swap(array[end],array[++i]);
	return i;
}


void selectionsort(int * ptr, int size){
	for (int i = 0; i<size ; i++){
		int smallest = i;
		for (int j = i+1 ; j <size; j++)
			if (ptr[j]<ptr[smallest]) 	
			smallest = j;
			swap(ptr[i],ptr[smallest]);
	}	
}
