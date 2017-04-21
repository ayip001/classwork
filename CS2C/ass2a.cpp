#include <iostream>

int gcd(int a, int b){
    // escape cases
    if(a == 0)
        return b;
    if(b == 0)
        return a;
    
    // conditions
    if(a % 2 == 0){
        if(b % 2 == 0)
            return 2 * gcd(a / 2, b / 2);
        return gcd(a / 2, b);
    }else{
        if(b % 2 == 0)
            return gcd(a, b / 2);
        return gcd((a + b) / 2, (a - b) / 2);
    }
}

int main(){
    std::cout 
        << "The GCD of 270 and 192 is " << gcd(270, 192) << std::endl
        << "The GCD of 1000012337 and 4 is " << gcd(1000012337, 4) << std::endl
        << "The GCD of 262144 and 131072 is " << gcd(262144, 131072);
    return 0;
}