#include<iostream>
#include<vector>
#include<string>

using namespace std;

template<typename T>
void print(T &vectofints, std::string delimiter=",")
{
	for(auto elem:vectofints)
	{
		cout << elem <<delimiter;
	}
}


int main()
{
	vector<int>vectofints = {1,2,3,4,5,6,7,8,10};
	
	std::cout << "original vector" << endl;
	print(vectofints);
	std:cout<<endl;
	std::cout << "original vector" << endl;
	vectofints[3] = 11; //changign the element by operator
	
	
	int &ref = vectofints[4];
	
	ref = 12;
	print(vectofints);
	
}
