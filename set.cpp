//STL set

#include<iostream>
#include<set>
#include<algorithm>

using namespace std;

void set_demo()
{
	set<int>s;
	s.insert(1);
	s.insert(2);
	s.insert(-1);
	s.insert(-10);
	
	for(int x: s)
	cout << x  << " ";
	cout << endl;
}

int main()
{
	set_demo();
}
