#include<iostream>
#include<vector>

using namespace std;

int main()
{
	std::vector<int> vecofints;
	
	for(int i=0;i<=10;i++)
	   vecofints.push_back(i);
	   
	std::vector<int>::iterator it = vecofints.begin();
	
	while(it != vecofints.end())
	{
		std::cout<<*it<< " , ";n
		it++;
	}
	
	std::cout << endl;
	
	for(int i=0; i<vecofints.size(); i++ )
	 std::cout << vecofints[i] << " ," ;
}
