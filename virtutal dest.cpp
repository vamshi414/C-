/* Virutal Destructors */
// Deleting derived class object using bass class type that has non-virtual make the undefined behavior,to 
// correct this we define virtual in base class to delete the derived class destrcutor properly
// constrcutors cant be virtual, because wheenevr constructor of a class is executed,there is no
//virtual table in memory which means no virtual pointer defined.hence constructors always be non-virtual.

#include<iostream>
using namespace std;

class base
{
	public:
	base()
	{
		cout << "construcitng base" << endl;
	}
	virtual ~base()
	{
		cout << "destructing base" << endl;
	}
	
	
};

class derived:public base
{
	public:
	derived()
	{
		cout << "constructing derived" << endl;
	}
	~derived()
	{
		cout << "destructing derived" << endl;
	}
	
};

int main()
{
	derived *d = new derived();
	base *bptr = d;
	delete bptr; 
while(1);
}

