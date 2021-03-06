#include <iostream>
#include <iomanip>
#include <time.h>

int gcd(int a, int b){
    // escape cases
    if(a == 0)
        return b;
    if(b == 0)
        return a;
    
    // conditions
    if(a % 2 == 0){
        if(b % 2 == 0)
            return 2 * gcd(a / 2, b / 2);       // both even
        return gcd(a / 2, b);                   // a even b odd
    }else{
        if(b % 2 == 0)
            return gcd(a, b / 2);               // a odd b even
        return gcd((a + b) / 2, (a - b) / 2);   // both odd
    }
}

int main(){
    clock_t t;
    t = clock();
    std::cout 
        << "The GCD of 270 and -192 is " << gcd(270, -192) << std::endl
        << "The GCD of 1000012337 and 4 is " << gcd(1000012337, 4) << std::endl
        << "The GCD of 262144 and -131072 is " << gcd(262144, -131072);
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
