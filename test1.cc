#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

class A{
public:
    int Avar;
    
    A(int Avar = 0){this->Avar = Avar;}
};

class B{
private:
    static A *AArray;
public:
    static void setAArray();
};

A* B::AArray = 0;

int main(){
    srand(time(NULL));
    A *p;
    p = new A[5];
    for(int i = 0; i < 52; i++)
        p[i] = A(i + 1);
    
    random_shuffle(&p[0], &p[2]);
    
    for(int i = 0; i < 52; i++)
        cout << p[i].Avar << " ";
    
    return 0;
}

void B::setAArray(){
    A *data;
    data = new A[10];
    AArray = data;
}