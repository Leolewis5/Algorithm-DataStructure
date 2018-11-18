#include <iostream>
using namespace std;

class cquene{
	private:
		int front,back,size;
		int *quene;
		void doublesize();
	public:
		cquene():front(0),back(0),size(5){
			quene = new int[size];
		}
		void pop();
		void fvalue();
		void bvalue();
		int getsize();
		void getlarge();
		void push(int x);
};


void cquene::push(int x){
	if ((back+1)%size==front) doublesize();
	
	back=(back+1)%size;
	quene[back]=x;	
//	cout<<"==========debug push number====="<<back<<endl;
}

void cquene::pop(){
	if (front==back){
		cout<<"quene is empty"<<endl;
		return;
	}
	front=(front+1)%size;
}

void cquene::fvalue(){
	if (front==back){
		cout<<"quene is empty, no fvalue"<<endl;
		return;
	}
	cout<<"front value is: "<<quene[(front+1)%size]<<endl;
}

void cquene::bvalue(){
	if (front==back){
		cout<<"quene is empty, no bvalue"<<endl;
		return;
	}
	cout<<"back value is: "<<quene[back]<<endl;
}

int cquene::getsize(){
	int sizze;
	if (front == back) return 0;
    if (front < back) {
        sizze = back - front;
    }
    else {
        sizze = size - (front - back);
    }

    return sizze;
} 

void cquene::doublesize(){
	int sizze=getsize();
	size = size*2;
	int *newquene = new int[size];
	int j=0; 
//	cout << "=====sizze"<<sizze<<endl;
	for (int i=0 ; i<=sizze; i++){
		j++;
		newquene[j]=quene[(front+1+i)%size];
//		cout <<"===debug j value=="<< j <<endl;
	}
	delete [] quene;
	quene = newquene;
	front=0;
	back=j;
//	cout<<"=====debug after double  front and back: "<<front<<"   "<< back<<endl;
}

void cquene::getlarge(){
	cout << "current quene big as: "<<size<<endl;
}

int main(){
	
	cquene test;
	cout <<"size is: "<<test.getsize()<<endl;
	test.fvalue();
	test.bvalue();
	test.push(1);
	test.push(2);
	test.push(3);
		cout <<"size is: "<<test.getsize()<<endl;
	test.getlarge();
	test.push(4);
	test.pop();
	test.fvalue();
	test.bvalue();
	test.pop();
	test.push(6);
	test.push(7);
	test.fvalue();
	test.bvalue();
		cout <<"size is: "<<test.getsize()<<endl;
 		test.getlarge();
	test.push(9);

		cout <<"size is: "<<test.getsize()<<endl;
		test.getlarge();
	test.fvalue();
	test.bvalue();

	
	return 0;
}	
