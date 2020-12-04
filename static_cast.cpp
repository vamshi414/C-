// static_cast
//it is compile time cast, it does things like implicit converstions {float,int}
//syntax :  static_cast<type>(variable)

#include<iostream>
using namespace std;

int main()
{
	float f=10.20;
	int i = f;
	cout << "i:" << i << endl;
	i = static_cast<float>(i);
	cout <<"i:" << i << endl;
while(1);
}


