#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool f(int x, int y)
{
	return x>y;
}

int main()
{
	vector<int> A = {10,11,3,5,15};
	
	cout << A[1] << endl;
	
	sort(A.begin(), A.end() );
	
	bool present  = binary_search(A.begin(),A.end(), 3);
	if(present)
	{
		cout << "value detected" << endl;
	}
	
	bool present1 = binary_search(A.begin(), A.end(), 30 );
	if(!present1)
	{
		cout << "Not Present" << endl;
	}
 A.push_back(30);
	bool present2 = binary_search(A.begin(), A.end(), 30 );
	if(present2)
	{
		cout << " Present" << endl;
	}
	
	
	A.push_back(100);
	A.push_back(100);
	A.push_back(100);
	A.push_back(150);
	
	auto  it = lower_bound(A.begin(), A.end(), 100 );
	auto it1 = upper_bound(A.begin(), A.end(), 100 );
	
	cout << "it:" << *it << endl;
	cout << "it1:" << *it1 << endl;
	cout << it1-it << endl;	
	
	sort(A.begin(), A.end(), f );
	
	vector<int>::iterator it3;
	
	for(int &x: A)
	{
		x++;
		
    }
    
    for(int x : A )
    {
    	cout << x << endl;
	}
}
