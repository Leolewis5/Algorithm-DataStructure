#include <iostream>
#include <queue>
#include <list>
#include <stack>
using namespace std;

struct Edge{
	int begin;
	int end;
	Edge():begin(0),end(0){}
	Edge(int b,int e):begin(b),end(e){}
};

class Graph{
	private:
		int key;
		
		list<Edge> DFTEdge; 
		vector<list<int> > AdjList;
		int * color,
			* predecessor,
			* distance;
	public:
		Graph(){}
		Graph(int m):key(m){
			AdjList.resize(key);
		}
		
		void AddEdgeList(int, int);
		void DFS_while(int);
		void DFS_recursive(int);
		void TravelDFS(int);
		void ShowDFT();
};

void Graph::AddEdgeList(int from,int to){
	AdjList[from].push_back(to);
}

void Graph::DFS_while(int start){
	//important!! need to assign pointer array size
	color = new int[key];
	predecessor = new int[key];
	distance = new int[key];
	
	//initial state
	for (int i =0; i<key;i++){
		color[i]= 0;
		predecessor[i]=-1;
		distance[i] = key+1;
	}

	stack<int> s;
	int i = start;
	
	// need to consider there have several conenctive component
	for (int j = 0; j<key; j++){
		if(color[i]==0){
			s.push(i);
			distance[i]=0;
			color[i]=1;
			while(!s.empty()){
				for (list<int>::iterator itr = AdjList[i].begin(); itr != AdjList[i].end(); ){
					cout <<"i: "<< i << "itr" << *itr <<endl ;
					
					if (color[*itr]==0){
						
						DFTEdge.push_back(Edge(i, *itr)) ;// store the edge of DFT
						 						
						s.push(*itr);
						color[*itr]=1;
						predecessor[*itr]=i;
						distance[*itr]=1+distance[i];
						i = s.top();
						itr = AdjList[i].begin();
					}
					else{
						itr++;
					}
				}
				s.pop();
			}
		}
		i = j;
	}
}

void Graph::DFS_recursive(int start){
	//important!! need to assign pointer array size
	color = new int[key];
	predecessor = new int[key];
	distance = new int[key];
	
	//initial state
	for (int i =0; i<key;i++){
		color[i]= 0;
		predecessor[i]=-1;
		distance[i] = key+1;
	}
	
	int i = start;
	for (int j = 0; j < key; j++){
		if (color[i]==0){
			color[i]=1;
			TravelDFS(i);
		}
		i = j;
	}
}

void Graph::TravelDFS(int i){
	for (list<int>::iterator itr = AdjList[i].begin(); itr != AdjList[i].end(); itr++){
		if (color[*itr]==0){
			DFTEdge.push_back(Edge(i, *itr)) ; // store the edge of DFT
			color[*itr]=1;
			distance[*itr]=distance[i]+1;
			predecessor[*itr]=i;
			TravelDFS(*itr);
		}
	}
}

void Graph::ShowDFT(){
	cout<< "DFT edge is: ";
	for (list<Edge>::iterator itr = DFTEdge.begin(); itr !=DFTEdge.end(); itr++){
		cout<< "("<< itr->begin <<", "<< itr->end<<") ";
	}
	cout<< endl;
}

int main(){
	 Graph g1(9);    
    // contribute one adjacenct list
    g1.AddEdgeList(0, 1);g1.AddEdgeList(0, 2);g1.AddEdgeList(0, 3);    
    g1.AddEdgeList(1, 0);g1.AddEdgeList(1, 4);
    g1.AddEdgeList(2, 0);g1.AddEdgeList(2, 4);g1.AddEdgeList(2, 5);g1.AddEdgeList(2, 6);g1.AddEdgeList(2, 7);
    g1.AddEdgeList(3, 0);g1.AddEdgeList(3, 7);
    g1.AddEdgeList(4, 1);g1.AddEdgeList(4, 2);g1.AddEdgeList(4, 5);
    g1.AddEdgeList(5, 2);g1.AddEdgeList(5, 4);g1.AddEdgeList(5, 8);
    g1.AddEdgeList(6, 2);g1.AddEdgeList(6, 7);g1.AddEdgeList(6, 8);
    g1.AddEdgeList(7, 2);g1.AddEdgeList(7, 3);g1.AddEdgeList(7, 6);
    g1.AddEdgeList(8, 5);g1.AddEdgeList(8, 6);
    
	//g1.showVE();

   // g1.DFS_while(0); 
    g1.DFS_recursive(0);
    g1.ShowDFT();
return 0;
} 
