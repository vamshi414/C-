// vector
// lets take data :  1,2,5,6,5,8,5,9,10,11,12
//Remove all occuerences of an element say:5
//two ways :  erase and remove

#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;

void remove_alloccuerences(std::vector<int>&v, int elem)
{
	v.erase(std::remove(v.begin(), v.end(), elem) , v.end() );
}

void displayv(std::vector<int> &v)
{
    std::vector<int >::iterator it = v.begin();
    while(it != v.end())
    cout << *it++ << " ";
    cout << endl;
}
int main()
{
	std::vector<int>v = {1,2,5,6,5,8,5,9,10,11,12};
	remove_alloccuerences(v,5);
	displayv(v);
	
}

