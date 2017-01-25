#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

// Card class prototype
class Card{
public:
    enum Suit {
        clubs,
        diamonds,
        hearts,
        spades
    };

private:
    char value;
    Suit suit;
    bool errorFlag;
    
public:
    Card(char value = 'A', Suit suit = spades);
    string toString();
    bool set(char value, Suit suit);
    bool equals(Card card);
    
    char getValue(){return value;}
    Suit getSuit(){return suit;}
    bool getErrorFlag(){return errorFlag;}
    
private:
    static bool isValid(char value, Suit suit);
};

// Hand class prototype
class Hand{
public:
    static const int MAX_CARDS = 30;
    
private:
    Card *myCards;
    int numCards;
    
public:
    Hand();
    void resetHand();
    bool takeCard(Card card);
    Card playCard();
    string toString();
    Card inspectCard(int k);
    
    int getNumCards(){return numCards;}
};

// Deck class prototype
class Deck{
private:
    static const int MAX_PACKS = 6;
    static const int NUM_CARDS_PER_PACK = 52;
    static const int MAX_CARDS_PER_DECK = MAX_PACKS * NUM_CARDS_PER_PACK;
    
    static Card *masterPack;
    
    Card *cards;
    int topCard;
    int numPacks;

public:
    Deck(int numPacks = 1);
    bool init(int numPacks = 1);
    void shuffle();
    Card dealCard();
    Card inspectCard(int k);
    
    int getTopCard(){return topCard;}
    
private:
    static void allocateMasterPack();
};

Card *Deck::masterPack = 0;

// Main client
int main(){   
    Deck myDeck = Deck();
    Hand *myHands;
    int numHands;
    string input;
    
    bool error = true;
    while(error){
        cout << "How many hands? (1 - 10, please): ";
        getline(cin, input);
        if(istringstream(input) >> numHands && (numHands >= 1 && 
            numHands <= 10))
            error = false;
    }
    
    myHands = new Hand[numHands];
    
    while(myDeck.getTopCard() > 0)
        for(int i = 0; i < numHands; i++)
            myHands[i].takeCard(myDeck.dealCard());
    
    cout << "Here are our hands, from unshuffled deck:\n";
    for(int i = 0; i < numHands; i++)
        cout << myHands[i].toString() << endl << endl;
    
    myDeck.init();
    myDeck.shuffle();
    for(int i = 0; i < numHands; i++)
        myHands[i].resetHand();
        
    while(myDeck.getTopCard() > 0)
        for(int i = 0; i < numHands; i++)
            myHands[i].takeCard(myDeck.dealCard());
            
    cout << "\nHere are our hands, from SHUFFLED deck:\n";
    for(int i = 0; i < numHands; i++)
        cout << myHands[i].toString() << endl << endl;
    
    return 0;
}

// Card method definitions
Card::Card(char value, Suit suit){
    set(value, suit);
}

string Card::toString(){
    if(errorFlag)
        return "[ illegal ]";
    string strSuit;
    switch(suit){
    case clubs:
        strSuit = "Clubs";
        break;
    case diamonds:
        strSuit = "Diamonds";
        break;
    case hearts:
        strSuit = "Hearts";
        break;
    case spades:
        strSuit = "Spades";
        break;
    }
    return string(1, value) + " of " + strSuit;
}

bool Card::set(char value, Suit suit){
    value = toupper(value);
    this->value = value;
    this->suit = suit;
    errorFlag = isValid(value, suit);
    return errorFlag;
}

bool Card::equals(Card card){
    if(card.getValue() != value || card.getSuit() != suit)
        return false;
    return true;
}

bool Card::isValid(char value, Suit suit){
    if(value == 'A' || value == 'J' || value == 'Q' || value == 'K' || 
        value == 'T' || (value >= '2' && value <= '9'))
        return false;
    
    return true;
}

// Hand method definitions
Hand::Hand(){
    myCards = 0;
    resetHand();
}

void Hand::resetHand(){
    if(myCards)
        delete[] myCards;
    numCards = 0;
    myCards = new Card[MAX_CARDS];
}

bool Hand::takeCard(Card card){
    if(numCards >= MAX_CARDS || card.getErrorFlag())
        return false;
    myCards[numCards++] = card;
    return true;
}

Card Hand::playCard(){
    if(numCards > 0)
        return myCards[--numCards];
    // *NOT STATED IN SPEC* return 'E'rror card if called with empty hand
    return Card('E', Card::clubs);
}

