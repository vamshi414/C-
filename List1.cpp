// LIST covering like :  push_back,push_front, pop_front, pop_back and reverse

#include<iostream>
#include<list>
#include<algorithm>

using namespace std;

template<typename T>
void showlist(T &g)
{
	
/*	list<int>::iterator it;
	
	for(it=g.begin(); it!=g.end(); ++it)
	{
		cout << *it << "\t"<< endl;
	} */
	
	for(auto elem:g)
	{
		cout << elem << endl;
	}
	cout << endl;
	
}


int main()
{
	list<int> glist1,glist2;
	
	for(int i=0;i<10;i++)
	{
		glist1.push_back(i*2);
		glist2.push_back(i*3);
	}
	
	cout << "List 1:" << endl;
	showlist(glist1);
	cout << "List 2:" << endl;
	showlist(glist2);
	
	glist1.pop_front();
	cout << "After popping Front" << endl;
	showlist(glist1);
	
    glist2.pop_back();
    cout << "After popping Back" << endl;
    showlist(glist2);
    
    glist1.reverse();
    cout <<"Reversing List1:"<< endl;
	showlist(glist1);
	
	glist2.reverse();
	cout << "Reversing List2:" << endl;
	showlist(glist2);
	 
    
    
}
