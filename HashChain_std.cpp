#include <iostream>
#include <vector>
#include <list>

using namespace std;


struct dic{
	string name;
	string team;
	dic():name(""),team(""){}
	dic(string KeyInName, string KeyInTeam):name(KeyInName), team(KeyInTeam){}
};



class HashChain_std{
	private:
		int size;
	
		vector<list<dic> > table;
	
		int GetKey(string );    //  enter name to get index
		int HashFunction(string ); //enter name to get index than hash slot
			
	public:
		
		HashChain_std():size(0){}
		HashChain_std(int m):size(m){
			table.resize(size);     // use resize to construct the table
		}
		void Insert(dic);  //insert element into hash
		void Delete(string); // delete element in the hash
		string Search(string); //search the team of the name
		void display();   //print the hash content
};


void HashChain_std::Insert(dic EnterDic){
	// 1. give dic a index
	// 2. push_front to the slot
	int index = HashFunction (EnterDic.name);
	table[index].push_front(EnterDic);	
}

void HashChain_std::Delete(string EnterName){
	// 1. find string index
	// 2. delete such index data
	int index = HashFunction(EnterName);
	for (list<dic>::iterator itr = table[index].begin(); itr != table[index].end(); itr++){
	
		if ((*itr).name == EnterName){
			table[index].erase(itr);	
			return;
		}
	}
}

string HashChain_std::Search(string EnterName){
	// 1. find string index
	// 2. return index team name
	int index = HashFunction(EnterName);
	for (list<dic>::iterator itr = table[index].begin(); itr != table[index].end(); itr++){
		if ((*itr).name == EnterName){
			return (*itr).team;
		}
	}
	return "no such data";
}

void HashChain_std::display(){
	for (int i = 0; i < size ; i++){
		cout << "slot: "<<i<<" has content : ";
		for (list<dic>::iterator itr = table[i].begin(); itr != table[i].end(); itr++ ){
			cout << "(" << (*itr).name << ", " << (*itr).team<<") " ;
		}
		cout << endl;
	}
	cout <<endl;
}

int HashChain_std::GetKey(string name){
	// exp: name: Henry, then key = H*9^5 + e*9^4 + n*9^3 +  r*9^2 + y*9^1
	// retun key
	
	int index = 0;
	int item = 9;
	int store = 1;
	
	for (int i = (int)name.size()-1; i>=0; i--){
		index += name[i]*store;
		store *= item;
	}
	return index;
}

int HashChain_std::HashFunction(string name){
	return GetKey(name)% this->size;
}


int main(){
	
	HashChain_std hash(5);
    hash.Insert(dic("T-Mac","Magic"));
    hash.Insert(dic("Bryant","Lakers"));
    hash.Insert(dic("Webber","Kings"));
    hash.Insert(dic("Arenas", "Wizards"));
    hash.Insert(dic("Davis","Clippers"));
    hash.Insert(dic("Kidd","Nets"));
    hash.display();

    cout << "T-Mac is in " << hash.Search("T-Mac") << ". " << endl;
    cout << "Arenas is in " << hash.Search("Arenas") << ". " << endl;

    hash.Delete("Kidd");
    hash.Delete("T-Mac");
    cout << "\nAfter deleing Kidd and T-Mac:\n";
    hash.display();

	
	
	return 0;
}
