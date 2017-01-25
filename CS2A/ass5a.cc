#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// method prototypes
char getKeyLetter();
string getString();
string maskLetter(string theString, char keyLetter);
string removeLetter(string theString, char keyLetter);
int countKey(string theString, char keyLetter);

// main function
int main(){
    // variables
    char keyLetter;
    string theString;
    int numKey;
    
    // input methods
    keyLetter = getKeyLetter();
    theString = getString();
    
    // output + processing methods
    cout << "\nString with '" << keyLetter << "' masked:\n" 
        << maskLetter(theString, keyLetter);
    cout << "\n\n# " << keyLetter << "s :" << countKey(theString, keyLetter);
    cout << "\n\nStrings with '" << keyLetter << "' removed:\n"
        << removeLetter(theString, keyLetter);
    
    return 0;
}

char getKeyLetter(){
    string prompt, input;
    prompt = "Please enter a SINGLE letter to act as key: ";
    // if there's user error it loops until the input is legal
    bool error = true;
    while(error){
        cout << prompt;
        getline(cin, input);
        // if the input is a single character, exit error checking loop
        if(input.length() == 1)
            error = false;
    }
    
    // input[0] first letter of the string input, which is a char
    return input[0];
}

string getString(){
    string prompt, input;
    prompt = "Please enter a phrase or sentence >= 4 letters:\n";
    // if there's user error it loops until the input is legal
    bool error = true;
    while(error){
        cout << prompt;
        getline(cin, input);
        // if the input has at least 4 letters, exit error checking loop
        if(input.length() >= 4)
            error = false;
    }
    
    return input;
}

string maskLetter(string theString, char keyLetter){
    // the character used to mask
    const char MASK = '-';
    // this method builds a newString
    string newString = "";
    
    for(int i = 0; i < theString.length(); i++){
        if(theString[i] == keyLetter)
            newString += MASK;
        else
            newString += theString[i];
    }
    
    return newString;
}

string removeLetter(string theString, char keyLetter){
    // this method builds a newString
    string newString = "";
    
    for(int i = 0; i < theString.length(); i++){
        if(theString[i] != keyLetter)
            newString += theString[i];
    }
    
    return newString;
}

int countKey(string theString, char keyLetter){
    // number of keys accumulator
    int numKey = 0;
    
    for(int i = 0; i < theString.length(); i++){
        if(theString[i] == keyLetter)
            numKey++;
    }
    
    return numKey;
}

/* --------------------- RUN 1 ----------------------------------------------

Please enter a SINGLE letter to act as key: ayy lmao
Please enter a SINGLE letter to act as key: 
Please enter a SINGLE letter to act as key: a
Please enter a phrase or sentence >= 4 letters:
123                                        
Please enter a phrase or sentence >= 4 letters:
aaaaaAAAAAaaaaahahahahaha!!!!!      

String with 'a' masked:
-----AAAAA-----h-h-h-h-h-!!!!!

# as :15

Strings with 'a' removed:
AAAAAhhhhh!!!!!

Process exited with code: 0

------------------------ END OF RUN 1 ------------------------------------ */

/* --------------------- RUN 2 ----------------------------------------------

Please enter a SINGLE letter to act as key: ! 
Please enter a phrase or sentence >= 4 letters:
!@#$%^&*()

String with '!' masked:
-@#$%^&*()

# !s :1

Strings with '!' removed:
@#$%^&*()

Process exited with code: 0

------------------------ END OF RUN 2 ------------------------------------ */

/* --------------------- RUN 3 ----------------------------------------------

Please enter a SINGLE letter to act as key: A
Please enter a phrase or sentence >= 4 letters:
eh~~

String with 'A' masked:
eh~~

# As :0

Strings with 'A' removed:
eh~~

Process exited with code: 0

------------------------ END OF RUN 3 ------------------------------------ */

/* --------------------- RUN 4 ----------------------------------------------

Please enter a SINGLE letter to act as key: -
Please enter a phrase or sentence >= 4 letters:
----

String with '-' masked:
----

# -s :4

Strings with '-' removed:


Process exited with code: 0

------------------------ END OF RUN 4 ------------------------------------ */