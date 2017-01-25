#include <iostream>

using namespace std;

int main(){
    
    int studID = 20267919, numLet = 3, intResult;
    double doubleResult;
    
    cout << "My family name is Yip\nMy student ID is " << studID << endl
        << "The number of characters in my last name is " << numLet << endl
        << endl;
    
    intResult = studID % 2;
    cout << "Expression #1 ------------ : " << intResult << endl << endl;
    
    intResult = studID % numLet;
    cout << "Expression #2 ------------ : " << intResult << endl << endl;
    
    doubleResult = ((double) studID) / numLet;
    cout << "Expression #3 ------------ : " << doubleResult << endl << endl;
    
    intResult = 1 + 2 + numLet;
    cout << "Expression #4 ------------ : " << intResult << endl << endl;
    
    doubleResult = ((double) 100000) / (99 + ((double) (studID - 54321)) / 
        ((numLet + 30) * (numLet + 30)));
    cout << "Expression #5 ------------ : " << doubleResult << endl << endl;
    
    return 0;
}

/* ------------------------------RUN-------------------------------------------

My family name is Yip
My student ID is 20267919
The number of characters in my last name is 3

Expression #1 ------------ : 1

Expression #2 ------------ : 0

Expression #3 ------------ : 6.75597e+06

Expression #4 ------------ : 6

Expression #5 ------------ : 5.35888



Process exited with code: 0

---------------------------------------------------------------------------- */