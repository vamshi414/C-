// Filestreams in C++
//ifstream -- > to read the files
//ofstream --> create files and writ the into to file

#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	ofstream filestream("Desktop\Sample.txt");
	
	if( filestream.is_open() )
	{
		filestream << "Welcome to C++\n";
		filestream << "The End\n";
	
	
	filestream.close();
	cout << "Create file success" << endl;

	}
	else
	{
		cout << "fail" << endl;
	} 
	string data;
	ifstream filestream2("Desktop\Sample.txt");
	
	if(filestream2.is_open() )
	{
		while( getline(filestream2,data) )
		cout << data << endl;
		
		filestream2.close();
	}
	return 0;
}
