#include <iostream>
#include <iomanip>
using namespace std;


void print(int *arr, int N){
	for (int i=0;i<N;i++){
		cout << setw(3)<< i;
	}
	cout<< endl;
	for (int i=0;i<N;i++){
		cout << setw(3) << arr[i];
	}
	cout <<endl;
}


int FindandCollapsed(int* arr, int current){
	int root = current;
	while(arr[root]>-1){
		root = arr[root];
	}
	while(arr[current]>-1){
		int parent = arr[current];
		arr[current]=root;
		current = parent;
	}
	return root;
}

void Union(int* arr, int a, int b){
	//	Union a set and b set
	int aset = FindandCollapsed(arr, a);
	int bset = FindandCollapsed(arr, b);
	
	if (arr[aset]<=arr[bset]){
		arr[aset]+=arr[bset];
		arr[bset]=aset;
	}
	else{
		arr[bset]+=arr[aset];
		arr[aset]=bset;
	}
	
}


int main(){
	int size =6;
	int arr[size] = {-1, -1, -1, -1, -1, -1};
	print(arr, size);
	
	Union(arr, 1, 2);
	print(arr, size);
	
	Union(arr, 0, 2);
	print(arr, size);
	
	Union(arr, 3, 5);
	print(arr, size);
	
	Union(arr, 2, 5);
	print(arr, size);
	
	FindandCollapsed(arr, 5);
	print(arr, size);
	

	return 0;
}
