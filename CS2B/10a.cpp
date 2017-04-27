#include <iostream>
#include <string>

using namespace std;

// Class Node  ----------------------------------
class Node
{ 
public:
    Node *next;

    Node() { next = NULL; }
    virtual ~Node() {}
    virtual string toString() { return "(generic node) "; }
};

// Class Queue ---------------------------------------
class Queue
{
    Node *youngest;
 
public:
    Queue() { youngest = NULL; }
    virtual ~Queue() {}
    void add(Node *newNode);
    Node *remove();
    virtual string toString();
};

// Queue method definitions --------------------------
  
Node *Queue::remove()
{
    Node * prev;
    Node * curr;
  
    prev = NULL;
    curr = youngest;
    
    while (curr != NULL && curr -> next != NULL) {
        prev = curr;
        curr = curr -> next;
    }
    
    if (prev != NULL)
        prev -> next = NULL;
    else
        youngest = NULL;
    
    return curr;
}
    
void Queue::add(Node  *newNode)
{    
    if (newNode == NULL) 
        return;    // emergency return
    newNode->next = youngest;
    youngest = newNode;
}  

string Queue::toString()
{
    Node *p;
    int size = 0;
    string theString = "| ";
    
    for ( p = youngest; p != NULL; p = p->next )
        size++;
    
    for ( int i = size; i > 0; i-- )
    {
        p = youngest;
        for ( int j = 0; j < i - 1; j++ )
            p = p->next;
        
        theString += p->toString() + " | ";
    }
    
    return theString;
}

// end Queue method definitions ---------------------



// class Card prototype ----------------------------------------
class Card
{
public:
    enum Suit { clubs, diamonds, hearts, spades };
    static char DEFAULT_VAL;
    static Suit DEFAULT_SUIT;
    
    static const int NUM_CARD_VALS = 13;
    static const int NUM_CARD_SUITS = 4;

private:
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

    // helpers
private:
    bool isValid(char value, Suit suit);
};

char Card::DEFAULT_VAL = 'A';
Card::Suit Card::DEFAULT_SUIT = Card::spades;

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

// end of Card method definitions ----------------------------------------

// CardNode class prototype
class CardNode : public Node
{
private:
    Card data;
    
public:
    CardNode(Card x) { data = x; }
    Card getData() { return data; }
    string toString() { return data.toString(); }
};

// end CardNode method definitions ---------------------


// CardQueue class prototype

class CardQueue : public Queue
{
public:
    ~CardQueue();  // needed this time
    void add(Card x);
    Card remove();
    string toString() { return Queue::toString(); }
    
    class CardQueueEmptyException {};
}; 

// CardQueue method definitions --------------------------

void CardQueue::add(Card x)
{
    // create a new CardNode
    CardNode *fp = new CardNode(x);

    // add the Node onto the Queue (base class call)
    Queue::add(fp);
}

Card CardQueue::remove()
{
    // remove a node
    CardNode *fp = (CardNode *)Queue::remove();
    if (fp == NULL)
        throw CardQueueEmptyException();
    
    // copy the data into the formal parameter
    return fp->getData();
}

CardQueue::~CardQueue()
{
    // because we are creating our own Nodes internally, we
    // do have to destroy any lingering nodes here.
    Node *np;

    while (np = Queue::remove())
        delete np;
}
// end CardQueue method definitions ---------------------

// main method ---------------------------------------
int main()
{

    CardQueue cstk;

    cstk.add(Card('A', Card::diamonds));
    cstk.add(Card('2', Card::diamonds));
    cstk.add(Card('3', Card::diamonds));
    cstk.add(Card('4', Card::diamonds));
    
    cout << "demonstrating whole queue toString():\n\n";
    cout << cstk.toString() << endl;
    
    cout << "\nremoving cards 1 by 1:\n";
    try
    {
        for (int k = 0; k < 5; k++)
            cout << endl << cstk.remove().toString();
    }
    catch (CardQueue::CardQueueEmptyException)
    {
        cout << "\nCardQueueEmptyException caught";
    }

    return 0;
}

/* -------------------------- TEST RUN ----------------------------------------

demonstrating whole queue toString():

| A of Diamonds | 2 of Diamonds | 3 of Diamonds | 4 of Diamonds | 

removing cards 1 by 1:

A of Diamonds
2 of Diamonds
3 of Diamonds
4 of Diamonds
CardQueueEmptyException caught

Process exited with code: 0

---------------------------------------------------------------------------- */