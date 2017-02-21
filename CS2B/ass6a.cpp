#include <iostream>
#include <string>
#include <climits>
#include <cmath>
#include <sstream>
#include <ctime>       
#include <stdlib.h>   

using namespace std;
// DELETE THIS COMMENT inconsistent runtime error occurs if I use copy constructor or use =
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
DONE Constructors  -  BooleanFunc( int tableSize = DEFAULT_TABLE_SIZE, bool evalReturnIfError = false )
and a Destructor
DONE bool setTruthTableUsingTrue( int inputsThatProduceTrue[], int arraySize ) ex: returns {3,9} if only 3 and 9 true
DONE bool setTruthTableUsingFalse( int inputsThatProduceFalse[], int arraySize ) for if true is more common
bool eval( int input ) mutator for the state member based on the an input integer, which also returns that evaluated state
    if input invalid evalReturnIfError is assigned to state and returned.
DONE bool getState(){ return state; }
DONE Deep memory methods - 
    DONE A copy constructor, 
    DONE destructor 
    DONE assignment operator.
optional helper methods


*/
// BooleanFunc class prototype
class BooleanFunc{
public:
    static const int MAX_TABLE_FOR_CLASS = 65536; // 16 binary input lines
    static const int DEFAULT_TABLE_SIZE = 16;
public:
    int tableSize;
    bool *truthTable;
    bool evalReturnIfError;
    bool state;
    
    void allocateCleanArray();
    void deallocateArray();
public:
    BooleanFunc(int tableSize = DEFAULT_TABLE_SIZE, 
        bool evalReturnIfError = false);
    BooleanFunc(const BooleanFunc &bf);
    ~BooleanFunc();
    bool setTruthTableUsingTrue(int inputsThatProduceTrue[], int arraySize);
    bool setTruthTableUsingFalse(int inputsThatProduceFalse[], int arraySize);
    bool eval(int input);
    bool getState(){ return state; }
    
    BooleanFunc & operator=(const BooleanFunc &bf);
};

int main(){
    BooleanFunc segA, segB( 13 ), segC( 100, true );
    
    for(int i = 0; i < 100; i++)
        cout << segC.truthTable[1];
    
    int evenFunc[] = { 0, 2, 4, 6, 8, 10, 12, 14 }, inputX;
    short sizeEvenFunc = sizeof(evenFunc) / sizeof(evenFunc[0]);

    int greater9Func[] = { 10, 11, 12, 13, 14, 15 };
    short sizeGreater9Func = sizeof(greater9Func) / sizeof(greater9Func[0]);

    int greater3Func[] = { 0, 1, 2, 3 };
    short sizeGreater3Func = sizeof(greater3Func) / sizeof(greater3Func[0]);

    // testing class BooleanFunc
    return 0;
}

// BooleanFunc method definitions
BooleanFunc::BooleanFunc(int tableSize, bool evalReturnIfError){
    if(tableSize < MAX_TABLE_FOR_CLASS && tableSize > 0)
        this->tableSize = tableSize;
    else
        this->tableSize = DEFAULT_TABLE_SIZE;
    this->evalReturnIfError = evalReturnIfError;
    truthTable = NULL;
    allocateCleanArray();
}

BooleanFunc::BooleanFunc(const BooleanFunc &bf){
    tableSize = bf.tableSize;
    evalReturnIfError = bf.evalReturnIfError;
    truthTable = NULL;
    allocateCleanArray();
    for(int i = 0; i < this->tableSize; i++)
        this->truthTable[i] = bf.truthTable[i];
}

BooleanFunc::~BooleanFunc(){
    deallocateArray();
}

void BooleanFunc::allocateCleanArray(){
    if(truthTable != NULL)
        deallocateArray();
    
    truthTable = new bool [tableSize];
    for(int i = 0; i < tableSize; i++)
        truthTable[i] = new bool(evalReturnIfError);
}

void BooleanFunc::deallocateArray(){
    if(truthTable == NULL)
        return;
    delete[] truthTable;
    truthTable = NULL;
}

bool BooleanFunc::setTruthTableUsingTrue(int inputsThatProduceTrue[], 
    int arraySize){
    for(int i = 0; i < arraySize; i++)
        truthTable[inputsThatProduceTrue[i] - 1] = !evalReturnIfError;
    
    return true;
}

bool BooleanFunc::setTruthTableUsingFalse(int inputsThatProduceFalse[], 
    int arraySize){
    for(int i = 0; i < arraySize; i++)
        truthTable[inputsThatProduceFalse[i] - 1] = !evalReturnIfError;
        
    return true;
}

BooleanFunc & BooleanFunc::operator=(const BooleanFunc &bf){
    if(this != &bf){
        this->tableSize = bf.tableSize;
        this->allocateCleanArray();
        for(int i = 0; i < this->tableSize; i++)
            this->truthTable[i] = bf.truthTable[i];
        this->evalReturnIfError = bf.evalReturnIfError;
        this->state = bf.state;
    }
    return *this;
}