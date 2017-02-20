/*------------------------------------------------------------------------
Two classes used by assignment #4.  Do not modify these defintions.  
Place the prototypes and definitions into your final submission, 
with each element appearing in the correct place among the other protypes, 
defintions, and main().

The #includes are needed by my solution and will probably be needed
by yours, so you should place them in your project at the top of the
file(s).
----------------------------------------------------------------------- */

#include <iostream>
#include <string>
#include <climits>
#include <cmath>
#include <sstream>
#include <ctime>       
#include <stdlib.h>   
using namespace std;

// ++++++++++++++++++++ helper class for client and these member methods

// IntPair allows public, no filtering; classes that use it will protect it
class IntPair{
public:
    long firstInt;
    long secondInt;

    IntPair(){ firstInt = secondInt = 0; }
    IntPair(long frst, long scnd){ firstInt = frst;  secondInt = scnd; }
    string toString();
};

// EncryptionSupport contains only static methods that clients can use wherever
// all method names should be fairly descriptive other than inverseMonN(), which
// you can take as a black-box (see description of assignment)
class EncryptionSupport{
public:
    static bool isPrime(long x);
    static long inverseModN(long a, long n);
    static long getSmallRandomPrime();
    static long getMedSizedRandomPrime();
};

// InternetUser class prototype
class InternetUser{
protected:
    string name;
    string ip;

private:
    static const int MAX_NAME_LEN = 50;
    static const int MIN_NAME_LEN = 2;
    static const string DFT_NAME;
    static const int MAX_IP_LEN = 15;
    static const int MIN_IP_LEN = 7;
    static const string DFT_IP;
    
    static bool isNameValid(string name);
    static bool isIpValid(string ip);
    
public:
    InternetUser();
    InternetUser(string name, string ip);
    
    string getName(){ return name; }
    string getIp(){ return ip; }
    bool setName(string name);
    bool setIp(string ip);
    
    string toString();
};

const string InternetUser::DFT_NAME = "(undefined)";
const string InternetUser::DFT_IP = "0.0.0.0";

// Communicator class prototype
class Communicator : public InternetUser {
private:
    static const int MAX_ATTEMPT = 500;
    int MAX_PQ = sqrt(LONG_MAX); // complier won't allow static const
    
    IntPair publicKey;
    IntPair privateKey;
    
    long firstPrime;    // p
    long secondPrime;   // q
    long n, phi, e, d;
    
public:
    static const int ERROR_FLAG_NUM = 0;
    
    Communicator();
    Communicator(long firstPrime, long secondPrime);
    Communicator(string name, string ip);
    Communicator(string name, string ip, long firstPrime, long secondPrime);
    
    void resetNum();
    bool setPQ(long p, long q);
    IntPair getPublicKey(){ return publicKey; }
    IntPair getPrivateKey(){ return privateKey; }
    
    string toString();
    
private:
    bool isPQValid(long p, long q);
    bool computeBothEncrKeys();
};

// Class StackNode prototype
class StackNode{ 
public:
    StackNode *next;
    
    StackNode(){ next = NULL; }
    virtual ~StackNode(){}
    void show();
};

// Class Stack prototype
class Stack{
    StackNode *top;
 
public:
    Stack(){ top = NULL; }
    virtual ~Stack(){}
    void push(StackNode *newNode);
    StackNode *pop();
    void showStack();
};

// Class IuNode prototype
class IuNode : public StackNode{
private:
    InternetUser data;
public:
    IuNode(InternetUser user){ data = user; }
    void show();
    InternetUser getData();
};

// Class IuStack prototype 
class IuStack : private Stack{
public:
    ~IuStack();
    void push(InternetUser user);
    bool pop(InternetUser &iu);
};

