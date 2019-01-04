#include <iostream>
#include <vector>
#include <list>
#include <iomanip>

using namespace std;



struct Edge{
	int from, to, weight;
	Edge(){}
	Edge(int f, int t, int w):from(f),to(t),weight(w){}
};



class GraphSP{
	private:
		int vertex;
		vector<list<Edge> > AdjList;
	public:
		GraphSP(){}
		GraphSP(int v):vertex(v){
			AdjList.resize(vertex);
		}
		void AddEdgeList(int, int, int);
		void BellmanFordSP(int);
		friend int ExtractMin(int*,bool* , int);
		
};



void GraphSP::BellmanFordSP(int start = 0){
	int Memory[vertex][vertex];
	Memory[0][start]=0;
	for( int i=0; i<vertex;i++){
		if (i!=start)	Memory[0][i]=10000; //regard as infinited
	}
	
	// OPT ( i, v) = min{ OPT (i -1 ,w), min {(i-1, x) + Cwx} }
	
	for (int i=1;i<vertex;i++){ // control distance 
		for (int j=0; j<vertex;j++) //control vertex shmoo
			Memory[i][j] = Memory[i-1][j];
			
		for (int j=0; j<vertex;j++ ){ //control vertex shmoo
			for (list<Edge>:: iterator itr = AdjList[j].begin(); itr != AdjList[j].end(); itr++){
				if ((Memory[i][(*itr).to])>((*itr).weight+Memory[i-1][j]))
					Memory[i][(*itr).to]=((*itr).weight+Memory[i-1][j]) ;		 	
			}
		}
	}
	
	// printSP
	cout << "begin from: "<< start <<" to each node which weight: "<<endl;
	for (int i=0 ; i < vertex; i++){
		for (int j=0; j< vertex; j++){
			cout << setw(10)<< Memory[j][i];
		}
		cout<< endl;
	}
}

void GraphSP::AddEdgeList(int from, int end, int weight){
	Edge NewEdge(from,end,weight);
	AdjList[from].push_back(NewEdge);
}




int main(){
	/*
	GraphSP G(7);
    G.AddEdgeList(0, 1, 5);G.AddEdgeList(0, 5, 3);
    G.AddEdgeList(1, 0, 5);G.AddEdgeList(1, 2, 10);G.AddEdgeList(1, 4, 1);G.AddEdgeList(1, 6, 4);
    G.AddEdgeList(2, 1, 10);G.AddEdgeList(2, 3, 5);G.AddEdgeList(2, 6, 8);
    G.AddEdgeList(3, 2, 5);G.AddEdgeList(3, 4, 7);G.AddEdgeList(3, 6, 9);
    G.AddEdgeList(4, 1, 1);G.AddEdgeList(4, 3, 7);G.AddEdgeList(4, 5, 6);G.AddEdgeList(4, 6, 2);
    G.AddEdgeList(5, 0, 3);G.AddEdgeList(5, 4, 6);
    G.AddEdgeList(6, 1, 4);G.AddEdgeList(6, 2, 8);G.AddEdgeList(6, 3, 9);G.AddEdgeList(6, 4, 2);
	*/
	
	/*
    GraphSP G(6);
    G.AddEdgeList(0, 1, 8);G.AddEdgeList(0, 5, 1);
    G.AddEdgeList(1, 0, 3);G.AddEdgeList(1, 2, 1);
    G.AddEdgeList(2, 0, 5);G.AddEdgeList(2, 3, 2);G.AddEdgeList(2, 4, 2);
    G.AddEdgeList(3, 1, 4);G.AddEdgeList(3, 2, 6);G.AddEdgeList(3, 4, 7);G.AddEdgeList(3, 5, 3);
    G.AddEdgeList(5, 3, 2);G.AddEdgeList(5, 4, 8);
	*/
	
	// try negetive weight
    GraphSP G(6);
    G.AddEdgeList(0, 1, -3);G.AddEdgeList(0, 3, 3);G.AddEdgeList(0, 4, 4);G.AddEdgeList(0, 5, 2);
    G.AddEdgeList(1, 4, 6);
    G.AddEdgeList(2, 1, -4);G.AddEdgeList(2, 3, 8);
    G.AddEdgeList(3, 5, -3);
    G.AddEdgeList(4, 2, -1);
    G.AddEdgeList(5, 2, -2);


    std::cout << "SP found by Dijkstra :\n";
    G.BellmanFordSP();

	
	return 0;
}

