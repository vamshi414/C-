// polymorphism
// In shot this having many forms , by define: has the ability of message to dsiplayed in more than one form.
// Polymorphism cateroized into : Compile time and Run time
// Compile time  : function overload and operator overloas
// run time : virtual functions
//sample for function overload
#include<iostream>
using namespace std;

class Overload
{
	public:
		
		void fun()
		{
			 cout << "overload function" << endl;
		}
		
		void fun1(int x)
		{
			cout << "x:" << x << endl;
		}
		
		
		void fun2(double x)
		{
			cout << "x:" << x << endl;
		}
		
		void fun3(int x, int y)
		{
			cout << "x:" << x << "y:" << y << endl;
		}
		
};

int main()
{
	Overload obj1;
	obj1.fun();
	obj1.fun1(10);
	obj1.fun2(10.20);
	obj1.fun3(10,20);
while(1);
}

