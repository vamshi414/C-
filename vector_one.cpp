//vector STL
//begin(), end(), rbegin(), rend(),
//size(), max_size(),  capacity(), empty(), resize(int), 
#include<iostream>
#include<vector>

using namespace std;

int main()
{
	vector<int>g1;
	
	for(int i=1;i<=5;i++)
	  g1.push_back(i);
	  
	  cout << "output of begin to end\n";
	  for(auto it = g1.begin(); it!= g1.end(); ++it)
	     cout << *it << endl;
	     
	  cout << "output of end to begin\n";
	  
	  for(auto it = g1.rbegin(); it!= g1.rend(); ++it)
	     cout << *it << endl;
	     
	     cout << "size is:" << g1.size() << endl;
	     cout << "max_size:" << g1.max_size()<< endl;
	     cout << "capacity:" << g1.capacity()<< endl;
	     
	     if(g1.empty() == true)
	     {
	     	cout << "vector is empty" << endl;
		 }
		 else
		 {
		 	cout << "vector is not empty" << endl;
		 }
		 
		 g1.resize(4);
		 
		 cout << "new size:" << g1.size()<< endl;
		 
		 g1.shrink_to_fit();
		 for(int x: g1)
		 {
		 	cout << x << endl;
		 }
		 		 	     
	     g1.assign(5,10);
	     
	     for(int i=0;i<g1.size(); i++ )
	     cout << g1[i] << endl;
	     
	     
}
