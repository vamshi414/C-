// LIST
// LIST is one more container in C++, this is bit reverse to Vector, where in vector the memory is in contingnous, whereas
//in LIST we can insert in mid too, basically which is like LInkedlist container
// some specfiers in LISt:begin,push_back,push_front,pop_back,pop_front,empty,insert


#include<iostream>
#include<algorithm>
#include<list>

using namespace std;

int main()
{
	list<int>l = {1,2,3,4,5};
	
	l.push_front(100);
	l.push_back(20);

	auto it = std::find(l.begin(), l.end(),5);
	if (it != l.end())
	{
		l.insert(it,25);
	}
	
	
	for(int n:l)
	{
		cout << n << "\t" << endl;
	}
}
