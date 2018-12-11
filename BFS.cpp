#include <iostream>
#include <queue>
#include <list>
#include <vector>
using namespace std;

class Graph{
	private:
		int key;
		vector <list<int> > AdjList;
		int *color, 
			*predecessor,
			*distance;
	public:
		Graph():key(0){}
		Graph(int n):key(n){
			AdjList.resize(key);
		}
		void AddEdgeList (int, int);
		void BFS(int);
};

void Graph::AddEdgeList(int from, int to){
	AdjList[from].push_back(to);
}

void Graph::BFS(int start){
	
}

int main(){
	
	
	return 0;
}
