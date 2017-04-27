#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

using namespace std;

// constants
const int MIN_BET = 1, MAX_BET = 50;
const string BAR = "BAR", CHERRIES = "cherries", SPACE = "(space)", SEVEN = "7";
const int BAR_WEIGHT = 40, CHERRIES_WEIGHT = 30, SPACE_WEIGHT = 5, 
    SEVEN_WEIGHT = 25; 
const int REWARD_TRIPLE_SEVEN = 100, REWARD_TRIPLE_BAR = 50, 
    REWARD_TRIPLE_CHERRIES = 30, REWARD_DOUBLE_CHERRIES = 15,
    REWARD_SINGLE_CHERRIES = 5, REWARD_NONE = 0;

// class prototype
class TripleString{
private:
    string string1, string2, string3;
    
    // private helper method
    bool validString(string str);
    
public:
    static const int MAX_LEN = 20;
    
    // default constructor
    TripleString();
    
    // mutators and accessors
    bool setString1(string str);
    bool setString2(string str);
    bool setString3(string str);
    string getString1();
    string getString2();
    string getString3();
};

// method prototypes
int getBet();
TripleString pull();
string randString();
int getPayMultiplier(TripleString thePull);
void display(TripleString thePull, int winnings);

// main loop
int main(){
    int bet;
    TripleString thePull;
    
    while(true){
        bet = getBet();
        if(bet == 0)
            break;
        
        thePull = pull();
        
        display(thePull, bet * getPayMultiplier(thePull));
    }
    
    return 0;
}

// methods defintion
int getBet(){
    string prompt, input;
    int bet;
    prompt = "How much would you like to bet (" + to_string(MIN_BET) + "-" + 
        to_string(MAX_BET) + ") or 0 to quit? ";
    // if there's user error it loops until the input is legal
    bool error = true;
    while(error){
        cout << prompt;
        getline(cin, input);
        if(istringstream(input) >> bet && ((bet >= MIN_BET && bet <= MAX_BET) 
            || bet == 0))
            error = false;
    }
    
    return bet;
}

TripleString pull(){
    TripleString pull;
    
    pull.setString1(randString());
    pull.setString2(randString());
    pull.setString3(randString());
    return pull;
}

string randString(){
    int wheel = rand() % (BAR_WEIGHT + CHERRIES_WEIGHT + SPACE_WEIGHT +
    SEVEN_WEIGHT);
    
    if(wheel < BAR_WEIGHT)
        return BAR;
    if(wheel < BAR_WEIGHT + CHERRIES_WEIGHT)
        return CHERRIES;
    if(wheel < BAR_WEIGHT + CHERRIES_WEIGHT + SPACE_WEIGHT)
        return SPACE;
    return SEVEN;
}

int getPayMultiplier(TripleString thePull){
    if(thePull.getString1() == SEVEN && thePull.getString2() == SEVEN && 
        thePull.getString3() == SEVEN)
        return REWARD_TRIPLE_SEVEN;
    if(thePull.getString1() == BAR && thePull.getString2() == BAR && 
        thePull.getString3() == BAR)
        return REWARD_TRIPLE_BAR;
    if(thePull.getString1() == CHERRIES && thePull.getString2() == CHERRIES && 
        thePull.getString3() == CHERRIES)
        return REWARD_TRIPLE_CHERRIES;
    if(thePull.getString1() == CHERRIES && thePull.getString2() == CHERRIES)
        return REWARD_DOUBLE_CHERRIES;
    if(thePull.getString1() == CHERRIES)
        return REWARD_SINGLE_CHERRIES;
    return REWARD_NONE;
}

void display(TripleString thePull, int winnings){
    cout << "whirrrrrr.... and your pull is...\n " << thePull.getString1()
        << "  " << thePull.getString2() << "  " << thePull.getString3();
    cout << (winnings == REWARD_NONE ? "\nsorry, you lose.\n\n" : 
        "\ncongratulations, you win: " + to_string(winnings) + "\n\n");
}

// class methods definition
bool TripleString::validString(string str){
    return str.length() <= MAX_LEN;
}

TripleString::TripleString(){
    string1 = "";
    string2 = "";
    string3 = "";
}

bool TripleString::setString1(string str){
    if(!validString(str))
        return false;
    string1 = str;
    return true;
}

bool TripleString::setString2(string str){
    if(!validString(str))
        return false;
    string2 = str;
    return true;
}

bool TripleString::setString3(string str){
    if(!validString(str))
        return false;
    string3 = str;
    return true;
}

string TripleString::getString1(){
    return string1;
}

string TripleString::getString2(){
    return string2;
}

string TripleString::getString3(){
    return string3;
}

