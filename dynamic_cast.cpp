//dynamic-cast
//syntax:  dynamic_cast<new_type> (expression)
// dynamic_cast is used at run time to findout correct down-cast
//Need one virtual function in base class
//if dynamic_cast is successfull, then it returns a new type
//if cast fails and new_type is pointer type , it returns null pointer of that type
//if cast fails and new_type is reference type, it returns a exception std::bad_cast

#include<iostream>
using namespace std;

class Base
{
	virtual void print()
	{
		cout << "Base" << endl;
	}
	
};

class Derived1:public Base
{
	void print()
	{
		cout << "Derived1" << endl;
	}
};

class Derived2:public Base
{
	void print()
	{
		cout << "Dervied2" << endl;
	}
};

int main()
{
	Derived1 d1;
	Base *bp = dynamic_cast<Base*>(&d1);
	
	Derived1 *d2 = dynamic_cast<Derived1*>(bp);
	
	if(d2 == NULL)
	{
		cout << "NULL" << endl;
	}
	else
	{
		cout << "NOT NULL" << endl;
	}
	
	try {
	
	Derived2 &r1 = dynamic_cast<Derived2&>(d1);
   } catch(std::exception &e )
     {
     	cout << e.what() << endl;
	 }
}
