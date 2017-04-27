// required includes
#include <iostream>
#include <string>
#include <ctime>
#include <list>
#include <algorithm>
using namespace std;

// class Card prototype ----------------------------------------
class Card
{
public:
    enum Suit { clubs, diamonds, hearts, spades };
    static char DEFAULT_VAL;
    static Suit DEFAULT_SUIT;
    
    static const int NUM_CARD_VALS = 13;
    static const int NUM_CARD_SUITS = 4;

protected:
    char value;
    Suit suit;
    bool errorFlag;

public:
    Card(char value = DEFAULT_VAL, Suit suit = DEFAULT_SUIT);
    string toString();
    bool set(char value = DEFAULT_VAL, Suit suit = DEFAULT_SUIT);

    char getVal() { return value; }
    Suit getSuit() { return suit; }
    bool getErrorFlag() { return errorFlag; }
    bool equals(Card card);
    
    // comparison members and methods  
    const static char valueRanks[NUM_CARD_VALS]; 
    const static Suit suitRanks[NUM_CARD_SUITS];
    
    int compareTo(Card &other);
    static int getSuitRank(Suit st);
    static int getValueRank(char val);

    // helpers
protected:
    bool isValid(char value, Suit suit);
};

char Card::DEFAULT_VAL = 'A';
Card::Suit Card::DEFAULT_SUIT = Card::spades;

// class CardWMultiOrders prototype ----------------------------
class CardWMultiOrders : public Card
{
public:
    enum SortType { SORT_BY_ALL, SORT_BY_RUN, SORT_BY_SUIT };
    static SortType DEFAULT_SORT;
    
private:
    SortType sortKey;
    
public:
    CardWMultiOrders(char value = DEFAULT_VAL, Suit suit = DEFAULT_SUIT) 
        : Card(value, suit){ sortKey = DEFAULT_SORT; }
    bool setSortType( CardWMultiOrders::SortType whichType );
    int compareTo( CardWMultiOrders &other );
};

CardWMultiOrders::SortType CardWMultiOrders::DEFAULT_SORT = 
    CardWMultiOrders::SORT_BY_ALL;

// class Hand prototype ----------------------------------------
class Hand
{
public:
    // need this in-line for array declaration
    static const int MAX_CARDS_PER_HAND = 50; // should be enough for any game
    static const int NUM_CARD_VALS = 13;
    static const int NUM_CARD_SUITS = 4;

private:
    Card myCards[MAX_CARDS_PER_HAND];
    int numCards;

public:
    Hand() { resetHand(); }

    // mutators
    void resetHand() { numCards = 0; }
    bool takeCard(Card card);
    Card playCard();

    // accessors
    string toString();
    int getNumCards() { return numCards; }
    Card inspectCard(int k);
};

// class CardList prototype ----------------------------------------
class CardList
{
private:
    list<Card> theList;
public:
    CardList(){ }
    static void showList(CardList &myList);
    static void insert(CardList &myList, Card &x);
    static bool remove(CardList &myList, Card &x);
    static bool removeAll(CardList &myList, Card &x);
};

// for easy comparisons
int operator==(Card first, Card other)
    { return first.compareTo(other) == 0; }

// for client Card generation
Card generateRandomCard();

// for comparisons -- ordering values and ranks
const char Card::valueRanks[NUM_CARD_VALS]// const forces correct # initializers
    = { '2', '3', '4', '5', '6', '7', '8', '9', 'T',
    'J', 'Q', 'K', 'A'};   
const Card::Suit Card::suitRanks[NUM_CARD_SUITS] = {Card::clubs, Card::diamonds, 
    Card::hearts, Card::spades};

