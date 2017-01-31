#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

// Automation class prototype
class Automaton{
private:
    static const int RULES_SIZE = 32; // can only be 2^n, n >= 3 odd number
    
    bool rules[RULES_SIZE];
    string thisGen;
    string extremeBit; // bit, "*" or " ", implied everywhere "outside"
    string fullBit;
    int displayWidth;  // an odd number so it can be perfectly centered

public:
    static const int MAX_DISPLAY_WIDTH = 121;
    static const int DEFAULT_DISPLAY_WIDTH = 79;

    Automaton(int rule);
    string toStringCurrentGen();
    bool setRule(int newRule);      // change rule set
    void resetFirstGen();
    bool setDisplayWidth(int width = DEFAULT_DISPLAY_WIDTH);
    void propagateNewGeneration();
    
    static int getRulesSize(){return RULES_SIZE;}
};

// Main client
int main(){
    int rule;
    string input;
    bool error = true;
    while(error){
        cout << "Enter Rule (0 - " << pow(2, Automaton::getRulesSize()) - 1 
            << "): ";
        getline(cin, input);
        if(istringstream(input) >> rule && (rule > 0 && 
            rule < pow(2, Automaton::getRulesSize())))
            error = false;
    }
    
    Automaton myAut = Automaton(rule);
    
    cout << "    start\n";
    for(int i = 0; i < 100; i++){
        cout << myAut.toStringCurrentGen() << endl;
        myAut.propagateNewGeneration();
    }
    cout << "    end";
    return 0;
}

// Automation class definition
Automaton::Automaton(int rule){
    resetFirstGen();
    setDisplayWidth();
    setRule(rule);
}

string Automaton::toStringCurrentGen(){
    if(thisGen.length() < displayWidth){
        string returnString = thisGen;
        for(int i = 0; i < (displayWidth - thisGen.length()) / 2; i++){
            returnString = extremeBit + returnString;
            returnString = returnString + extremeBit;
        }
        return returnString;
    }
    return thisGen.substr((thisGen.length() - displayWidth) / 2, displayWidth);
}

bool Automaton::setRule(int newRule){
    if(newRule < 0 || newRule > pow(2, RULES_SIZE) - 1)
        return false;
    
    for(int i = RULES_SIZE - 1; i >= 0; i--){
        rules[i] = newRule % 2;
        newRule /= 2;
    }
    return true;
}

void Automaton::resetFirstGen(){
    thisGen = "*";
    extremeBit = " ";
    fullBit = thisGen;
}

bool Automaton::setDisplayWidth(int width){
    if(width < 1 || width > MAX_DISPLAY_WIDTH)
        return false;
    if(width % 2 == 0)
        return false;
        
    displayWidth = width;
    return true;
}

void Automaton::propagateNewGeneration(){
    string nextGen;
    int bit;
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
        
        nextGen += (rules[RULES_SIZE - 1 - bit]) ? fullBit : extremeBit;
    }
    
    thisGen = nextGen;
}

/* --------------------------Rule --------------------------------------------



---------------------------------------------------------------------------- */