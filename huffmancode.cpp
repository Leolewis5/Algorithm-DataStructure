#include <iostream>
#include <sstream>
using namespace std;


//  basic element, which include two content, 1. word and 2. which frequence;
class element{
	private:
		int freq;
		char name;
	public:
		element():freq(0),name(0){}  //constructor , name and freq set to 0
		
	friend class heap;
	friend class heapnode;
	friend class minheap;
	friend class huffmantree;
};

// basic minheap, which use to arrange oringinal char* into heap, and sort by minheap
class heap{
	private:
		element *e;  // element array
		int total;  // store how many different element in element array
	public:
		heap():e(0),total(0){};
		heap(char *);
		void construct(element*, stringstream &); // use to construct constructor
		void verify();   //use to print heap content to verify code 
		void verify2();  //use to print minheap content to verify code
		void minheap();  // sort heap into minheap

	friend class huffmantree;
	friend class heapnode;
	friend class minheap;
};

// heapnode is use to huffmantree use, every node have one element and two node pointer left and right
class heapnode{
	private:
		heapnode *left, *right;   
		element data;
	public:
		heapnode():data(),left(NULL),right(NULL){} //default constructor
		heapnode(const heapnode &a){ // use to copy heapnode, (maybe this one is duplicate...
			data = a.data;
			left = a.left;
			right = a.right;
		}
	friend class minheap;
	friend class huffmantree;
};

// minheap by heapnode
class minheap{
	private:
		heapnode *first;  //first pointer point to minheap, can be regard as heapnode array
		int total; //total element
	public:
		minheap():first(NULL),total(0){}// default constructor, in this project, we dont use it
		minheap(heap a); // copy oringal heap array(content only get element) to heapnode array (content has additional pointer left and right)
		void verify(); //this is use to print minheap content for verify code
		void insert(heapnode *); // insert function, use to insert new heap node and sort this minheap by element frequence
		heapnode deletetop(); //delete min frequence element and pop out, also sort this minheap by element frequence
	friend class huffmantree;
};

//huffman tree
class huffmantree{
	private:
		heapnode *root;// first pointer point to tree root
	public:
		huffmantree():root(NULL){}
		huffmantree(minheap *); //construct huffmantree by minheap
		void construct(minheap *); //use into constructor
		heapnode *merge(heapnode*,heapnode*); //use into constructor, this will delete two min frequence element and merge into newone the insert new one into minheap
		void printcode(heapnode *,string); //print huffmancode
		void getcode(); //call printcode
};


huffmantree::huffmantree(minheap *a){
	construct(a);
}


//pop two min element and merge into new heapnode then pushback into minheap
void huffmantree::construct(minheap *a){
	heapnode *newone = new heapnode;
	while (a->total>1){
		cout <<"===construct huffmantree process==="<<endl;
	heapnode *one = new heapnode(a->deletetop()); //maybe this one it is not necessary use pointer?
	heapnode *two = new heapnode(a->deletetop()); //and this one
	newone = merge(one,two);
	a->insert(newone);
   }
   root = newone;
}


void huffmantree::getcode(){
	heapnode *current = root;
	
	printcode(current,"");
}


void huffmantree::printcode(heapnode *current,string str){
	if (!current) return;
	if (current->data.name!=0)
		cout<<"element: "<< current->data.name<< "  code is: "<<str<<endl;
	printcode(current->left,str+"0");
	printcode(current->right,str+"1");
}


heapnode *huffmantree::merge(heapnode *one, heapnode *two){
	heapnode *newone= new heapnode;
	newone->left= one;
	newone->right= two;
	newone->data.freq = one->data.freq+two->data.freq;
	return newone;
}


minheap::minheap(heap a):total(0){
	first = new heapnode[100];
	total = a.total;
	for (int i=1; i <=a.total;i++ ){
		first[i].data=a.e[i];
	}
}


void minheap::insert(heapnode *addone){
	first[++total] = *addone; //because I pass by reference, so I need to dereference
	int j = total;
	while (j>1){
		if (addone->data.freq<first[j/2].data.freq){
			first[j]=first[j/2];
			j/=2;
		}
		else{
			first[j]= *addone;
			return;
		}
	}
	first[j]=*addone;
}


// minheap deletetop
heapnode minheap::deletetop(){
	heapnode popone = first[1];      //ready for pop
	heapnode shift = first[total];   // let end do minheap sort
	heapnode clean;                  // clean end item
	first[total]= clean;
	total--;
	int i = 1, j =2;
	int dd=1;
	while (j<=total){
		if (j<total)
			if (first[j].data.freq>first[j+1].data.freq) j++;
			if (shift.data.freq>first[j].data.freq){
				first[i]=first[j];
				i=j;
				j*=2;
			}
			else{
				break;
			}
	}
	first[i]=shift;
	cout <<"pop element is: "<< popone.data.name<<"  frequence is:  "<<popone.data.freq<<endl;
	return popone;	
}

	
// heap constructor
heap::heap(char *string){
	stringstream ss;
	ss<< string;
	e = new element[100];
	
	construct(e, ss);
}


// this is use to construct original heap
void heap::construct(element *e, stringstream &ss){
	char data = 0;
	int n = 0;

	while (ss>>data){
		if (n==0){
			e[0].freq=1;
			e[0].name=data;
			
			n++;
			continue;
		}
		bool jj= 1;
		
		for (int i=n-1; i>=0; i--){
			if (data==e[i].name){
				e[i].freq+=1;
				jj=0;
			}
		}
		
		if (jj){
			e[n].freq=1;
			e[n].name=data;
			n++;
		}
	}
	total = n;
}


//========this is use to sort heap======
void heap::minheap(){
	element *sort = new element[100];
	element *current = e;
	int sorttotal=0;

	for (int i= 0; i<8; i++){

		sort[++sorttotal]=e[i];
		int n = sorttotal;
		while (n !=0 && e[i].freq<sort[n/2].freq){
			
			sort[n]=sort[n/2];		
			n=n/2;
			
		}
		
		sort[n]=e[i];
	}
	
	e =sort;
	delete current;
}

//=================for data verify=====================
void heap::verify(){
	int n = total;
	for(int i =0 ; i<n ; i++){
		cout <<"element: "<< e[i].name<<" frequence: "<<e[i].freq<< endl;
	}

}


void heap::verify2(){
	int n = total;
	for(int i =1 ; i<n+1 ; i++){
		cout <<"element: "<< e[i].name<<" frequence: "<<e[i].freq<< endl;
	}

}

void minheap::verify(){
	int n = total;
	for(int i =1 ; i<n+1 ; i++){
		cout <<"element: "<< first[i].data.name<<" frequence: "<<first[i].data.freq<< endl;
	}

}


//=================for data verify end=====================

int main(){
	
	char *T = "ferafaefearzcevzzzzzzzzxcvferv";
	heap t(T);
	t.verify();
	t.minheap();
	cout <<"minheap sort"<<endl;
	t.verify2();
	minheap AA(t);
	cout <<"minheap verify"<<endl;
	AA.verify();
//	AA.deletetop();
	cout <<endl;
	AA.verify();
	huffmantree SS(&AA);
	SS.getcode();
	
	
	return 0;
}