// main client
int main(){
    // first part
    cout << "Base Class Testing ***********************\n\n";
    
    InternetUser user1 = InternetUser();
    cout << user1.toString() << endl << endl;
    
    InternetUser user2 = InternetUser("test mutator", "asdf");  // bad ip
    user2.setName("K");                                         // bad name
    user2.setIp("192.168.2.1");
    cout << user2.toString() << endl << endl;
    
    cout << "Testing accessor for ip: " << user2.getIp() << endl << endl;
    
    user1.setName("bad ip entered");
    user1.setIp("bad ip");
    cout << user1.toString() << endl << endl;
    
    cout << "success as expected\n\n\nDerived Class Constructor Testing ******"
        << "*********\n\n";
    
    Communicator comm1 = Communicator();
    cout << "----------------\n\n" << comm1.toString() << endl << endl;
    
    Communicator comm2 = Communicator(67, 89);
    cout << "----------------\n\n" << comm2.toString() << endl << endl;
    
    Communicator comm3 = Communicator("3", "3.33.33.333");  // bad name
    cout << "----------------\n\n" << comm3.toString() << endl << endl;
    
    Communicator comm4 = Communicator("comm4", "4", 4, 90); // bad p, q, and ip
    cout << "----------------\n\n" << comm4.toString() << endl << endl;
    
    cout << "----------------\n\n\nDerived and Base Class Mutator Testing "
        << "**********\n\n";
    
    comm1.setPQ(809, 821);
    cout << "----------------\n\n" << comm1.toString() << endl << endl;
    
    cout << "----------------\n\n\nDerived Class Accessor Testing "
        << "**********\n\n";
        
    cout << comm4.getPrivateKey().toString() << endl 
        << comm4.getPublicKey().toString() << endl 
        << comm1.getPrivateKey().toString() << endl 
        << comm1.getPublicKey().toString() << endl << endl;
    
    cout << "----------------\n\n\nIU Stack Testing "
        << "**********\n\n";
    
    IuStack iuStk;
    InternetUser user;
    
    iuStk.push(InternetUser("first guy", "1.1.1.1"));
    iuStk.push(InternetUser("second guy", "2.2.2.2"));
    iuStk.push(InternetUser("third guy", "3.3.3.3"));
    iuStk.push(InternetUser("fourth guy", "4.4.4.4"));
    
    for(int i = 0; i < 5; i++)
        if(iuStk.pop(user))
            cout << user.toString() << endl;
        else
            cout << "empty stack";
    
    return 0;
}

// helper class IntPair method definitions ----------------------------------
string IntPair::toString(){
    ostringstream cnvrt1, cnvrt2;
    string retString;

    cnvrt1 << firstInt;
    cnvrt2 << secondInt;

    retString = "(" + cnvrt1.str() + ", " + cnvrt2.str() + ")";

    return retString;
}

// helper class EncryptionSupport method definitions -------------------------
bool EncryptionSupport::isPrime(long x){
    long k, loopLim;

    if(x < 2)
        return false;
    if(x < 4)
        return true;
    if(x % 2 == 0 || x % 3 == 0)
        return false;

   // now use the fact the all primes of form 6k +/- 1
    loopLim = (long)sqrt(x);
    for(k = 5; k <= loopLim; k += 6)
        if(x % k == 0 || x % (k + 2) == 0)
            return false;
    
    return true;
}

long EncryptionSupport::getSmallRandomPrime(){
    int index;
    long lowPrimes[] = {
        19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
        71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
        127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
        179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
        233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
        283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
        353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
        419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
        467, 479, 487, 491, 499, 503, 509, 521, 523, 541
    };
    short arraySize = sizeof(lowPrimes) / sizeof(lowPrimes[0]);

    // pick prime in the above array bet 0 and arraySize - 1
    index = (int) (rand() % (arraySize - 1));

    return lowPrimes[index];
}

long EncryptionSupport::getMedSizedRandomPrime(){
    int index;
    long medPrimes[] = {
        541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607,
        613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677,
        683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761,
        769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853,
        857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937,
        941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019,
        1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087,
        1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153,
        1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223,
    };
    short arraySize = sizeof(medPrimes) / sizeof(medPrimes[0]);

    // pick prime in the above array bet 0 and arraySize - 1
    index = (int) (rand() % (arraySize - 1));

    return medPrimes[index];
}

long EncryptionSupport::inverseModN(long a, long n){
    // uses extended euclidean algorithm giving as + nt = gcd(n, a), 
    // with gcd(n, a) = 1,  and s, t discovered.  s = 1/a, and t ignored

    long s, t, r, sPrev, tPrev, rPrev, temp, q, inverse;

    // special key encryption conditions;  we will pick some prime e >= 3 for a
    if(a < 3 || a >= n || !isPrime(a))
        return 0;  // error

                   // we are now guaranteed 3 <= a < n and gcd(a, n) = 1;

                   // initialize working variables
    s = 0;         t = 1;         r = n;
    sPrev = 1;    tPrev = 0;    rPrev = a;

    while(r != 0){
        q = rPrev / r;

        temp = r;
        r = rPrev - q * r;
        rPrev = temp;

        temp = s;
        s = sPrev - q * s;
        sPrev = temp;

        temp = t;
        t = tPrev - q * t;
        tPrev = temp;
    }

    inverse = sPrev % n;
    if(inverse < 0)
        inverse += n;
    return inverse;
}

// InternetUser class method definitions
InternetUser::InternetUser(){
    setName(DFT_NAME);
    setIp(DFT_IP);
}