string Hand::toString(){
    if(numCards == 0)
        return "Hand = ()";
    string display = "Hand = (";
    for(int i = 0; i < numCards; i++)
        display += " " + myCards[i].toString() + ", ";
    display.erase(display.length() - 2, 2);
    display += " )";
    return display;
}

Card Hand::inspectCard(int k){
    Card::Suit suit;
    suit = static_cast<Card::Suit>(0);
    myCards[0].set('A', suit);
    if(k < 0 || k >= numCards)
        return Card('E', Card::clubs);
    return myCards[k];
}

// Deck method definitions
Deck::Deck(int numPacks){
    cards = 0;
    allocateMasterPack();
    init(numPacks);
}

bool Deck::init(int numPacks){
    if(numPacks > MAX_PACKS || numPacks < 1)
        return false;
    if(cards)
        delete[] cards;
    this->numPacks = numPacks;
    cards = new Card[NUM_CARDS_PER_PACK * numPacks];
    for(int i = 0; i < numPacks; i++){
        for(int k = 0; k < NUM_CARDS_PER_PACK; k++)
            cards[i * NUM_CARDS_PER_PACK + k] = masterPack[k];
    }
    topCard = NUM_CARDS_PER_PACK * numPacks;
    return true;
}

void Deck::shuffle(){
    random_shuffle(&cards[0], &cards[topCard]);
}

Card Deck::dealCard(){
    if(topCard > 0)
        return cards[--topCard];
    // *NOT STATED IN SPEC* return 'E'rror card if called with empty hand
    return Card('E', Card::clubs);
}

Card Deck::inspectCard(int k){
    if(k < 0 || k >= NUM_CARDS_PER_PACK * numPacks)
        return Card('E', Card::clubs);
    return cards[k];
}

void Deck::allocateMasterPack(){
    if(masterPack == 0){
        masterPack = new Card[NUM_CARDS_PER_PACK];
        Card::Suit suit;
        
        for(int k = 0; k < 4; k++){
            suit = static_cast<Card::Suit>(k);
            
            masterPack[13 * k].set('A', suit);
            for(char i = '2', j = 1; i <= '9'; i++, j++)
                masterPack[13 * k + j].set(i, suit);
            masterPack[13 * k + 9].set('T', suit);
            masterPack[13 * k + 10].set('J', suit);
            masterPack[13 * k + 11].set('Q', suit);
            masterPack[13 * k + 12].set('K', suit);
        }
    }
}

