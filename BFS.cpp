#include <iostream>
#include <queue>
#include <list>
#include <vector>
using namespace std;

struct Edge{
	int from;
	int to;
	Edge():from(0),to(0){}
	Edge(int f, int t):from(f),to(t){}
};

class Graph{
	private:
		int key,
			EdgeCount;
			
		vector <list<int> > AdjList;
		list <Edge> E;
		
		int *color, 
			*predecessor,
			*distance;
	public:
		Graph():key(0),EdgeCount(0){}
		Graph(int n):key(n),EdgeCount(0){
			AdjList.resize(key);
		}
		void AddEdgeList (int, int);
		void BFS(int);
		void showVE();
		void ShowBFTEdge();
		void FCCBFS();  // find connect component of BFS
		void Collapsed(int); // use to FFCBFS
};

void Graph::FCCBFS(){
	BFS(0);
	for(int i=0; i<key; i++){
		Collapsed(i);
	}
	int component=0;
	for(int i=0; i<key; i++){
		if (predecessor[i]==-1){
			component++;
			cout << "component"<<component<<" :";
			for (int j=0;j<key;j++){
				if (predecessor[j]==i){
					cout <<" "<<j;
				}
			}
			cout<< endl;
		}
	}
}

void Graph::Collapsed(int current){
	int root= current;
	while(predecessor[root]!=-1){
		root=predecessor[root];
	}
	while (current!=root){
		int parent = predecessor[current];
		predecessor[current]=root;
		current = parent;
	}
}

void Graph::ShowBFTEdge(){
	cout <<"BST edge is (from, to): ";
	for (list<Edge>::iterator itr= E.begin(); itr!= E.end(); itr++){
		cout<< "(" <<(*itr).from<<", "<<(*itr).to<<"), ";
	}
	cout <<endl;
}

void Graph::showVE(){
	for (int i =0;i<key;i++){
		cout<< "key is: "<< i << " ,and it conect to: ";
		for (list<int>::iterator itr=AdjList[i].begin(); itr!=AdjList[i].end() ; itr++){
			cout<< *itr<< ", ";
		}
		cout <<endl;
	}
}
void Graph::AddEdgeList(int from, int to){
	AdjList[from].push_back(to);
	EdgeCount++;
}

void Graph::BFS(int start){
	color = new int[key];
	predecessor = new int[key];
	distance = new int[key];
	
	for (int i = 0; i < key ; i++){
		color[i] = 0;				//set all color to 1.white (2. gray 3. black)
		predecessor[i] = -1;		//set all perdecessor to -1 (not exist)
		distance[i] = key+1;		//set all distance to infinite (longest distance +1)
	}
	
	queue<int> q;
	int i = start;
	
	//  need to consider a graph have plenty of conective component
	
	for (int z = 0; z <key; z++){
		if(color[i]==0){
			q.push(i); 
			color[i] = 1;
			distance[i] = 0;
			
			while(!q.empty()){
				int j = q.front();
				color[j] = 1;
				for (list<int>::iterator itr = AdjList[j].begin(); itr!= AdjList[j].end(); itr ++){
				
					if (color[*itr]==0){
						
						color[*itr]=1;
						predecessor[*itr]=j;
						distance[*itr] = distance[j] +1 ;
						q.push(*itr);
						E.push_back(Edge(j,*itr));
					}
				}
				q.pop();
			}
		}
		i = z;
	}
}

int main(){
	 Graph g1(14);    
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
    
    g1.AddEdgeList(9, 10);g1.AddEdgeList(9, 12);
    g1.AddEdgeList(10, 9);g1.AddEdgeList(10, 11);
    g1.AddEdgeList(11, 10);g1.AddEdgeList(11, 12);
    g1.AddEdgeList(12, 9);g1.AddEdgeList(12, 11);g1.AddEdgeList(12, 13);
    g1.AddEdgeList(13, 12);
    
	//g1.showVE();
	
    g1.BFS(0);    
    g1.ShowBFTEdge();
    g1.FCCBFS();
	
	return 0;
}
