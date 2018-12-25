#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <iomanip>
using namespace std;

void swap(int&,int&);
void InsertionSort(int* , int , int* ); //this is sort by large to small, explain in PrintSSC

class Graph{
	private:
		int key,
			time;
		vector<list<int> > AdjList;
		int * color,
			* predecessor,
			* distance,
			* start,
			* end;
	public:
		Graph(){}
		Graph(int k):key(k),time(0){
			AdjList.resize(key);
		}
		void VariableInitial(); //initial index
		// use stack to achieve DFS
		void DFSstack(int);
		// use recursive to achieve DFS
		void DFSrecursive(int);
		void DFSVisit(int,int&);
		
		// add edge list and transpose edge list
		void AddEdgeList(int, int);
		Graph Transpose();
		
		//print strong connective component, which need to use 
		// 1. a transpose graph to original one ( edge reverse )
		// 2. start first DFS to origin graph to get end time
		// 3. issue second one DFS'(transpose one) by the sequence of first DFS end time
		// this method is that if one graph which connective component end time is this relation : C1 > C2 > C3
		// that the transpose one connective component would have this relation : C1 < C2 < C3
		// please be noticed that DFS and DFS' would have same SCC.
		void PrintSCC();
		
		
		// this is use to check connective component
		void Collapsed(int); //need start point to collaped tree.
		
		// check 1. distance 2. predecessor 3. start time & end time 
		void Print();
};

void Graph::AddEdgeList(int from, int to){
	AdjList[from].push_back(to);
}

Graph Graph::Transpose(){
	Graph gT(key);
	for (int i=0; i<key;i++ ){
		for (list<int>::iterator itr = AdjList[i].begin(); itr!=AdjList[i].end(); itr++){
			gT.AddEdgeList(*itr,i);
		}
	}
	return gT;
}

void Graph::VariableInitial(){
	color = new int[key];
	predecessor = new int[key];
	distance = new int[key];
	start = new int[key];
	end = new int[key];
	
	//initial index of DFS
	for (int i=0; i<key; i++){
		color[i]=0;
		predecessor[i]=-1;
		distance[i]=key+1;
		start[i]=0;
		end[i]=0;
	} 
}

void Graph::Collapsed(int current){
	int root = current;
	while (predecessor[root]!=-1){
		root=predecessor[root];
	}
	
	while(current!=root){
		int parent = predecessor[current];
		predecessor[current]=root;
		current = parent;
	}
}

void Graph::DFSstack(int begin = 0){ // defualt start at 0

	VariableInitial();
	
	int i = begin;
	stack<int> s;
	
	for (int j=0; j<key; j++){
		if (color[i]==0){
			time++;
			color[i]=1;
			start[i]=time;
			distance[i]=0;
			s.push(i);
			while(!s.empty()){
				int z=s.top();
				for(list<int>::iterator itr = AdjList[z].begin(); itr!=AdjList[z].end();){
					if (color[*itr]==0){
						time++;
						s.push(*itr);
						color[*itr]=1;
						distance[*itr]=distance[z]+1;
						predecessor[*itr]=z;
						start[*itr]=time;
						z = s.top();
						itr = AdjList[z].begin();
					}
					else{
						itr++;
					}
				}
				time++;
				s.pop();
				end[z]=time;
				color[z]=2;
			}
		}	
		i = j;
	}
}

void Graph::DFSrecursive(int begin = 0){
	VariableInitial();
	int i = begin;
	for (int j=0; j<key; j++){
		if (color[i]==0){
			distance[i]=0;
			DFSVisit(i,time);
		}
		i = j;
	}
}

void Graph::DFSVisit(int i, int& time){
	time++;
	color[i]=1;
	start[i]=time;
	for (list<int>::iterator itr=AdjList[i].begin(); itr!=AdjList[i].end();itr++){
		if (color[*itr]==0){
			predecessor[*itr]=i;
			distance[*itr]=distance[i]+1;
			DFSVisit(*itr,time);
		}
	}
	end[i]=++time;
	color[i]=2;
}

void Graph::PrintSCC(){
	DFSstack(); //first DFS to get finish time sequence
	int Record[key];  // this use to record sequence of finish time
	for (int i=0; i<key; i++){
		Record[i]=i;
	}
	
	InsertionSort(end,key,Record); // Record will record the sequence from low to high
	
	Graph gt(key);
	gt = Transpose();
	
	time=0;
	gt.VariableInitial();
	for(int i=0; i<key; i++){
		if(gt.color[Record[i]]==0){
			gt.distance[Record[i]]=0;
			gt.DFSVisit(Record[i],time);
		}
	}
	gt.Print();
	
	for (int i=0; i<key; i++){
		gt.Collapsed(i);
	}
	
	int component = 0;
	for (int i=0; i<key; i++){
		if (gt.predecessor[i]==-1){
			cout << "component"<<++component<<" : "<<endl<<i;
			for (int j=0; j<key; j++){
				if (gt.predecessor[j]==i){
					cout << setw(4) << j;
				}
			}
			cout<<endl;
		}
	}
}

void Graph::Print(){
	// print start time
	cout<< "predecessor: "<<endl;
	for (int i=0; i<key; i++){
		cout << setw(4) << i ;
	}
	cout <<endl;
	for (int i=0; i<key; i++){
		cout << setw(4) << predecessor[i];
	}
	cout<<endl;
	
	// print start time
	cout<< "start time: "<<endl;
	for (int i=0; i<key; i++){
		cout << setw(4) << i ;
	}
	cout <<endl;
	for (int i=0; i<key; i++){
		cout << setw(4) << start[i];
	}
	cout<<endl;
	
	
	// print end time
	cout<< "end time: "<<endl;
	for (int i=0; i<key; i++){
		cout << setw(4) << i ;
	}
	cout <<endl;
	for (int i=0; i<key; i++){
		cout << setw(4) << end[i];
	}
	cout<<endl;
	
	// print distance
	cout<< "distance: "<<endl;
	for (int i=0; i<key; i++){
		cout << setw(4) << i ;
	}
	cout <<endl;
	for (int i=0; i<key; i++){
		cout << setw(4) << distance[i];
	}
	cout<<endl;
}

void swap(int& a, int& b){
	int c = b;
	b = a;
	a = c;
}

void InsertionSort(int* arr, int k, int* arrT){
	for (int i=1; i<k; i++){
		int min = arr[i];
		int current = arrT[i];
		int j = i-1;
		for (; j>=0; j--){
			if (min>arr[j]){
				arr[j+1]=arr[j];
				arrT[j+1]=arrT[j];
			}
			else{
				break;
			}
		}
		arr[j+1]=min;
		arrT[j+1]=current;
	}
}



int main(){
 
    Graph g4(9);
    g4.AddEdgeList(0, 1);
    g4.AddEdgeList(1, 2);g4.AddEdgeList(1, 4);
    g4.AddEdgeList(2, 0);g4.AddEdgeList(2, 3);g4.AddEdgeList(2, 5);
    g4.AddEdgeList(3, 2);
    g4.AddEdgeList(4, 5);g4.AddEdgeList(4, 6);
    g4.AddEdgeList(5, 4);g4.AddEdgeList(5, 6);g4.AddEdgeList(5, 7);
    g4.AddEdgeList(6, 7);
    g4.AddEdgeList(7, 8);
    g4.AddEdgeList(8, 6);
    
    g4.DFSstack();    
    g4.Print();
    cout << "printSCC"<<endl;
    g4.PrintSCC();
	
	
	return 0;
}
