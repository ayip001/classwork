// apparently teacher wanted minus sign as an additional 1.

#include <iostream>
#include <string>

// PART 1
// Number of binary ones in a number
int numOfBinOnesInNum(int input){
    // negative -> positive
    if(input < 0)
        input = -input;
    
    // escape cases
    if(input == 0)
        return 0;
    if(input == 1)
        return 1;
    
    // even
    if(input % 2 == 0)
        return numOfBinOnesInNum(input / 2);
    
    // odd
    return numOfBinOnesInNum((input - 1) / 2) + 1;
}

/* ----------------------------- PART 2 ---------------------------------------

a.) SUM(i = 0, inf, 1 / 4 ^ i)
    = 1 / (1 - 1/4)
    = 4 / 3 ,,

b.) SUM(i = 0, inf, i / 4 ^ i)
    = 4 / (4 - 1) ^ 2 | identity SUM(i = 0, inf, i / a ^ i) = a / (a - 1) ^ 2 
    = 4 / 9,,
    
c.) SUM(i = 0, inf, i ^ 2 / 4 ^ i)
    = (16 + 4) / (4 - 1) ^ 3 
        | identity SUM(i = 0, inf, i ^ 2 / a ^ i) = a (a + 1) / (a - 1) ^ 3
    = 20 / 27 ,,
    if not using the identity, solve by reducing i ^ 2 / 4 ^ i to
    (i / 2 ^ i) ^ 2
    
d.) SUM(i = 0, inf, i ^ N / 4 ^ i) 
        can be represente the Hurwitz Lerch transcendent
    SUM(i = 0, inf, z ^ i / (a + k) ^ i) = Zeta(z, s, a) which cannot be 
    represented with a single answer in terms of the original numbers
    

---------------------------------------------------------------------------- */

// PART 3
template <class myType>
myType getMax(myType a, myType b){
    return (a > b ? a : b);
}

template <class myType>
myType getMin(myType a, myType b){
    return (a < b ? a : b);
}

int main(){
    // PART 1 TEST
    std::cout << "Testing numbers of '1's recursion:\n"
        << numOfBinOnesInNum(-18) << std::endl        // -10001            (2)
        << numOfBinOnesInNum(65536) << std::endl      // 10000000000000000 (1)
        << numOfBinOnesInNum(857) << std::endl;       // 1101011001        (6)
    
    
    // PART 3 TEST
    std::cout << "\nTesting template functions:"
        << "\nMax of 4, 5: " << getMax(4, 5)
        << "\nMin of -3.2, 1.7: " << getMin(-3.2, 1.7)
        << "\nMax of 'L', '$': " << getMax('L', '$')
        << "\nMin of \"barrrrrrrr\", \"bar\": " << getMin("barrrrrrrr", "bar")
        << "\nMax of 0L, 0L: " << getMax(0L, 0L)
        << "\nMin of \"foo\", \"foo\": " << getMin("foo", "foo");
    
    return 0;
}

/* ---------------------------- RUN RESULT ------------------------------------

Testing numbers of '1's recursion:
2
1
6

Testing template functions:
Max of 4, 5: 5
Min of -3.2, 1.7: -3.2
Max of 'L', '$': L
Min of "barrrrrrrr", "bar": bar
Max of 0L, 0L: 0
Min of "foo", "foo": foo

Process exited with code: 0

---------------------------------------------------------------------------- */