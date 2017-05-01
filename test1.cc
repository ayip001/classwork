#include<iostream>
#include<list>
#include<string>

using namespace std;


int main(){
    list<int> List1;
	list<int> List2;
	list<int> ListEmpty;

	List1.push_back(1);
	List1.push_back(2);
	List1.push_back(3);
	List1.push_back(4);

	List2.push_back(2);
	List2.push_back(4);
	List2.push_back(6);
	List2.push_back(8);
	
	typename list<int>::const_iterator L1pos = List1.begin(), L2pos = List2.begin();
	cout << *L1pos;
	L1pos++;
	cout << *L1pos;
    
    
    return 0;
}