/* Copy constructor  is type of construcotr which is used to create copy of already exisiting object of class type */
#include<iostream>
using namespace std;

class Simple
{
	private:
	  int x,y;
	public:
		Simple( int x1, int y1 )
		{
			x = x1;
			y = y1;
		}
		Simple(const Simple &sim)
		{
			x = sim.x;
			y = sim.y;
		}
		
		void display()
		{
			cout << x << " " << y << endl;
		}
};

int main()
{
	Simple obj1(10,20);
	Simple obj2 = obj1;
cout << "Normal Constructor:\t ";	
 obj1.display();
cout << "Copy Constructor:\t ";
 obj2.display();
while(1);
}
