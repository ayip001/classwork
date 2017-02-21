#include <iostream>
#include <string>
#include <climits>
#include <cmath>
#include <sstream>
#include <ctime>       
#include <stdlib.h>   

using namespace std;

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
    
    int evenFunc[] = { 0, 2, 4, 6, 8, 10, 12, 14 }, inputX;
    short sizeEvenFunc = sizeof(evenFunc) / sizeof(evenFunc[0]);

    int greater9Func[] = { 10, 11, 12, 13, 14, 15 };
    short sizeGreater9Func = sizeof(greater9Func) / sizeof(greater9Func[0]);

    int greater3Func[] = { 0, 1, 2, 3 };
    short sizeGreater3Func = sizeof(greater3Func) / sizeof(greater3Func[0]);

    
    segA.setTruthTableUsingTrue( evenFunc, sizeEvenFunc );
    segB.setTruthTableUsingTrue( greater9Func, sizeGreater9Func );
    segC.setTruthTableUsingFalse( greater3Func, sizeGreater3Func );
    // testing class BooleanFunc
    cout << "before eval()\n";
    cout
        << "\n  A(x) = "
        << segA.getState()
        << "\n  B(x) = "
        << segB.getState()
        << "\n  C(x) = "
        << segC.getState()
        << endl << endl;
    cout << "looping with eval()\n";
    for(inputX = 0; inputX < 10; inputX++ ){
        segA.eval( inputX );
        segB.eval( inputX );
        segC.eval( inputX );
        cout
            << "Input: " << inputX
            << "\n  A(x) = "
            << segA.getState()
            << "\n  B(x) = "
            << segB.getState()
            << "\n  C(x) = "
            << segC.getState()
            << endl << endl;
    }
    segA.eval( inputX );
    
    cout << "Finally testing assignment operator and copy constructors"
        << "\nProgram should exit normally with no runtime error";
        
    segA = segB = segC = segB;
    segA = BooleanFunc(segB);
    return 0;
}

// BooleanFunc method definitions
BooleanFunc::BooleanFunc(int tableSize, bool evalReturnIfError){
    if(tableSize < MAX_TABLE_FOR_CLASS && tableSize > 0)
        this->tableSize = tableSize;
    else
        this->tableSize = DEFAULT_TABLE_SIZE;
    this->evalReturnIfError = evalReturnIfError;
    state = false;
    truthTable = NULL;
    allocateCleanArray();
}

BooleanFunc::BooleanFunc(const BooleanFunc &bf){
    tableSize = bf.tableSize;
    evalReturnIfError = bf.evalReturnIfError;
    state = false;
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
        truthTable[i] = evalReturnIfError;
}

void BooleanFunc::deallocateArray(){
    if(truthTable == NULL)
        return;
    delete[] truthTable;
    truthTable = NULL;
}

bool BooleanFunc::setTruthTableUsingTrue(int inputsThatProduceTrue[], 
    int arraySize){
    for(int i = 0; i < arraySize; i++){
        if(inputsThatProduceTrue[i] >= tableSize)
            return false;
        truthTable[inputsThatProduceTrue[i]] = !evalReturnIfError;
    }
    return true;
}

bool BooleanFunc::setTruthTableUsingFalse(int inputsThatProduceFalse[], 
    int arraySize){
    for(int i = 0; i < arraySize; i++){
        if(inputsThatProduceFalse[i] >= tableSize)
            return false;
        truthTable[inputsThatProduceFalse[i]] = !evalReturnIfError;
    }
    return true;
}

bool BooleanFunc::eval(int input){
    state = truthTable[input];
    return state;
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

/* ------------------------- ACT 1 TEST ---------------------------------------

before eval()

  A(x) = 0
  B(x) = 0
  C(x) = 0

looping with eval()
Input: 0
  A(x) = 1
  B(x) = 0
  C(x) = 0

Input: 1
  A(x) = 0
  B(x) = 0
  C(x) = 0

Input: 2
  A(x) = 1
  B(x) = 0
  C(x) = 0

Input: 3
  A(x) = 0
  B(x) = 0
  C(x) = 0

Input: 4
  A(x) = 1
  B(x) = 0
  C(x) = 1

Input: 5
  A(x) = 0
  B(x) = 0
  C(x) = 1

Input: 6
  A(x) = 1
  B(x) = 0
  C(x) = 1

Input: 7
  A(x) = 0
  B(x) = 0
  C(x) = 1

Input: 8
  A(x) = 1
  B(x) = 0
  C(x) = 1

Input: 9
  A(x) = 0
  B(x) = 0
  C(x) = 1

Finally testing assignment operator and copy constructors
Program should exit normally with no runtime error

Process exited with code: 0

---------------------------------------------------------------------------- */