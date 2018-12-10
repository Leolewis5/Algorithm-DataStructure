#include <iostream>
using namespace std;

struct dict{
	int key;
	string value;
	dict():key(0),value(""){}
	dict(int k,string s):key(k),value(s){}
};

class HashOpenAddress{
	private:
		int size;
		dict* table;
		int QuadraticProbing(int ,int);
	
	public:
		HashOpenAddress(){}
		HashOpenAddress(int m):size(m){
			table = new dict[size];
		}
		
		void Insert(int,string);
		void Delete(int);
		void Search(int);	
		void Display();
};


int HashOpenAddress::QuadraticProbing(int key, int i){
	return ((int)((key%size) +0.5*i+0.5*i*i))%size;
}

void HashOpenAddress::Insert(int k, string s){
	dict a= dict(k,s);
	int i = 0;
	while (i!=size){
		int index = QuadraticProbing(k, i);
		if (table[index].value == ""){
			table[index]=a;
			return;
		}
		i++;
	}
	cout <<"hash table overflow"<<endl;
}

void HashOpenAddress::Delete(int k){
	int i = 0;
	while (i!=size){
		int index = QuadraticProbing(k, i);
		if (table[index].key==k){
			table[index].key=0;
			table[index].value="";
			return;
		}
		i++;
	}
	cout << "no: "<<k<< " such item can be deleted"<< endl;
}

void HashOpenAddress::Search(int k){
	cout<< "search key: "<<k;
	int i =0;
	while (i!=size){
		int index = QuadraticProbing(k, i);
		if (table[index].key==k){
			cout<< "item is: "<< table[index].value<<endl;
			return;
		}
		i++;
	}
	cout << "can not found: "<<k<< " such item"<< endl;
}

void HashOpenAddress::Display(){
	for (int i =0;  i<size; i++){
		cout<< "slot: "<<i<< "( "<<table[i].key<<", "<<table[i].value<<" )"<<endl;
	}
	cout <<endl;
}


int main(){
	HashOpenAddress hash(8);          // probing sequence:
    hash.Insert(33, "blue");          // 1,2,4,7,3,0,6,5 -> 1
    hash.Insert(10, "yellow");        // 2,3,5,0,4,1,7,6 -> 2
    hash.Insert(77, "red");           // 5,6,0,3,7,4,2,1 -> 5
    hash.Insert(2, "white");          // 2,3,5,0,4,1,7,6 -> 3
    hash.Display();
    hash.Insert(8, "black");          // 0,1,3,6,2,7,5,4 -> 0
    hash.Insert(47, "gray");          // 7,0,2,5,1,6,4,3 -> 7
    hash.Insert(90, "purple");        // 2,3,5,0,4,1,7,6 -> 4
    hash.Insert(1, "deep purple");    // 4,5,7,2,6,3,1,0 -> 6
    hash.Display();
    hash.Insert(15, "green");         // hash table overflow
	
	hash.Delete(90);
    cout << "after deleting (90,purple):\n";
    hash.Search(90);
    cout<<endl;
    
    hash.Search(8);

    hash.Insert(12, "orange");        // 4,5,7,2,6,3,1,0 -> 4
    hash.Display();

	
	return 0;
}
