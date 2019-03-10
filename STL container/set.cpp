#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int main(){
	set<int> s;
	
	s.insert(10);
	s.insert(20);
	s.insert(30);
	s.insert(10); // same thing only count once!!
	
	set<int>::iterator itr = s.begin();
	
	while(itr!=s.end()){
		cout<<*itr<<endl;
		itr++;
	}
	
	return 0;
}
