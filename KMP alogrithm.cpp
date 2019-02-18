#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

int main(){
	string str="aabaabaaa";
	vector<int> p(str.size(),0);
	
	for(int i=1 , k = p[0]= 0;i<str.size();i++){
		while(k>0&&str[k]!=str[i]){
			k=p[k-1];
		}
		if(str[k]==str[i]){
			k++;
			p[i]=k;
			
		}
	}
	
	for(int i=0;i<p.size();i++) cout<<p[i]<<",";
	return 0;
}