// main client --------------------------------------------------------
int main()
{
    //srand(time(NULL));  // or not, if you want repetition
    CardList myList;
    Card temp;
    cout << "Generating CardList of 10 cards: \n";
    for ( int k = 0; k < 5; k++ )
    {
        temp = generateRandomCard();
        CardList::insert( myList, temp );
        CardList::insert( myList, temp );
    }
    CardList::showList( myList );
    
    cout << "Removing 3 of Diamonds and 6 of Diamonds by looping remove():\n";
    temp = Card('3', Card::diamonds);
    while( CardList::remove( myList, temp ) );
    temp = Card('6', Card::diamonds);
    while( CardList::remove( myList, temp ) );
    CardList::showList( myList );
    
    cout << "Testing removeAll value which should be false(0): "
        << CardList::removeAll( myList, temp ) << endl << endl;
    
    cout << "Demonstrating comparison methods:\n\n"
        << "Sorting by all: \n";
    
    CardWMultiOrders card1('A', Card::spades), card2('2', Card::diamonds);
    if(card1.compareTo( card2 ) != 0)
        if(card1.compareTo( card2 ) > 0)
            cout << "A > 2\n\n";
        else
            cout << "A < 2\n\n";
    else
        cout << "A == 2\n\n";
    
    cout << "Sorting by run: \n";
    card1.setSortType(CardWMultiOrders::SORT_BY_RUN);
    if(card1.compareTo( card2 ) != 0)
        if(card1.compareTo( card2 ) > 0)
            cout << "A > 2\n\n";
        else
            cout << "A < 2\n\n";
    else
        cout << "A == 2\n\n";
        
    cout << "Sorting by suit: \n";
    card1.setSortType(CardWMultiOrders::SORT_BY_SUIT);
    if(card1.compareTo( card2 ) != 0)
        if(card1.compareTo( card2 ) > 0)
            cout << "spades > diamonds\n\n";
        else
            cout << "spades < diamonds\n\n";
    else
        cout << "spades == diamonds\n\n";
    

    return 0;
}

// beginning of class CardList method definitions ------------------------------

void CardList::showList(CardList &myList)
{
    list<Card>::iterator iter;
    
    cout << endl << "_____Here's the List_______" << endl;
    for( iter = myList.theList.begin(); iter != myList.theList.end(); iter++)
    {
        cout << "[" << iter->toString() << "] " << endl;
    }
    cout << endl << "_____That's all!_______" << endl << endl;
}

void CardList::insert(CardList &myList, Card &x)
{
    list<Card>::iterator iter;

    // loop until we find a tune > x
    for (iter = myList.theList.begin() ; iter != myList.theList.end() ; iter++ )
        if ( x.compareTo( *iter ) < 0 )
            break;   // found the exact place for this float 
    myList.theList.insert(iter, x);
}

bool CardList::remove(CardList &myList, Card &x)
{
    list<Card>::iterator iter;

    // loop until we find or exhaust list
    for (iter = myList.theList.begin() ; iter != myList.theList.end() ; iter++ )
        if ( x == *iter )
        {
            myList.theList.erase(iter);
            return true;
        }
    return false;
}

bool CardList::removeAll(CardList &myList, Card &x)
{
    bool found = (find(myList.theList.begin(), 
        myList.theList.end(), x) != myList.theList.end());
    if(!found)
        return false;
    myList.theList.remove(x);
    
    return true;
}

Card generateRandomCard()
{
    Card::Suit suit;
    char val;

    suit = (Card::Suit) ( rand() % Card::NUM_CARD_SUITS );
    val = Card::valueRanks[ rand() % Card::NUM_CARD_VALS ];

    return Card(val, suit);
}
// end of CardList method definitions ---------------------------

// beginning of Card method definitions ----------------------------------------
// constructor
Card::Card(char value, Suit suit)
{
    // because mutator sets errorFlag, we don't have to test
    set(value, suit);
}

// stringizer
string Card::toString()
{
    string retVal = " ";  // just enough space for the value char

    if (errorFlag)
        return "** illegal **";

    // convert char to a string
    retVal[0] = value;

    if (suit == spades)
        retVal += " of Spades";
    else if (suit == hearts)
        retVal += " of Hearts";
    else if (suit == diamonds)
        retVal += " of Diamonds";
    else if (suit == clubs)
        retVal += " of Clubs";

    return retVal;
}

// mutator
bool Card::set(char value, Suit suit)
{
    char upVal;

    // convert to uppercase to simplify (may need to #include <cctype>)
    upVal = toupper((int)value);

    if ( !isValid(upVal, suit))
    {
        errorFlag = true;
        return false;
    }

    // else implied
    errorFlag = false;
    this->value = upVal;
    this->suit = suit;
    return true;
}

