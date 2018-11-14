#include <iostream>
using namespace std;

class stackarray{
	private:
		int top;       // array top element
		int capacity; // array size
		int *stack;  // an array for stack
		void doublearray();
		
	public:

	  stackarray():top(-1), capacity(1){
	  stack = new int[capacity];
	  }
	  void pop();         // remove top element
	  void pushback(int x); // put element in
	  void getsize();
	  void clear();	
	  void Top();
	  void isempt();
};

  void stackarray::doublearray(){
  	
	if (top+1 == capacity) {
		capacity *=2;
	}
	int *newstack = new int[capacity];
	
	for (int i=0; i<capacity/2;i++){
		newstack[i]=stack[i];
	}
	
	delete [] stack;
	stack = newstack;
	
  }

  void stackarray::pushback(int x){
	if (top== capacity -1){  // array is full
		doublearray();
	}
  	stack[++top]=x;
  } 

  void stackarray::getsize(){
  	if (top==-1) {
  		cout<< "stack is empty"<< endl;
  		return;
	  }
  	cout << "the size is: "<<top+1<<endl;
  	
  }

  void stackarray::pop(){
  	
  	if (top==-1){
  		cout<<"stack is empty, can not pop"<<endl;
  		return;
	  }
  	//stack[top]=NULL;   //wrong way, need to write a destructor
  	top--;
  }
  
  void stackarray::Top(){
  	if (top==-1){
	  cout<<"stack is empty, no value"<< endl;
	  return;
	  }
  	cout << stack[top]<<endl;
  } 
  
  

  void stackarray::clear(){
  	
    delete [] stack;
    top=-1; 
  }


int main(){
	stackarray one;
	one.Top();
	one.pushback(2); 
	one.Top();
	one.pushback(4);
	one.pushback(8);
	one.Top();
	one.getsize();
	one.pop();
	one.Top();
	one.getsize();
	one.clear();
	one.getsize();
	one.Top();
	
	
	
	return 0;
}
