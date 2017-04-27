#include<iostream>
#include<stack>
#include<string>
#include<list>
using namespace std;

list intersect(list L1, list L2)
{
    list result;
    position L1pos = first(L1), L2pos = first(L2), resultPos = first(result);
    while( L1pos != NULL && L2pos != NULL )
    {
        if( L1pos->element < L2pos->element )
            L1pos = L1pos->next;
        else if( L1pos->element > L2pos->element )
            L2pos = L2pos->next;
        else
        {
            insert(L1pos->element, result, resultPos);
            L1pos = L1pos->next;
            L2pos = L2pos->next;
            resultPos = resultPos->next;
        }
    }
    return result;
}