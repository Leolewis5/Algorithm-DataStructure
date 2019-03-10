#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
using namespace std;

int main()
{
  int x = 0x12345678;

  char *y = (char*)&x;
  	cout<<setw(15)<<"x: "<<x<<endl;
	cout<<setw(15)<<"&x: "<<&x<<endl;
	cout<<setw(15)<<"(char)x: "<<(char)x<<endl;	
	cout<<setw(15)<<"(char*)&x: "<<(char*)&x<<endl;
	cout<<setw(15)<<"y: "<<y<<endl;
	cout<<setw(15)<<"*y: "<<*y<<endl;
	cout<<setw(15)<<"*(y+1): "<<*(y+1)<<endl;
	cout<<setw(15)<<"*(y+2): "<<*(y+2)<<endl;
  //printf("%c\n",*y+48);
}
