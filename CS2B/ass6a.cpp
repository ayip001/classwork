#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

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
    BooleanFunc(const BooleanFunc &bf);
    ~BooleanFunc();
    bool setTruthTableUsingTrue(int inputsThatProduceTrue[], int arraySize);
    bool setTruthTableUsingFalse(int inputsThatProduceFalse[], int arraySize);
    bool eval(int input);
    bool getState(){ return state; }
    
    BooleanFunc & operator=(const BooleanFunc &bf);
};

// MultiSegmentLogic class prototype
class MultiSegmentLogic{
protected:
    int numSegs;
    BooleanFunc *segs;
    
private:
    void allocateCleanArray();
    void deallocateArray();

public:
    MultiSegmentLogic(int numSegs = 0); 
    MultiSegmentLogic(const MultiSegmentLogic &msl);
    ~MultiSegmentLogic();
    bool setNumSegs(int numSegs); // numSegs >= 0
    bool setSegment(int segNum, BooleanFunc &funcForThisSeg);
    void eval(int input);
    
    MultiSegmentLogic & operator=(const MultiSegmentLogic &msl);
};

// SevenSegmentLogic class prototype
class SevenSegmentLogic : public MultiSegmentLogic{
public:
    SevenSegmentLogic() : MultiSegmentLogic(7){ init(); }
    bool getValOfSeg(int seg);
    
private:
    void init();
};

int main(){
    int inputX, k;
    SevenSegmentLogic my7Seg;
    SevenSegmentLogic myCopy(my7Seg);
    my7Seg = myCopy = myCopy = SevenSegmentLogic();
    
    cout << "Tested = operator and copy constructor. No error. Carry on\n\n";
    
    cout << "[ # ]| a | b | c | d | e | f | g |\n"
        << "----------------------------------";
    for(inputX = 0; inputX < 16; inputX++){
        myCopy.eval(inputX);
        cout << "\n[ " << inputX << ((inputX >= 10) ? "" : " ") << "]| ";
        for(k = 0; k < 7; k++)
            cout << myCopy.getValOfSeg(k) << " | ";
        cout << endl;
    }
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
    allocateCleanArray();
    for(int i = 0; i < arraySize; i++)
        if(inputsThatProduceTrue[i] >= 0 && 
            inputsThatProduceTrue[i] < tableSize)
            truthTable[inputsThatProduceTrue[i]] = !evalReturnIfError;
    return true;
}

bool BooleanFunc::setTruthTableUsingFalse(int inputsThatProduceFalse[], 
    int arraySize){
    allocateCleanArray();
    for(int i = 0; i < arraySize; i++)
        if(inputsThatProduceFalse[i] >= 0 && 
            inputsThatProduceFalse[i] < tableSize)
            truthTable[inputsThatProduceFalse[i]] = !evalReturnIfError;
    return true;
}

