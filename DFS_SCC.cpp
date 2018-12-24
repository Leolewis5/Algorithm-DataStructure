#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <iomanip>
using namespace std;

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
		void DFS(int);
		void AddEdgeList(int, int);
		void Print();
		
};



void Graph::DFS(int begin = 0){ // defualt start at 0
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
	
	int i = begin;
	stack<int> s;
	
	for (int j=0; j<key; j++){
		if (color[i]==0){
			color[i]=1;
			start[i]=time;
			s.push(i);
			while(!s.empty()){
				int z=s.top();
				for(list<int>::iterator itr = AdjList[z].begin(); itr!=AdjList[z].end();){
					if (color[*itr]==0){
						time++;
						s.push(*itr);
						color[*itr]=1;
						distance[*itr]=z+1;
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

void Graph::AddEdgeList(int from, int to){
	AdjList[from].push_back(to);
}

int main(){
	
	Graph g2(8);
	g2.AddEdgeList(0, 1);g2.AddEdgeList(0, 2); 
    g2.AddEdgeList(1, 3);
    g2.AddEdgeList(2, 1);g2.AddEdgeList(2, 5);
    g2.AddEdgeList(3, 4);g2.AddEdgeList(3, 5);
    // AdjList[4] is empty
    g2.AddEdgeList(5, 1);
    g2.AddEdgeList(6, 4);g2.AddEdgeList(6, 7);
    g2.AddEdgeList(7, 6);

    g2.DFS();    
    g2.Print();
	
	
	return 0;
}
