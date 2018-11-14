#include <iostream>
using namespace std;

class quenenode{
	private:
		int data;
		quenenode *next;
	public:
		quenenode():data(0),next(0){}
		quenenode(int x):data(x),next(0){}		
	friend class quenelist;
};



class quenelist{
	private:
		quenenode *front;
		quenenode *back;
		int size;
	public:
		quenelist():front(0),back(0),size(0){}
		void push(int x);
		void pop();
		void getsize();
		void clear();
		void fvalue();		
		void bvalue();
};


void quenelist::push(int x){
	if (size==0){
		quenenode *newnode= new quenenode(x);
		front = newnode;
		back = newnode;
		size++;
		return;
	}
	
	quenenode *newnode =new quenenode(x);
	back->next = newnode;
	back= back->next;
	size++;	
}

void quenelist::pop(){
	if (size==0){
		cout <<"quene is empty"<<endl;
		return;
	}
	

	else{
		quenenode *current= front;
		front= front->next;
		delete current;
		current = 0 ;
		size--;
		return;
	}
}


void quenelist::getsize(){
	cout << "current size is: "<< size<<endl;
}

void quenelist::clear(){
	if (size==0){
		cout<<"quenelist is empty"<<endl;
		return;
	}

	while (front!=NULL){
		quenenode *current = front;
		front= front->next;
		delete current;
		current = 0;
		size --;		
	}
	
}

void quenelist::fvalue(){
	if (size == 0 ){
		cout << "quene is empty, no value can show"<<endl;
		return;
	}
	
	cout<<"the front value is: "<<front->data<<endl; 
	
}

void quenelist::bvalue(){
	if (size == 0 ){
		cout << "quene is empty, no value can show"<<endl;
		return;
	}
	
	cout<<"the back value is: "<<back->data<<endl; 
}


int main(){
	
	quenelist test;
	test.fvalue();
	test.push(3);
	test.bvalue();
	test.push(5);
	test.bvalue();
	test.push(7);
	test.bvalue();
	test.fvalue();
	test.getsize();
	test.pop();
	test.fvalue();
	test.getsize();
	test.bvalue();
	test.clear();
	test.getsize();
	test.fvalue();
	
	return 0;
}
