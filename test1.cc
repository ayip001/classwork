#include <iostream>
#include <iomanip>
#include <time.h>

int main(){
    clock_t t;
    t = clock();
    int i = 0, j = 0, k = 0;
    int n = 1000;
    
    int sum = 0;

for( i = 1; i < n; ++i )

for( j = 1; j < i * i; ++j )

if( j % i == 0 )

for( k = 0; k < j; ++k )

++sum;
    
    
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;   // time in s
    time_taken *= 1000;                                 // time in ms
    
    std::fixed;
    std::setprecision(2);
    std::cout << std::endl << time_taken << " ms";
    
    return 0;
}

/* -------------------------- TEST RUN OUTPUT ---------------------------------

The GCD of 270 and -192 is 6
The GCD of 1000012337 and 4 is 1
The GCD of 262144 and -131072 is 131072
0.064 ms

Process exited with code: 0

---------------------------------------------------------------------------- */