InternetUser::InternetUser(string name, string ip){
    if(!setName(name))
        setName(DFT_NAME);
    if(!setIp(ip))
        setIp(DFT_IP);
}

bool InternetUser::isNameValid(string name){
    if(name.length() < MIN_NAME_LEN || name.length() > MAX_NAME_LEN)
        return false;
    return true;
}

bool InternetUser::isIpValid(string ip){
    if(ip.length() < MIN_IP_LEN || ip.length() > MAX_IP_LEN)
        return false;
    return true;
}

bool InternetUser::setName(string name){
    if(!isNameValid(name))
        return false;
    this->name = name;
    return true;
}

bool InternetUser::setIp(string ip){
    if(!isIpValid(ip))
        return false;
    this->ip = ip;
    return true;
}

string InternetUser::toString(){
    string description;
    description = "Name: " + name + "\nIP: " + ip;
    return description;
}

// Communicator class method definitions

Communicator::Communicator() : InternetUser(){
    resetNum();
}

Communicator::Communicator(long firstPrime, long secondPrime) 
    : InternetUser(){
    setPQ(firstPrime, secondPrime);
}

Communicator::Communicator(string name, string ip) : InternetUser(name, ip){
    resetNum();
}

Communicator::Communicator(string name, string ip, long firstPrime, 
    long secondPrime) : InternetUser(name, ip){
    resetNum();
    setPQ(firstPrime, secondPrime);
}

void Communicator::resetNum(){
    privateKey = IntPair(ERROR_FLAG_NUM, ERROR_FLAG_NUM);
    publicKey = IntPair(ERROR_FLAG_NUM, ERROR_FLAG_NUM);
    firstPrime = ERROR_FLAG_NUM;
    secondPrime = ERROR_FLAG_NUM;
    n = phi = e = d = ERROR_FLAG_NUM;
}

bool Communicator::setPQ(long p, long q){
    if(!isPQValid(p, q))
        return false;
    firstPrime = p;
    secondPrime = q;
    return computeBothEncrKeys();
}

string Communicator::toString(){
    string description;
    description = InternetUser::toString() + "\n\n(p, q)  n, phi, e, d: (" 
        + to_string(firstPrime) + ", " + to_string(secondPrime) + ")  " 
        + to_string(n) + ", " + to_string(phi) + ", " + to_string(e) + ", " 
        + to_string(d) + "\npublic key" + publicKey.toString() 
        + "\nprivate key" + privateKey.toString();
    return description;
}

bool Communicator::isPQValid(long p, long q){
    if(p == q)
        return false;
    if(!EncryptionSupport::isPrime(p) || !EncryptionSupport::isPrime(q))
        return false;
    return true;
}

bool Communicator::computeBothEncrKeys(){
    if(!isPQValid(firstPrime, secondPrime))
        return false;
    n = firstPrime * secondPrime;
    phi = (firstPrime - 1) * (secondPrime - 1);
    
    int attempt = 0;
    do{
        e = EncryptionSupport::getSmallRandomPrime();
        if(attempt++ > MAX_ATTEMPT)
            return false;
    }
    while(e > phi || phi % e == 0 || e == firstPrime || e == secondPrime);
    d = EncryptionSupport::inverseModN(e, n);
    publicKey = IntPair(e, n);
    privateKey = IntPair(d, n);
    return true;
}

// StackNode/Stack class method definitions
void StackNode::show()
{
    cout << "(generic node) ";
}

StackNode *Stack::pop(){
    StackNode *temp;
   
    temp = top;
    if(top != NULL){
        top = top->next;   
        temp->next = NULL;   // don't give client access to stack!
    }
    return temp;           
}
   
void Stack::push(StackNode *newNode){   
    if (newNode == NULL) 
        return;   // emergency return
    newNode->next = top;
    top = newNode;
}  

void Stack::showStack(){   
    StackNode *p;
    
    // Display all the nodes in the stack
    for(p = top; p != NULL; p = p->next)
        p->show();
}

// IuNode/InStack class method definitions
void IuNode::show(){
    cout << data.toString() << endl;
}

InternetUser IuNode::getData(){
    return data;
}

IuStack::~IuStack(){
    StackNode *np;
    
    while(np = Stack::pop())
        delete np;
}

void IuStack::push(InternetUser user){
    IuNode *iuPtr = new IuNode(user);
    
    Stack::push(iuPtr);
}

bool IuStack::pop(InternetUser &iu){
    iu = InternetUser();
    
    IuNode *iuPtr = (IuNode*)Stack::pop();
    if(iuPtr == NULL)
        return false;
        
    iu = iuPtr->getData();
    
    delete iuPtr;
    return true;
}