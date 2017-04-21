#include <iostream>
#include <math.h>

using namespace std;

int binary(int num)
{
    if (num == 0)
        return 0;
    
    if (num & 1)
        return 1 + binary(num >> 1);
    
    return binary(num >> 1);
}

int main()
{
    int N;
    cout << "Enter N: ";
    cin >> N;
    cout << "Number of 1's in binary representation of " << N << " is " << binary(N) << endl;
    return 0;
}

//-----------------------------------------Sample Output 1------------------------------------------------
//12
//nter N: Number of 1's in binary representation of 12 is 2
//Program ended with exit code: 0
