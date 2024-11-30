/* Shallow Copy and Deep Copy of constructors */

#include<iostream>
using namespace std;

class Shalloc
{
	private:
		int *x;
	public:
		Shalloc( int m )
		{
			x = new int;
			*x = m;
		}
		Shalloc(const Shalloc &obj )
		{
			x = new int;
			*x = obj.getx();		
	    }
		
		int getx() const
		{
			  return *x;
		}
		
		void setx(int m)
		{
			*x = m;
		}
		
		void printx()
		{
			cout << "X:" << *x << endl;
		}
		
		~Shalloc()
		{
			delete x;
		}
};

int main()
{
	Shalloc obj1(10);
	Shalloc obj2 = obj1;
	obj1.printx();
	obj2.printx();
	
	obj1.setx(20);
	obj1.printx();
	obj2.printx();
	while(1);
}
