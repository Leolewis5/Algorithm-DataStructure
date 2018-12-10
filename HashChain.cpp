#include <iostream>
#include <vector>
#include <string.h>
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
		void DoubleSize();
		void ReduceSize();
		void rehashing();
	
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


void HashTable::DoubleSize(){
//	cout <<"==============\n"<<"double size\n"<<"==============\n";
	size *=2;
	rehashing();
}

void HashTable::ReduceSize(){
///	cout <<"==============\n"<<"reduce size\n"<<"==============\n";
	size/=4;
	rehashing();
}

void HashTable::rehashing(){
	Node temp[size*5] =  {};
	int j =0;
	for (int i = 0; i<=size/2 -1; i++){     //restore all old data into and delete all the content
		Node* current = table[i];
		Node* pre = new Node;
		while (current != NULL){
			pre = current;
			temp[j].name = current->name;
			temp[j].genre = current->genre;
			current= current->next;
			delete pre;          // delete old content, prevent the memory leak
			pre = NULL;          // prevent bug issue
			j++;
		}
		table[i]=NULL;
	}
	
	//table.clear();          // or use clear to clear table content

	table.resize(size);
	count = 0;
	int z = 0;
	
	while (strcmp(temp[z].name.c_str(),"")){
		Insert(temp[z].name,temp[z].genre);
		z++;
	}
	//delete temp;	 // when I use Node* temp = new temp[size*5] and then delete it, it would happend bug, need to study
}

string HashTable::Search(string KeyInName){
	int index = HashFunction(KeyInName);
	Node *current = table[index];
	while (current != NULL){
		if (current->name==KeyInName) return current->genre;
		current = current -> next;
	}
	
	return " no such data";
}

void HashTable::Insert(Node InsertNode){
	count++;
	if (count>2*size) {
		cout <<"ready double size: "<< "count is: "<<count<< " size is: "<< size<<endl;
		DoubleSize();
	}
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
	count++;
	if (count>2*size) {
		cout <<"ready double: "<< "count is: "<<count<< " size is: "<< size<<endl;
		DoubleSize();
	}
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
	// there are four case in the delete
	// 1. slot is NULL
	// 2. data found in slot begin
	// 3. data found in other place in slot instead of first plase
	// 4. no found
	int index = HashFunction(KeyInName);
	Node* current = table[index];
	if (current == NULL) {						//case 1.
		cout << " no: "<<KeyInName<<" can be delete"<<endl; 
		return;
	}
	Node* next = current->next;
	if (current->name == KeyInName){             //case 2.
		table[index]= next;
		delete current;
		count--;
		if (count <= size/4) {
			cout <<"ready reduce size: "<< "count is: "<<count<< " size is: "<< size<<endl;
			ReduceSize();
		}
		return;
	}
	else{
		while(next!= NULL){                      // case 3.
			if (next->name == KeyInName){
				current->next= next->next;
				delete next;
				count--;
				if (count <= size/4) {
					cout <<"ready reduce size: "<< "count is: "<<count<< " size is: "<< size<<endl;
					ReduceSize();
				}
				return;
			}
			current = next;
			next= next->next;
		}
	}
	
	cout << " no: "<<KeyInName<<" can be delete"<<endl;   // case 4.
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
	int exp = 7;
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

	// checl double function
    hash.Insert("Bryant2","Lakers");
    hash.Insert("Webber4","Kings");
    hash.Insert("Arenas5", "Wizards");
    hash.Insert("Davis4","Clippers");  
    hash.Insert("Kidd5","Nets");
    hash.Insert("Bryantfew","Lakers");
    hash.Insert("Webber561","Kings");
    hash.Insert("Arenas515", "Wizards");
    hash.Insert("Davis4dsa","Clippers");
    hash.Insert("Kiddcsac5","Nets");
    hash.Display();
    
    // checl delete function
    hash.Delete("Kidd");
    hash.Delete("T-Mac");
    hash.Delete("Bryant2");
    hash.Delete("Webber4");
    hash.Delete("Kidd5");
    hash.Delete("Davis4dsa");
    hash.Delete("Kiddcsac5");
    hash.Delete("Arenas515");
    hash.Delete("Webber561");
    hash.Delete("Bryantfew");
	hash.Delete("Arenas5");
    hash.Delete("Webber");
    hash.Delete("Davis4");
//	hash.Delete("Bryant");
//    hash.Delete("Webber");
  


 //   cout << "\nAfter deleing Kidd and T-Mac:\n";
    hash.Display();
	return 0;
}

