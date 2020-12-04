// Friend Function and class in  c++
// when it is private only auth can access, but with friend we can access
// friend function is a non member fucntion of class, and can access the private in class
// declaration should be in class and edefinition will be outside of class
// we can introduce funtion to any number of class
//friend function objs as arguments

#include<iostream>
using namespace std;


class Box
{
	private:
		int length;
	public:
		Box() :  length(0) { }
		friend int printlength(Box);
		
};

int printlength(Box b)
{
	b.length = 10;
	return b.length;
}

int main()
{
	Box b;
	cout << "length: " << printlength(b)<< endl;
	while(1);
}





