#include <iostream>
using namespace std;

class Polynomial;
int MaxTerm =100;

class Term{
	private:
		int coef;
		int exp;
	public:
	Term():coef(0),exp(0){}
	friend Polynomial;
};

class Polynomial{
	private:
		static Term termArray[100];
		static int free;
		int start,end;
	public:
		Polynomial();
		void print();
		Polynomial &AddNewTerm(int , int);
		Polynomial Add(Polynomial);
		char compare(int, int);
		void sort();
};


Term Polynomial::termArray[100];
int Polynomial::free=0;

Polynomial::Polynomial(){
	start=free;
	end=free;
	free++;
}

Polynomial &Polynomial::AddNewTerm(int newcoef, int newexp){
	
	termArray[end].coef=newcoef;
	termArray[end].exp=newexp;
	end++;
	free++;
	sort();
	return *this;
}

void Polynomial::print(){
	cout <<"f(x)=";
	for (int i = start; i<end-1;i++)
	cout << termArray[i].coef <<"x^"<<termArray[i].exp<<"+ ";
	cout <<termArray[end-1].coef <<"x^"<<termArray[end-1].exp<<endl;
}

Polynomial Polynomial::Add(Polynomial B){
	Polynomial C;
	int a=start; int b=end; int c=B.start; int d=B.end;
	while (a<=b&&c<=d)
		switch(compare(termArray[a].exp,termArray[c].exp)){
			case '>': 
				C.AddNewTerm(termArray[a].coef,termArray[a].exp);
				a++;
				break;
			case '<':
				C.AddNewTerm(termArray[c].coef,termArray[c].exp);
				c++;
				break;
			case '=':
				int e = termArray[a].coef+termArray[c].coef;
				if (e) C.AddNewTerm(e,termArray[a].exp);
				a++;c++;
		}
	for (;a<=b;a++){
		C.AddNewTerm(termArray[a].coef,termArray[a].exp);
	} 
	for (;c<=d;c++){
		C.AddNewTerm(termArray[c].coef,termArray[c].exp);
	}
	return C;
}

void Polynomial::sort(){
	//insertion sort method
	for (int i = 1; i <end; i++){
		int scoef= termArray[i].coef;
		int sexp = termArray[i].exp;
		int j = i -1;
		for (j;j>=start;j--){
			if (termArray[j].exp<sexp) {
				termArray[j+1]=termArray[j];
			}
			else {
				break;
			} 
		}
		termArray[j+1].coef=scoef;
		termArray[j+1].exp=sexp;
	}
	
}

char Polynomial::compare(int a, int b){
	if (a>b) return '>';
	else if (a<b) return '<';
	else return '=';
}

int main(){
	Polynomial A;
	A.AddNewTerm(3,5).AddNewTerm(4,3).AddNewTerm(10,2).AddNewTerm(10,7);
	A.print();
	Polynomial B;
	B.AddNewTerm(6,7).AddNewTerm(5,3).AddNewTerm(3,1);
	B.print();
	Polynomial C =A.Add(B);
	C.print();
	
	return 0;
}