/* ---------------------------------Phase 2 test-----------------------------

K of Spades / Q of Spades / J of Spades / T of Spades / 9 of Spades / 
8 of Spades / 7 of Spades / 6 of Spades / 5 of Spades / 4 of Spades / 
3 of Spades / 2 of Spades / A of Spades / K of Hearts / Q of Hearts / 
J of Hearts / T of Hearts / 9 of Hearts / 8 of Hearts / 7 of Hearts / 
6 of Hearts / 5 of Hearts / 4 of Hearts / 3 of Hearts / 2 of Hearts / 
A of Hearts / K of Diamonds / Q of Diamonds / J of Diamonds / T of Diamonds / 
9 of Diamonds / 8 of Diamonds / 7 of Diamonds / 6 of Diamonds / 5 of Diamonds / 
4 of Diamonds / 3 of Diamonds / 2 of Diamonds / A of Diamonds / K of Clubs / 
Q of Clubs / J of Clubs / T of Clubs / 9 of Clubs / 8 of Clubs / 
7 of Clubs / 6 of Clubs / 5 of Clubs / 4 of Clubs / 3 of Clubs / 
2 of Clubs / A of Clubs / K of Spades / Q of Spades / J of Spades / 
T of Spades / 9 of Spades / 8 of Spades / 7 of Spades / 6 of Spades / 
5 of Spades / 4 of Spades / 3 of Spades / 2 of Spades / A of Spades / 
K of Hearts / Q of Hearts / J of Hearts / T of Hearts / 9 of Hearts / 
8 of Hearts / 7 of Hearts / 6 of Hearts / 5 of Hearts / 4 of Hearts / 
3 of Hearts / 2 of Hearts / A of Hearts / K of Diamonds / Q of Diamonds / 
J of Diamonds / T of Diamonds / 9 of Diamonds / 8 of Diamonds / 7 of Diamonds / 
6 of Diamonds / 5 of Diamonds / 4 of Diamonds / 3 of Diamonds / 2 of Diamonds / 
A of Diamonds / K of Clubs / Q of Clubs / J of Clubs / T of Clubs / 
9 of Clubs / 8 of Clubs / 7 of Clubs / 6 of Clubs / 5 of Clubs / 
4 of Clubs / 3 of Clubs / 2 of Clubs / A of Clubs / 

8 of Diamonds / K of Clubs / 8 of Spades / 8 of Clubs / 8 of Spades / 
Q of Spades / A of Diamonds / A of Hearts / 6 of Clubs / 9 of Spades / 
9 of Diamonds / 5 of Clubs / 5 of Spades / K of Hearts / 2 of Clubs / 
7 of Spades / 3 of Clubs / 3 of Spades / 6 of Spades / 8 of Hearts / 
7 of Diamonds / K of Diamonds / T of Diamonds / J of Diamonds / 9 of Hearts / 
K of Hearts / J of Clubs / T of Spades / 9 of Spades / 5 of Hearts / 
6 of Hearts / 6 of Diamonds / 4 of Clubs / K of Diamonds / 3 of Diamonds / 
Q of Hearts / 8 of Hearts / 9 of Clubs / Q of Diamonds / 2 of Clubs / 
7 of Spades / 7 of Clubs / T of Clubs / 4 of Hearts / 8 of Diamonds / 
7 of Hearts / T of Spades / J of Spades / 9 of Clubs / 4 of Diamonds / 
5 of Spades / A of Clubs / 3 of Hearts / J of Hearts / 3 of Spades / 
4 of Spades / A of Clubs / 9 of Diamonds / 4 of Hearts / Q of Hearts / 
2 of Hearts / K of Spades / 3 of Hearts / 2 of Diamonds / T of Diamonds / 
T of Clubs / Q of Spades / 7 of Diamonds / T of Hearts / 4 of Clubs / 
4 of Diamonds / A of Diamonds / 6 of Spades / 5 of Hearts / 7 of Clubs / 
Q of Clubs / J of Clubs / 2 of Hearts / 4 of Spades / 2 of Diamonds / 
K of Clubs / 6 of Clubs / 9 of Hearts / A of Spades / 2 of Spades / 
7 of Hearts / 6 of Diamonds / 8 of Clubs / 5 of Clubs / J of Diamonds / 
3 of Clubs / 6 of Hearts / A of Spades / 3 of Diamonds / J of Spades / 
A of Hearts / J of Hearts / 5 of Diamonds / T of Hearts / Q of Diamonds / 
5 of Diamonds / Q of Clubs / K of Spades / 2 of Spades / 

K of Spades / Q of Spades / J of Spades / T of Spades / 9 of Spades / 
8 of Spades / 7 of Spades / 6 of Spades / 5 of Spades / 4 of Spades / 
3 of Spades / 2 of Spades / A of Spades / K of Hearts / Q of Hearts / 
J of Hearts / T of Hearts / 9 of Hearts / 8 of Hearts / 7 of Hearts / 
6 of Hearts / 5 of Hearts / 4 of Hearts / 3 of Hearts / 2 of Hearts / 
A of Hearts / K of Diamonds / Q of Diamonds / J of Diamonds / T of Diamonds / 
9 of Diamonds / 8 of Diamonds / 7 of Diamonds / 6 of Diamonds / 5 of Diamonds / 
4 of Diamonds / 3 of Diamonds / 2 of Diamonds / A of Diamonds / K of Clubs / 
Q of Clubs / J of Clubs / T of Clubs / 9 of Clubs / 8 of Clubs / 
7 of Clubs / 6 of Clubs / 5 of Clubs / 4 of Clubs / 3 of Clubs / 
2 of Clubs / A of Clubs / 

4 of Clubs / 5 of Spades / J of Spades / 5 of Clubs / 3 of Spades / 
6 of Hearts / A of Clubs / 4 of Spades / J of Hearts / 2 of Diamonds / 
T of Hearts / K of Hearts / K of Spades / A of Diamonds / 4 of Hearts / 
T of Diamonds / J of Diamonds / 8 of Spades / 5 of Diamonds / 8 of Diamonds / 
A of Spades / Q of Diamonds / J of Clubs / 9 of Diamonds / 3 of Diamonds / 
K of Diamonds / 7 of Diamonds / T of Clubs / 3 of Clubs / 7 of Spades / 
7 of Hearts / K of Clubs / 2 of Hearts / 4 of Diamonds / T of Spades / 
Q of Hearts / Q of Spades / 2 of Clubs / 2 of Spades / 7 of Clubs / 
9 of Spades / 6 of Diamonds / A of Hearts / Q of Clubs / 9 of Clubs / 
5 of Hearts / 8 of Hearts / 8 of Clubs / 3 of Hearts / 6 of Clubs / 
9 of Hearts / 6 of Spades /  

Process exited with code: 0

----------------------------------------------------------------------------- */


