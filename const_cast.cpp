//const_cast 
//expression for this :  const_cast<T>(v) , can be used to change the const or volatile qualifiers of pointers r reference
//where T mube a pointer, reference r pointer to member type

#include<iostream>
using namespace std;

int main()
{
	int a1=20;
	const int *b1 = &a1;
	int *c1 = const_cast<int*>(b1);
	cout << *c1 << endl;
	*c1 = 30;
	cout << *c1 << endl;
	while(1);
}
