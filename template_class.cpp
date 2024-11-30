// class template
#include<iostream>
using namespace std;

template<class T1, class T2>
class A
{
   public:
   T1 num1 = 10;
   T2 num2 = 20.5;
   void disp()
   {
   	   cout << "output:" << num1 << "\t" << num2 << endl; 	

   }
};

int main()
{
	A<int,float>obj;
	obj.disp();
while(1);
}
