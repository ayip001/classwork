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
        << numOfBinOnesInNum(-17) << std::endl        // -10001            (2)
        << numOfBinOnesInNum(65536) << std::endl      // 10000000000000000 (1)
        << numOfBinOnesInNum(857) << std::endl;       // 1101011001        (6)
    
    
    // PART 3 TEST
    std::cout << "\nTesting template functions:"
        << "\nMax of 4, 5: " << getMax(4, 5)
        << "\nMin of -3.2, 1.7: " << getMin(-3.2, 1.7)
        << "\nMax of 'L', '$': " << getMax('L', '$')
        << "\nMin of \"foo\", \"bar\": " << getMin("foo", "bar")
        << "\nMax of 0L, 0L: " << getMax(0L, 0L);
    
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
Min of "foo", "bar": bar
Max of 0L, 0L: 0

Process exited with code: 0

---------------------------------------------------------------------------- */