// helper
bool Card::isValid(char value, Suit suit)
{
    string upVal = "_";  // string to hold the 1-char value
    string legalVals = "23456789TJQKA";

    // convert to uppercase to simplify
    upVal[0] = toupper((int)value);

    // check for validity
    if ( legalVals.find(upVal) != string::npos )
        return true;
    else
        return false;
}

bool Card::equals(Card card)
{
    if (this->value != card.value)
        return false;
    if (this->suit != card.suit)
        return false;
    if (this->errorFlag != card.errorFlag)
        return false;
    return true;
}

// Card comparison method definitions ------------------------------------------
int Card::compareTo(Card &other)
{
    if (this->value == other.value)
        return ( getSuitRank(this->suit) - getSuitRank(other.suit) );
    // else
    return getValueRank(this->value) - getValueRank(other.value) ;
}

int Card::getSuitRank(Suit st)
{
    int k;

    for (k = 0; k < NUM_CARD_SUITS; k++) 
        if (suitRanks[k] == st)
            return k;

    // should not happen
    return 0;
}

int Card::getValueRank(char val)
{
    int k;

    for (k = 0; k < NUM_CARD_VALS; k++) 
        if (valueRanks[k] == val)
            return k;

    // should not happen
    return 0;
}

// end of Card method definitions ----------------------------------------

// beginning of CardWMultiOrders method definitions ----------------------------
bool CardWMultiOrders::setSortType( CardWMultiOrders::SortType whichType )
{
    switch (whichType)
    {
    case SORT_BY_ALL:
    case SORT_BY_RUN:
    case SORT_BY_SUIT:
        sortKey = whichType;
        return true;
    default:
        return false;
    }
    return true;
}

int CardWMultiOrders::compareTo( CardWMultiOrders &other )
{
    switch (sortKey)
    {
    case SORT_BY_ALL:
        return Card::compareTo( other );
        break;
    case SORT_BY_RUN:
        return Card::getValueRank( value ) - Card::getValueRank( other.value );
        break;
    case SORT_BY_SUIT:
        return Card::getSuitRank( suit ) - Card::getSuitRank( other.suit);
        break;
    default:
        return false;
    }
    return true;
}
// end of CardWMultiOrders method definitions ----------------------------

// beginning of Hand method definitions ----------------------------------------
bool Hand::takeCard(Card card)
{
    if (numCards >= MAX_CARDS_PER_HAND)
        return false;

    // check for valid card - spec says to return true at this point even if invalid
    if (card.getErrorFlag())
        return true;

    myCards[numCards++] = card;
    return true;
}

Card Hand::playCard()
{
    // always play highest card in array.  client will prepare this position.
    // in rare case that client tries to play from a spent hand, return error

    Card errorReturn(0, Card::spades); // in rare cases

    if (numCards == 0)
        return errorReturn;
    else
        return myCards[--numCards];
}

Card Hand::inspectCard(int k)
{
    // return copy of card at position k.
    // if client tries to access out-of-bounds card, return error

    Card errorReturn(0, Card::spades); // force errorFlag, in rare cases

    if (k < 0 || k >= numCards)
        return errorReturn;
    else
        return myCards[k];
}

string Hand::toString()
{
    int k;
    string retVal = "Hand =  ( ";

    for (k = 0; k < numCards; k++)
    {
        retVal += myCards[k].toString();
        if (k < numCards - 1)
            retVal += ", ";
    }
    retVal += " )";
    return retVal;
}
// end of Hand method definitions ------------------------------------

/* ----------------------- TEST RUN -------------------------------------------

Generating CardList of 10 cards: 

_____Here's the List_______
[3 of Diamonds] 
[3 of Diamonds] 
[5 of Hearts] 
[5 of Hearts] 
[6 of Diamonds] 
[6 of Diamonds] 
[9 of Diamonds] 
[9 of Diamonds] 
[J of Spades] 
[J of Spades] 

_____That's all!_______

Removing 3 of Diamonds and 6 of Diamonds by looping remove():

_____Here's the List_______
[5 of Hearts] 
[5 of Hearts] 
[9 of Diamonds] 
[9 of Diamonds] 
[J of Spades] 
[J of Spades] 

_____That's all!_______

Demonstrating comparison methods:

Sorting by all: 
A > 2

Sorting by run: 
A == 2

Sorting by suit: 
spades > diamonds



Process exited with code: 0

---------------------------------------------------------------------------- */