//file read in vector

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

bool getfilecontent(std::string filename, vector<std::string>&vecstr)
{
	std::ifstream in(filename.c_str());
	
	if(!in)
	{
		 cout << "Not able to open the file" <<endl;
		 return false;
	}
	
	std::string str;
	
	while(std::getline(in,str))
	{
		if(str.size() >0)
		{
			vecstr.push_back(str);
		}
	}
	in.close();
	return true;
}

int main()
{
	vector<std::string>vecstr;
	
	bool result = getfilecontent("DesktopSample.txt", vecstr);
	
	if(result)
	{
		for(std::string data : vecstr)
		{
			cout << data<< endl;
		}
	}
}
