#include <iostream>
#include <string>
#include <climits>
#include <cmath>
#include <sstream>
#include <ctime>       
#include <stdlib.h>   

using namespace std;

// Complex class prototype
class Complex{
    friend Complex operator+(const Complex & c1, const Complex & c2);
    friend Complex operator-(const Complex & c1, const Complex & c2);
    friend Complex operator*(const Complex & c1, const Complex & c2);
    friend Complex operator/(const Complex & c1, const Complex & c2);
    friend ostream & operator<<(ostream & ostrm, const Complex & c);
    friend bool operator>(const Complex & c1, const Complex & c2);
    friend bool operator==(const Complex & c1, const Complex & c2);
    
private:
    static const double DFT_VALUE;
    
protected:
    double real;
    double imag;
    
public:
    Complex(double real = DFT_VALUE, double imag = DFT_VALUE);
    bool setReal(double real = DFT_VALUE);
    bool setImag(double imag = DFT_VALUE);
    double getReal(){ return real; }
    double getImag(){ return imag; }
    double modulus() const{ return sqrt(real * real + imag * imag); }
    Complex reciprocal() const;
    string toString() const;
    Complex & operator=(const Complex &c);
    
    // exception classes
    class DivByZeroException{};
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

// Class ComplexNode prototype
class ComplexNode : public StackNode{
private:
    Complex data;
public:
    ComplexNode(Complex c){ data = c; }
    void show();
    Complex getData();
};

// Class ComplexStack prototype 
class ComplexStack : private Stack{
public:
    ~ComplexStack();
    void push(Complex c);
    bool pop(Complex &comp);
};

const double Complex::DFT_VALUE = 0;

// main client
int main(){
    cout << "demonstrating code copied from spec: ";
    Complex a(3, -4), b(1.1, 2.1), c;
    double x = 2, y = -1.7;
    c = a + b;
    cout << "\na + b = " << c;
    c = x - a;
    cout << "\nx - a = " << c;
    c = b * y;
    cout << "\nb * y = " << c;

    // and also:
    c = 8 + a;
    cout << "\n8 + a = " << c;
    c = b / 3.2;
    cout << "\nb / 3.2 = " << c;
    
    cout << "\n\ndemonstrating comparison operators:";
    cout << "\na > b? " << (a > b);
    cout << "\na / 4 > b? " << (a / 4 > b);
    cout << "\na == 3? " << (a == 3);
    cout << "\na == 3 - Complex(0, 4)? " << (a == 3 - Complex(0, 4));
    
    cout << "\n\ndemonstrating divbyzero exception:";
    try{
        a = Complex(0,0);
        cout << a.reciprocal() << "this should not display";
    }
    catch(const Complex::DivByZeroException e){
        cout << "\ncaught Complex::DivByZeroException";
    }
    
    cout << "\n\ndemonstrating ComplexStack functionality:\n";
    ComplexStack CompStk;
    Complex comp;
    
    CompStk.push(Complex(1,1));
    CompStk.push(Complex(2,2));
    CompStk.push(Complex(3,3));
    CompStk.push(Complex(4,4));
    
    for(int i = 0; i < 5; i++)
        if(CompStk.pop(comp))
            cout << comp.toString() << endl;
        else
            cout << "empty stack";
    
    return 0;
}

// Complex class method definitions
Complex operator+(const Complex & c1, const Complex & c2){
    return Complex(c1.real + c2.real, c1.imag + c2.imag);
}

Complex operator-(const Complex & c1, const Complex & c2){
    return Complex(c1.real - c2.real, c1.imag - c2.imag);
}

Complex operator*(const Complex & c1, const Complex & c2){
    return Complex(c1.real * c2.real - c1.imag * c2.imag, 
        c1.real * c2.imag + c1.imag * c2.real);
}

Complex operator/(const Complex & c1, const Complex & c2){
    return c1 * c2.reciprocal();
}

ostream & operator<<(ostream & ostrm, const Complex & c){
    ostrm << c.toString();
    return ostrm;
}

Complex & Complex::operator=(const Complex &c){
    if(this != &c){
        this->real = c.real;
        this->imag = c.imag;
    }
    return *this;
}

bool operator>(const Complex & c1, const Complex & c2){
    if(c1.modulus() > c2.modulus())
        return true;
    return false;
}

bool operator==(const Complex & c1, const Complex & c2){
    if(c1.real == c2.real && c1.imag == c2.imag)
        return true;
    return false;
}

Complex::Complex(double real, double imag){
    setReal(real);
    setImag(imag);
}

bool Complex::setReal(double real){
    this->real = real; 
    return true;
}

bool Complex::setImag(double imag){
    this->imag = imag; 
    return true;
}

Complex Complex::reciprocal() const{
    if(real * real + imag * imag == 0)
        throw DivByZeroException();
    return Complex(real / (real * real + imag * imag), -imag / (real * real 
        + imag * imag));
}

string Complex::toString() const{
    string display = "(" + to_string(real) + ", " + to_string(imag) +")"; 
    return display;
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

// ComplexNode/InStack class method definitions
void ComplexNode::show(){
    cout << data.toString() << endl;
}

Complex ComplexNode::getData(){
    return data;
}

ComplexStack::~ComplexStack(){
    StackNode *np;
    
    while(np = Stack::pop())
        delete np;
}

void ComplexStack::push(Complex c){
    ComplexNode *compPtr = new ComplexNode(c);
    
    Stack::push(compPtr);
}

bool ComplexStack::pop(Complex &comp){
    comp = Complex();
    
    ComplexNode *compPtr = (ComplexNode*)Stack::pop();
    if(compPtr == NULL)
        return false;
        
    comp = compPtr->getData();
    
    delete compPtr;
    return true;
}

/* ---------------- run result -----------------------

demonstrating code copied from spec: 
a + b = (4.100000, -1.900000)
x - a = (-1.000000, 4.000000)
b * y = (-1.870000, -3.570000)
8 + a = (11.000000, -4.000000)
b / 3.2 = (0.343750, 0.656250)

demonstrating comparison operators:
a > b? 1
a / 4 > b? 0
a == 3? 0
a == 3 - Complex(0, 4)? 1

demonstrating divbyzero exception:
caught Complex::DivByZeroException

demonstrating ComplexStack functionality:
(4.000000, 4.000000)
(3.000000, 3.000000)
(2.000000, 2.000000)
(1.000000, 1.000000)
empty stack 
Exit code: 0

---------------------------------------------------------- */