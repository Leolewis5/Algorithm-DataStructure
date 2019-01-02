#include <iostream>
#include <vector>
#include <list>
#include <iomanip>

using namespace std;

int FindandCollapsed(int* , int );
void Union(int* , int , int );


struct Edge{
	int from, to, weight;
	Edge(){}
	Edge(int f, int t, int w):from(f),to(t),weight(w){}
};



class GraphMST{
	private:
		int vertex,EdgeCount;
		vector<list<Edge> > AdjList;
	public:
		GraphMST(){}
		GraphMST(int v):vertex(v),EdgeCount(0){
			AdjList.resize(vertex);
		}
		void AddEdgeList(int, int, int);
		void KruskalMST();
		//void sort (list<Edge>);
		
		friend void Union(int*, int, int);
		friend int FindandCollapsed(int*,int);
		
};

bool comp(const Edge &a, const Edge &b){  // if put this into class, it will fail, need to study
	return a.weight < b.weight;
}

void GraphMST::KruskalMST(){
	// allocated subset and initialize with -1
	int subset[vertex] = {};
	for (int i=0; i<vertex ;i++){
		subset[i]=-1;
	}
	
	// store MSTEdge
	list<Edge> MSTEdge;
	
	list<Edge> SortList;
	for (int i=0;i<vertex;i++){
		for(list<Edge>::iterator itr = AdjList[i].begin(); itr != AdjList[i].end();itr++){
			SortList.push_back(*itr);
		}
	}
	
	//sort(SortList, EdgeCount);
	SortList.sort(comp);
	
	int Checknode = vertex-1;
	while(Checknode != 0){
		Edge temp = SortList.front();
		SortList.pop_front();
		if (FindandCollapsed(subset,temp.from)!=FindandCollapsed(subset,temp.to)){
			Union(subset,temp.from,temp.to);
			MSTEdge.push_back(temp);
			Checknode--;
		}
	}
	
	// printMST
	cout << "from"<<setw(3)<<"to"<<setw(7)<<"weight"<<endl;
	for (list<Edge>::iterator itr = MSTEdge.begin(); itr != MSTEdge.end(); itr++){
		cout << setw(4)<<(*itr).from<<setw(3)<<(*itr).to<<setw(7)<<(*itr).weight<<endl;
	}
}
/*
void GraphMST::sort(list<Edge> ThisEdge){
	ThisEdge.sort()
}
*/


void GraphMST::AddEdgeList(int from, int end, int weight){
	Edge NewEdge(from,end,weight);
	EdgeCount++;
	AdjList[from].push_back(NewEdge);
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
	GraphMST G(7);
    G.AddEdgeList(0, 1, 5);G.AddEdgeList(0, 5, 3);
    G.AddEdgeList(1, 0, 5);G.AddEdgeList(1, 2, 10);G.AddEdgeList(1, 4, 1);G.AddEdgeList(1, 6, 4);
    G.AddEdgeList(2, 1, 10);G.AddEdgeList(2, 3, 5);G.AddEdgeList(2, 6, 8);
    G.AddEdgeList(3, 2, 5);G.AddEdgeList(3, 4, 7);G.AddEdgeList(3, 6, 9);
    G.AddEdgeList(4, 1, 1);G.AddEdgeList(4, 3, 7);G.AddEdgeList(4, 5, 6);G.AddEdgeList(4, 6, 2);
    G.AddEdgeList(5, 0, 3);G.AddEdgeList(5, 4, 6);
    G.AddEdgeList(6, 1, 4);G.AddEdgeList(6, 2, 8);G.AddEdgeList(6, 3, 9);G.AddEdgeList(6, 4, 2);

    std::cout << "MST found by Kruskal:\n";
    G.KruskalMST();

	
	return 0;
}