bool BooleanFunc::eval(int input){
    state = evalReturnIfError;
    if(input >= 0 && input < tableSize)
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

// MultiSegmentLogic method definitions
MultiSegmentLogic::MultiSegmentLogic(int numSegs){
    segs = NULL;
    if(!setNumSegs(numSegs))
        setNumSegs(0);
}

MultiSegmentLogic::MultiSegmentLogic(const MultiSegmentLogic &msl){
    segs = NULL;
    setNumSegs(msl.numSegs);
    for(int i = 0; i < this->numSegs; i++)
        this->segs[i] = msl.segs[i];
}

MultiSegmentLogic::~MultiSegmentLogic(){
    deallocateArray();
}

void MultiSegmentLogic::allocateCleanArray(){
    if(segs != NULL)
        deallocateArray();
    segs = new BooleanFunc [numSegs];
    for(int i = 0; i < numSegs; i++)
        segs[i] = BooleanFunc();
}

void MultiSegmentLogic::deallocateArray(){
    if(segs == NULL)
        return;
    delete[] segs;
    segs = NULL;
}

bool MultiSegmentLogic::setNumSegs(int numSegs){
    if(numSegs >= 0){
        deallocateArray();
        this->numSegs = numSegs;
        allocateCleanArray();
        return true;
    }
    return false;
}

bool MultiSegmentLogic::setSegment(int segNum, BooleanFunc &funcForThisSeg){
    if(segNum < 0 || segNum >= numSegs)
        return false;
    segs[segNum] = funcForThisSeg;
    return true;
}

void MultiSegmentLogic::eval(int input){
    for(int i = 0; i < numSegs; i++)
        segs[i].eval(input);
}

MultiSegmentLogic & MultiSegmentLogic::operator=(const MultiSegmentLogic &msl){
    if(this != &msl){
        this->setNumSegs(msl.numSegs);
        for(int i = 0; i < this->numSegs; i++)
            this->segs[i] = msl.segs[i];
    }
    return *this;
}

// SevenSegmentLogic method definitions
bool SevenSegmentLogic::getValOfSeg(int seg){
    if(seg < 0 || seg >= 16)
        return false;
    return segs[seg].getState();
}

void SevenSegmentLogic::init(){
    BooleanFunc bf = BooleanFunc(16, true);
    // seg a
    int aFunc[] = {1, 4, 11, 13};
    bf.setTruthTableUsingFalse(aFunc, 4);
    setSegment(0, bf);
    // seg b
    int bFunc[] = {5, 6, 11, 12, 14, 15};
    bf.setTruthTableUsingFalse(bFunc, 6);
    setSegment(1, bf);
    // seg c
    int cFunc[] = {2, 12, 14, 15};
    bf.setTruthTableUsingFalse(cFunc, 4);
    setSegment(2, bf);
    // seg d
    int dFunc[] = {1, 4, 7, 9, 10, 15};
    bf.setTruthTableUsingFalse(dFunc, 6);
    setSegment(3, bf);
    // seg e
    int eFunc[] = {1, 3, 4, 5, 7, 9};
    bf.setTruthTableUsingFalse(eFunc, 6);
    setSegment(4, bf);
    // seg f
    int fFunc[] = {1, 2, 3, 7, 13};
    bf.setTruthTableUsingFalse(fFunc, 5);
    setSegment(5, bf);
    // seg g
    int gFunc[] = {0, 1, 7, 12};
    bf.setTruthTableUsingFalse(gFunc, 4);
    setSegment(6, bf);
}

/* ------------------------- Act 3 Test ---------------------------------------

Tested = operator and copy constructor. No error. Carry on

[ # ]| a | b | c | d | e | f | g |
----------------------------------
[ 0 ]| 1 | 1 | 1 | 1 | 1 | 1 | 0 | 

[ 1 ]| 0 | 1 | 1 | 0 | 0 | 0 | 0 | 

[ 2 ]| 1 | 1 | 0 | 1 | 1 | 0 | 1 | 

[ 3 ]| 1 | 1 | 1 | 1 | 0 | 0 | 1 | 

[ 4 ]| 0 | 1 | 1 | 0 | 0 | 1 | 1 | 

[ 5 ]| 1 | 0 | 1 | 1 | 0 | 1 | 1 | 

[ 6 ]| 1 | 0 | 1 | 1 | 1 | 1 | 1 | 

[ 7 ]| 1 | 1 | 1 | 0 | 0 | 0 | 0 | 

[ 8 ]| 1 | 1 | 1 | 1 | 1 | 1 | 1 | 

[ 9 ]| 1 | 1 | 1 | 0 | 0 | 1 | 1 | 

[ 10]| 1 | 1 | 1 | 0 | 1 | 1 | 1 | 

[ 11]| 0 | 0 | 1 | 1 | 1 | 1 | 1 | 

[ 12]| 1 | 0 | 0 | 1 | 1 | 1 | 0 | 

[ 13]| 0 | 1 | 1 | 1 | 1 | 0 | 1 | 

[ 14]| 1 | 0 | 0 | 1 | 1 | 1 | 1 | 

[ 15]| 1 | 0 | 0 | 0 | 1 | 1 | 1 | 


Process exited with code: 0

---------------------------------------------------------------------------- */