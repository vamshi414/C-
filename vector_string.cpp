//vector string
//g++ --std=c++11 sample.cpp

#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main()
{
	std::vector<std::string>vecstr;
	
	cout << "sizeof vector" << vecstr.size() << endl;
	
	vecstr.push_back("Vamshi");
	vecstr.push_back("Latha");
	vecstr.push_back("Jahnavi");
	
	cout << "size of vector" << vecstr.size() << endl;
	
	for(std::string data: vecstr)
	{
		cout << data << "\t" << endl;
	}
}
