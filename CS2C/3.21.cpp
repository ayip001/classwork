#include<iostream>
#include<string>
#include<stack>

using namespace std;
 
bool isPair(char open, char close)
{
	if( open == '(' && close == ')' )
		return true;
	if( open == '{' && close == '}' )
		return true;
	if( open == '[' && close == ']' )
		return true;
	return false;
}

bool isBalanced(string str)
{
	stack<char>  S; // stack of opening brackets
	
	for( int i = 0; i < str.length(); i++ )
	{
		if( str[i] == '(' || str[i] == '{' || str[i] == '[' )
			S.push(str[i]);
			
		if( str[i] == ')' || str[i] == '}' || str[i] == ']' )
		{
			if( S.empty() || !isPair(S.top(), str[i]) )
				return false;
			S.pop();
		}
	}
	
	return S.empty() ? true : false;
}

int main()
{
	string test;
	cout << "Please enter test expression: ";
	cin >> test;
	cout << "Balanced: " << isBalanced(test);
}