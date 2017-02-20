#include <iostream>
#include <string>
#include <climits>
#include <cmath>
#include <sstream>
#include <ctime>       
#include <stdlib.h>   

using namespace std;

/*checklist
Act1:
BooleanFunc will contain a truthTable (a dynamic array) which defines the boolean function being represented.
We can load this truthTable using a mutator, setTruthTable() , and change the function it represents
We will not be able to change the size of the table (i..e. #inputs to the function) after an object is instantiated
we can totally redefine the object using the assignment operator, which will have the effect of giving it a new size.
eval( int ) evaluate the state (output) of the function based on input integers
getState() store the most recently evaluated output in an internal bool state member, so we can call eval() once, 
but get the resulting state later without having to re-call eval()

DONE static public
DONE int MAX_TABLE_FOR_CLASS = 65536; // that's 16 binary input lines
DONE int DEFAULT_TABLE_SIZE = 16

DONE private 
DONE int tableSize - reflects the number of inputs. tableSize of 4 would imply two binary inputs; a size of 16 would imply four binary inputs.
    one int to act as our multi-bit input, a tableSize of 4 means the valid input ints are 0-3.  Size of 16 means valid input ints are 0-15.
DONE bool *truthTable - to be dynamically allocated and de-allocated) whose size is tableSize.
DONE bool evalReturnIfError - if an illegal (out-of-range) or no input is presented to the object 
DONE bool state - this remembers the result of the most recent call to eval( int )

public
Constructors  -  BooleanFunc( int tableSize = DEFAULT_TABLE_SIZE, bool evalReturnIfError = false )
and a Destructor
bool setTruthTableUsingTrue( int inputsThatProduceTrue[], int arraySize ) ex: returns {3,9} if only 3 and 9 true
bool setTruthTableUsingFalse( int inputsThatProduceFalse[], int arraySize ) for if true is more common
bool eval( int input ) mutator for the state member based on the an input integer, which also returns that evaluated state
    if input invalid evalReturnIfError is assigned to state and returned.
DONE bool getState(){ return state; }
Deep memory methods - 
    A copy constructor, 
    destructor and 
    DONE assignment operator.
optional helper methods


*/
// BooleanFunc class prototype
class BooleanFunc{
public:
    static const int MAX_TABLE_FOR_CLASS = 65536; // 16 binary input lines
    static const int DEFAULT_TABLE_SIZE = 16;
private:
    int tableSize;
    bool *truthTable;
    bool evalReturnIfError;
    bool state;
    
    void allocateCleanArray();
    void deallocateArray();
public:
    BooleanFunc(int tableSize = DEFAULT_TABLE_SIZE, 
        bool evalReturnIfError = false);
    BooleanFunc(const & BooleanFunc bf);
    ~BooleanFunc();
    bool setTruthTableUsingTrue(int inputsThatProduceTrue[], int arraySize);
    bool setTruthTableUsingFalse(int inputsThatProduceFalse[], int arraySize);
    bool eval(int input);
    bool getState(){ return state; }
    
    BooleanFunc & operator=(const BooleanFunc &bf);
};

int main(){
    
    return 0;
}

// BooleanFunc method definitions
BooleanFunc::BooleanFunc(int tableSize, bool evalReturnIfError){
    if(tableSize < log2(MAX_TABLE_FOR_CLASS) && tableSize > 0)
        this->tableSize = tableSize;
    else
        this->tableSize = DEFAULT_TABLE_SIZE;
    this->evalReturnIfError = evalReturnIfError;
}

BooleanFunc::BooleanFunc(const & BooleanFunc bf){
    
}

BooleanFunc::~BooleanFunc(){
    
}

BooleanFunc & BooleanFunc::operator=(const BooleanFunc &bf){
    if(this != &bf){
        this->tableSize = bf.tableSize;
        this->truthTable = bf.truthTable;
        this->evalReturnIfError = bf.evalReturnIfError;
        this->state = bf.state;
    }
    return *this;
}