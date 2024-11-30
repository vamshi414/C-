// vector to insert at specific position

#include<iostream>
#include<string>
#include<vector>

using namespace std;

template<typename T>
void print(T &vectofints, std::string delimiter=",")
{
	for(auto elem:vectofints)
	{
		std::cout <<elem<<delimiter;
		
	}
}
int main()
{
	
	std::vector<int>vectofints = {1,3,5,7,9,10};
	
	auto it1 = vectofints.insert(vectofints.begin()+1,2);
	it1 = vectofints.insert(vectofints.begin()+3,4);
	it1 = vectofints.insert(vectofints.begin()+5,6);
	it1 = vectofints.insert(vectofints.begin()+7,8);
	cout << *it1 << "\t" << endl;
	
	print(vectofints);
}
