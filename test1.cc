#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

int main(){
    string thisGen = "*";
    string extremeBit = " ";
    int RULES_SIZE = 8;
    string nextGen;
    int rules[RULES_SIZE];
    
    int newRule = 124;
    for(int i = RULES_SIZE - 1; i >= 0; i--){
        rules[i] = newRule % 2;
        newRule /= 2;
    }
    
    for(int i = 0; i < RULES_SIZE; i++)
        cout << rules[i];
    
    string fullBit = thisGen;
    int bit;
    
    for(int k = 0; k < 10; k++){
        nextGen = "";
        
        for(int i = 0; i < log2(RULES_SIZE) - 1; i++){
            thisGen = thisGen + extremeBit;
            thisGen = extremeBit + thisGen;
        }
        
        for(int i = 0; i < thisGen.length() - log2(RULES_SIZE) + 1; i++){
            bit = 0;
            
            for(int j = 0; j < log2(RULES_SIZE); j++){
                if(thisGen[i + j] != extremeBit[0])
                    bit += pow(2, log2(RULES_SIZE) - 1 - j);
            }
            
            cout << bit << " " << rules[RULES_SIZE - 1 - bit] << endl;
            
            nextGen += (rules[RULES_SIZE - 1 - bit]) ? fullBit : extremeBit;
        }
        
        cout << nextGen;
        thisGen = nextGen;
    }
    return 0;
}
