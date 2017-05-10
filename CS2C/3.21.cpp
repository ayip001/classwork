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
	cout << 
		"\"b(a)l(a)n(c)e[d][{}]\" is balanced?: " << 
		isBalanced("b(a)l(a)n(c)e[d][{}]") << 
		"\n\"not ()[{]} balanced\" is balanced?: " <<
		isBalanced("not ()[{]} balanced") << 
		"\n\"empty and balanced\" is balanced?: " <<
		isBalanced("empty and balanced");
		
	return 0;
}

/* ---------------------------------- TEST ------------------------------------

"b(a)l(a)n(c)e[d][{}]" is balanced?: 1
"not ()[{]} balanced" is balanced?: 0
"empty and balanced" is balanced?: 1

Process exited with code: 0

---------------------------------------------------------------------------- */