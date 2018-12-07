#include <iostream>
#include <vector>
using namespace std;


struct Node{
	string name;
	string genre;
	Node *next;
	Node():name(""),genre(""),next(NULL){}
	Node(string name, string genre):name(name),genre(genre),next(NULL){}
	Node(Node const &data):name(data.name),genre(data.genre),next(data.next){}
};


class HashTable{
	private:
		int size;
		int count;
		
		vector<Node*> table;
		
		int GetIndex(string);
		int HashFunction(string);
	
	public:
		HashTable():size(0),count(0){}
		HashTable(int m):size(m),count(0){
			table.resize(size);
		}
		
		string Search(string);
		void Insert(string, string);
		void Insert(Node);
		void Delete(string);
		void Display();
};


string HashTable::Search(string KeyInName){
	int index = HashFunction(KeyInName);
	Node *current = table[index];
	while (current != NULL){
		if (current->name==KeyInName) return current->genre;
		current = current -> next;
	}
	
	return " no such data /n";
}

void HashTable::Insert(Node InsertNode){
	int index = HashFunction(InsertNode.name);
	Node* NewNode = new Node(InsertNode);

	if (table[index]==NULL){
		table[index] = NewNode;
	}
	else{
		Node* OldNode = table[index];   //push front
		NewNode->next = OldNode;
		table[index] = NewNode;
	}
}

void HashTable::Insert(string name, string group){
	int index = HashFunction(name);
	Node* NewNode = new Node(name, group);

	if (table[index]==NULL){
		table[index] = NewNode;
	}
	else{
		Node* OldNode = table[index];   //push front
		NewNode->next = OldNode;
		table[index] = NewNode;
	}
}

void HashTable::Delete(string KeyInName){
	int index = HashFunction(KeyInName);
	Node* current = table[index];
	Node* next = current->next;
	if (current->name == KeyInName){
		table[index]= next;
		delete current;
		return;
	}
	else{
		while(next!= NULL){
			if (next->name == KeyInName){
				current->next= next->next;
				delete next;
				return;
			}
			current = next;
			next= next->next;
		}
	}
	
	cout << " no such data can be delete"<<endl;
}

void HashTable::Display(){
	for (int i = 0; i<size; i++){
		Node* current = table[i];
		cout << "slot "<< i<< " has content: ";
		while (current!=NULL){
			cout <<"("<<current->name<<" , "<<current->genre<<") ";
			current = current->next;
		}
		cout<<endl;
	}
}

int HashTable::GetIndex(string KeyInName){
	int exp = 9;
	int index = 0;
	int item = 1;
	for (int i = (int)KeyInName.size()-1; i>=0; i--){
		index += KeyInName[i]*item;
		item *= exp;
	}
	
	return index;	
}

int HashTable::HashFunction(string KeyInName){
	return GetIndex(KeyInName)%size;
}

int main(){
	
	HashTable hash(5);
    hash.Insert("T-Mac","Magic");
    hash.Insert("Bryant","Lakers");
    hash.Insert("Webber","Kings");
    hash.Insert("Arenas", "Wizards");
    hash.Insert("Davis","Clippers");
    hash.Insert("Kidd","Nets");
    hash.Display();

    cout << "T-Mac is in " << hash.Search("T-Mac") << ". " << endl;
    cout << "Arenas is in " << hash.Search("Arenas") << ". " << endl;

    hash.Delete("Kidd");
    hash.Delete("T-Mac");
    cout << "\nAfter deleing Kidd and T-Mac:\n";
    hash.Display();
	return 0;
}

