// Function Templates
// template <class type> ret_type  func_name(param list)

#include<iostream>
using namespace std;

template<class x, class y> void fun(x a, y b)
{
	cout << "a:" << a << endl;
	cout << "b:"<< b << endl;
}

template<class x> void fun(x a)
{
	cout << "a:" << a << endl;
}

template <class T> T add(T &a, T &b)
{
	T result = a+b;
	return result;
}

int main()
{
	int i=10,j=20;
	float x=10.5,y=20.6;
	
	cout << "int:" << add(i,j) << endl;
	cout << "float:" << add(x,y) << endl;

      fun(1,1.5);
      fun(5);
while(1);
}
