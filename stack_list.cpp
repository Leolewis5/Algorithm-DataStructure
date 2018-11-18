#include <iostream>
using namespace std;


class listnode{
	public:
		listnode():data(0),next(0){}
		listnode(int x):data(x),next(0){}
		listnode(int x, listnode *addtop):data(x),next(addtop){}
		void print(){
			cout << data<<endl;
		}
	private:
		int data;
		listnode *next;
	friend class stacklist;
	
};


class stacklist{
	private:
	  listnode *Top;
	  int height;
	public:
	  stacklist():Top(0),height(0){}
	  void pop();         // remove top element
	  void pushback(int x); // put element in
	  void getsize();
	  void clear();	
	  void Topvalue();
	
};

void stacklist::pushback(int x){
	if (Top==NULL){
		listnode *newtop= new listnode (x);
		Top= newtop;
		height++;
		return;
	}
	
	listnode *newtop = new listnode(x, Top);
	Top = newtop;	
	height ++;	
}

void stacklist::pop(){
	if (height == 0 ){
		cout << "stack is empty"<<endl;
		return;
	}
	
	listnode *current=Top;
	Top=Top->next;
	delete current;
	 height--;
}

void stacklist::Topvalue(){
	if (Top==NULL){
		cout << "stack is empty, no top value"<<endl;
		return;
	}
	cout << Top->data <<endl;		
}

void stacklist::getsize(){
	cout <<"the size is: "<< height <<endl;	
}

void stacklist::clear(){
	while (Top!=NULL){
		listnode *current = Top;
		Top=Top->next;
		delete current;
		current=0;
	}
	height=0;
}




int main(){

	stacklist test;
	test.Topvalue();
	test.getsize();
	test.pushback(4);	
	test.pushback(7);	
	test.pushback(6);
	test.Topvalue();
	test.getsize();
	test.pop();
	test.getsize();	
	test.Topvalue();
	test.clear();
	test.getsize();	
	test.Topvalue();	

/*
	listnode *a = NULL;
	listnode *b =new listnode();
	
	if (a==b) cout <<"yyy";
	b->print();
	a->print();
this is used to test NULL pointer

*/
	
	return 0;
}
