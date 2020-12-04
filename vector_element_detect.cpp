//vector data element detect

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	vector<int>vectofints = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,16,18,19,20};
	
/*	std::vector<int>::iterator it = std::find(vectofints.begin(), vectofints.end(), 20);
	
	if(it != vectofints.end())
	{
		std::cout << "element found:" <<*it << endl;
	}
	else
	{
		std::cout << "element not found:" << *it << endl;
	}*/
	
	bool found=false;
//	std::vector<int>::iterator elem;
	for(auto elem: vectofints)
	{
		if(elem == 20)
		{
			found = true;
			break;
		}
	}
	
	if(found)
	{
		cout << "element found :" <<  """"<< endl;
	}
	else
	{
		cout <<"element not found:" <<""  << endl;
	}
}