/*-------------------------- RUN 1 ------------------------------------------

How much would you like to bet (1-50) or 0 to quit? hahaha
How much would you like to bet (1-50) or 0 to quit? -1
How much would you like to bet (1-50) or 0 to quit? 51
How much would you like to bet (1-50) or 0 to quit? 1
whirrrrrr.... and your pull is...
 7  7  7
congratulations, you win: 100

How much would you like to bet (1-50) or 0 to quit? 2
whirrrrrr.... and your pull is...
 BAR  7  BAR
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 3
whirrrrrr.... and your pull is...
 7  7  cherries
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 4
whirrrrrr.... and your pull is...
 BAR  cherries  BAR
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 5
whirrrrrr.... and your pull is...
 7  cherries  cherries
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 6
whirrrrrr.... and your pull is...
 BAR  cherries  BAR
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 7
whirrrrrr.... and your pull is...
 (space)  BAR  BAR
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 8
whirrrrrr.... and your pull is...
 cherries  cherries  BAR
congratulations, you win: 120

How much would you like to bet (1-50) or 0 to quit? 9
whirrrrrr.... and your pull is...
 7  BAR  cherries
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 10
whirrrrrr.... and your pull is...
 BAR  cherries  BAR
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 11
whirrrrrr.... and your pull is...
 BAR  BAR  BAR
congratulations, you win: 550

How much would you like to bet (1-50) or 0 to quit? 12
whirrrrrr.... and your pull is...
 cherries  cherries  cherries
congratulations, you win: 360

How much would you like to bet (1-50) or 0 to quit? 13
whirrrrrr.... and your pull is...
 7  cherries  BAR
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 14
whirrrrrr.... and your pull is...
 cherries  BAR  (space)
congratulations, you win: 70

How much would you like to bet (1-50) or 0 to quit? 15
whirrrrrr.... and your pull is...
 BAR  BAR  7
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 16
whirrrrrr.... and your pull is...
 BAR  7  BAR
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 17
whirrrrrr.... and your pull is...
 BAR  (space)  BAR
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 18
whirrrrrr.... and your pull is...
 BAR  7  7
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 19
whirrrrrr.... and your pull is...
 cherries  (space)  cherries
congratulations, you win: 95

How much would you like to bet (1-50) or 0 to quit? 20
whirrrrrr.... and your pull is...
 (space)  7  7
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 21
whirrrrrr.... and your pull is...
 BAR  BAR  7
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 22
whirrrrrr.... and your pull is...
 BAR  BAR  BAR
congratulations, you win: 1100

How much would you like to bet (1-50) or 0 to quit? 23
whirrrrrr.... and your pull is...
 cherries  BAR  BAR
congratulations, you win: 115

How much would you like to bet (1-50) or 0 to quit? 24
whirrrrrr.... and your pull is...
 cherries  BAR  7
congratulations, you win: 120

How much would you like to bet (1-50) or 0 to quit? 25
whirrrrrr.... and your pull is...
 7  cherries  BAR
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 26
whirrrrrr.... and your pull is...
 cherries  BAR  cherries
congratulations, you win: 130

How much would you like to bet (1-50) or 0 to quit? 27
whirrrrrr.... and your pull is...
 cherries  cherries  7
congratulations, you win: 405

How much would you like to bet (1-50) or 0 to quit? 28
whirrrrrr.... and your pull is...
 BAR  7  7
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 29
whirrrrrr.... and your pull is...
 7  7  BAR
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 30
whirrrrrr.... and your pull is...
 cherries  cherries  7
congratulations, you win: 450

How much would you like to bet (1-50) or 0 to quit? 31
whirrrrrr.... and your pull is...
 BAR  cherries  7
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 32
whirrrrrr.... and your pull is...
 cherries  BAR  BAR
congratulations, you win: 160

How much would you like to bet (1-50) or 0 to quit? 33
whirrrrrr.... and your pull is...
 BAR  7  7
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 34
whirrrrrr.... and your pull is...
 BAR  7  (space)
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 35
whirrrrrr.... and your pull is...
 BAR  7  cherries
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 36
whirrrrrr.... and your pull is...
 BAR  7  BAR
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 37
whirrrrrr.... and your pull is...
 BAR  7  cherries
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 38
whirrrrrr.... and your pull is...
 cherries  BAR  7
congratulations, you win: 190

How much would you like to bet (1-50) or 0 to quit? 39
whirrrrrr.... and your pull is...
 7  cherries  cherries
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 40
whirrrrrr.... and your pull is...
 7  cherries  BAR
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 41
whirrrrrr.... and your pull is...
 cherries  BAR  BAR
congratulations, you win: 205

How much would you like to bet (1-50) or 0 to quit? 42
whirrrrrr.... and your pull is...
 BAR  7  (space)
sorry, you lose.

How much would you like to bet (1-50) or 0 to quit? 0


Process exited with code: 0

-------------------------------------------------------------------------- */