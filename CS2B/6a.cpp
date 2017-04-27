#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;
// todo fix: BooleanFunc state should = evalReturnIfError when instantiated

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

// SevenSegmentImage class prototype
class SevenSegmentImage{
public:
    static const int MIN_HEIGHT = 5;
    static const int MIN_WIDTH = 5;
    static const int MAX_HEIGHT = 65;
    static const int MAX_WIDTH = 41;
    static const string DRAW_CHAR;
    static const string BLANK_CHAR;

private:
    bool **data;
    int topRow, midRow, bottomRow, leftCol, rightCol;

public:
    SevenSegmentImage(int width = MIN_WIDTH, int height = MIN_HEIGHT);
    ~SevenSegmentImage(){ deallocateArray(); }
    void clearImage();
    bool turnOnCellsForSegment(char segment);
    bool setSize(int width, int height);
    void display();

    SevenSegmentImage(const SevenSegmentImage &tdi);
    const SevenSegmentImage &operator=(const SevenSegmentImage &rhs);

private:
    static bool validateSize(int width, int height);
    void allocateCleanArray();
    void deallocateArray();

    void drawHorizontal(int row);
    void drawVertical(int col, int startRow, int stopRow);
};
const string SevenSegmentImage::DRAW_CHAR = "*";
const string SevenSegmentImage::BLANK_CHAR = " ";

// SevenSegmentDisplay class prototype
class SevenSegmentDisplay{
private:
    SevenSegmentImage theImage;
    SevenSegmentLogic theDisplay;

public:
    SevenSegmentDisplay(
        int width = SevenSegmentImage::MIN_WIDTH,
        int height = SevenSegmentImage::MIN_HEIGHT
    );
    bool setSize(int width, int height);
    void loadConsoleImage();
    void consoleDisplay();
    void eval(int input);
};


