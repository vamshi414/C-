// Virutal FUnctions C++
//virtual function is  a member function in the base class which we can redfine in the derived class.
// it is used to tell the compiler to perform the late binding or Dynamic linkage
//There is a necessity to use the single pointer to refer all the objects from different classes,we create pointer
//to the base class that refers to the derived objects,but when the base class pointer contains the address of derived class 
//object always execute the base class oject, to overcome this we need virtual function
//virtual functions always members of some classes, virtual functions must be defined in base class
//virtual functions cannot be static.

#include<iostream>
using namespace std;

class A
{
	int x=10;
	public:
	virtual	void display()
		{
			cout << "X:" << x << endl;
		}
		
};

class B : public A
{
	int y=5;
	public:
		void display()
		{
			cout << "Y:" << y <<  endl;
		}
};

int main()
{
	A *a;
	B b;
	a = &b;
	a->display();
while(1);
}
