#include<iostream>
#include<list>
#include<string>

using namespace std;

template <typename type>
list<type> Intersect(list<type> L1, list<type> L2)
{
    list<type> result;
    typename list<type>::const_iterator L1pos = L1.begin(), L2pos = L2.begin();
    while( L1pos != L1.end() && L2pos != L2.end() )
    {
        if( *L1pos < *L2pos )
            ++L1pos;
        else if( *L1pos > *L2pos )
            ++L2pos;
        else
        {
            result.push_back(*L1pos);
            ++L1pos;
            ++L2pos;
        }
    }
    return result;
}

template <typename type>
void printList(list<type> L)
{
    typename list<type>::const_iterator LPos = L.begin();
    
    cout << '(';
    while( LPos != L.end() )
    {
        cout << *LPos;
        if(++LPos != L.end())
            cout << ", ";
    }
    cout << ')';
}

int main(){
    list<int> List1;
	list<int> List2;

	List1.push_back(1);
	List1.push_back(2);
	List1.push_back(3);
	List1.push_back(4);

	List2.push_back(2);
	List2.push_back(4);
	List2.push_back(6);
	List2.push_back(8);
	
	cout << "(1, 2, 3, 4) n (2, 4, 6, 8): ";
	printList(Intersect(List1, List2));
    
    List1.clear();
    List2.clear();
    
    List1.push_back(1);
	List1.push_back(3);
	List1.push_back(5);
	List1.push_back(7);

	List2.push_back(2);
	List2.push_back(4);
	List2.push_back(6);
	List2.push_back(8);
	
	cout << "\n(1, 3, 5, 7) n (2, 4, 6, 8): ";
	printList(Intersect(List1, List2));
	
	List1.clear();
    List2.clear();
    
    List1.push_back(1);
	List1.push_back(2);
	List1.push_back(3);
	List1.push_back(4);

	List2.push_back(2);
	List2.push_back(3);
	
	cout << "\n(1, 2, 3, 4) n (2, 3):       ";
	printList(Intersect(List1, List2));
    
    return 0;
}

/* ---------------------- TEST ------------------------------------------------

(1, 2, 3, 4) n (2, 4, 6, 8): (2, 4)
(1, 3, 5, 7) n (2, 4, 6, 8): ()
(1, 2, 3, 4) n (2, 3):       (2, 3)

Process exited with code: 0

---------------------------------------------------------------------------- */