int main(){
    SevenSegmentDisplay my7SegForCon(15, 13);
    
    my7SegForCon.setSize(5, 7);
    my7SegForCon.setSize(6, 40);
    for (int j = 0; j < 16; j++){
        cout << j << " :";
        my7SegForCon.eval(j);
        my7SegForCon.loadConsoleImage();
        my7SegForCon.consoleDisplay();
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

// SevenSegmentImage method definitions
SevenSegmentImage::SevenSegmentImage(int width, int height){
    data = NULL;
    if(!setSize(width, height))
        setSize(MIN_WIDTH, MIN_HEIGHT);
}

SevenSegmentImage::SevenSegmentImage(const SevenSegmentImage &tdi){
    data = NULL;
    setSize(tdi.rightCol, tdi.bottomRow);
    for(int row = 0; row < tdi.bottomRow; row++)
        for(int col = 0; col < tdi.rightCol; col++)
            data[row][col] = tdi.data[row][col];
}

void SevenSegmentImage::clearImage(){
    for (int row = 0; row < bottomRow; row++)
        for (int col = 0; col < rightCol; col++)
            data[row][col] = false;
}

bool SevenSegmentImage::turnOnCellsForSegment(char segment){
    switch(segment){
        case 'a': 
            drawHorizontal(topRow);
            break;
        case 'b': 
            drawVertical(rightCol, topRow, midRow);
            break;
        case 'c': 
            drawVertical(rightCol, midRow, bottomRow);
            break;
        case 'd': 
            drawHorizontal(bottomRow);
            break;
        case 'e': 
            drawVertical(leftCol, midRow, bottomRow);
            break;
        case 'f': 
            drawVertical(leftCol, topRow, midRow);
            break;
        case 'g': 
            drawHorizontal(midRow);
            break;
        default:
            return false;
    }
    return true;
}

bool SevenSegmentImage::setSize(int width, int height){
    if(!validateSize(width, height))
        return false;
    deallocateArray();
    topRow = 1;
    midRow = (height + 1) / 2;
    bottomRow = height;
    leftCol = 1;
    rightCol = width;
    allocateCleanArray();
    return true;
}

void SevenSegmentImage::display(){
    for(int row = 0; row < bottomRow; row++){
        cout << endl;
        for(int col = 0; col < rightCol; col++)
            cout << (data[row][col] ? DRAW_CHAR : BLANK_CHAR);
    }
}

const SevenSegmentImage & SevenSegmentImage::operator=
    (const SevenSegmentImage &rhs){
    if(this != &rhs){
        this->setSize(rhs.rightCol, rhs.bottomRow);
        for(int row = 0; row < rhs.bottomRow; row++)
            for(int col = 0; col < rhs.rightCol; col++)
                this->data[row][col] = rhs.data[row][col];
    }
    return *this;
}

bool SevenSegmentImage::validateSize(int width, int height){
    if(width < MIN_WIDTH || width > MAX_WIDTH ||
        height < MIN_HEIGHT || height > MAX_HEIGHT || height % 2 == 0)
        return false;
    return true;
}

void SevenSegmentImage::allocateCleanArray(){
    if (data != NULL)
        deallocateArray();

    data = new bool*[bottomRow];
    for (int row = 0; row < bottomRow; row++)
       data[row] = new bool[rightCol];

    for (int row = 0; row < bottomRow; row++)
        for (int col = 0; col < rightCol; col++)
            data[row][col] = false;
}

void SevenSegmentImage::deallocateArray(){
    if (data == NULL)
        return;

    for (int row = 0; row < bottomRow; row++)
        delete[] data[row];
    delete[] data;
    data = NULL;
}

void SevenSegmentImage::drawHorizontal(int row){
    for(int col = 0; col < rightCol; col++)
        data[row - 1][col] = true;
}

void SevenSegmentImage::drawVertical(int col, int startRow, int stopRow){
    for(int row = startRow; row <= stopRow; row++)
        data[row - 1][col - 1] = true;
}

// SevenSegmentDisplay method definitions
SevenSegmentDisplay::SevenSegmentDisplay(int width, int height){
    if(!setSize(width, height))
        setSize(SevenSegmentImage::MIN_WIDTH, SevenSegmentImage::MIN_HEIGHT);
}

bool SevenSegmentDisplay::setSize(int width, int height){
    return theImage.setSize(width, height);
}

void SevenSegmentDisplay::loadConsoleImage(){
    theImage.clearImage();
    for(int seg = 'a'; seg <= 'g'; seg++)
        if(theDisplay.getValOfSeg(seg - 'a'))
            theImage.turnOnCellsForSegment(seg);
}

void SevenSegmentDisplay::consoleDisplay(){
    theImage.display();
}

void SevenSegmentDisplay::eval(int input){
    theDisplay.eval(input);
}

/* ----------------------------- TEST -----------------------------------------

0 :
*****
*   *
*   *
*   *
*   *
*   *
*****
1 :
    *
    *
    *
    *
    *
    *
    *
2 :
*****
    *
    *
*****
*    
*    
*****
3 :
*****
    *
    *
*****
    *
    *
*****
4 :
*   *
*   *
*   *
*****
    *
    *
    *
5 :
*****
*    
*    
*****
    *
    *
*****
6 :
*****
*    
*    
*****
*   *
*   *
*****
7 :
*****
    *
    *
    *
    *
    *
    *
8 :
*****
*   *
*   *
*****
*   *
*   *
*****
9 :
*****
*   *
*   *
*****
    *
    *
    *
10 :
*****
*   *
*   *
*****
*   *
*   *
*   *
11 :
*    
*    
*    
*****
*   *
*   *
*****
12 :
*****
*    
*    
*    
*    
*    
*****
13 :
    *
    *
    *
*****
*   *
*   *
*****
14 :
*****
*    
*    
*****
*    
*    
*****
15 :
*****
*    
*****
*    
*    
*    


Process exited with code: 0

---------------------------------------------------------------------------- */