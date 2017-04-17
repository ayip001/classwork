#include <iostream>
#include <string>

using namespace std;

// Class StackNode  ----------------------------------
class StackNode
{ 
 public:
   StackNode *next;

   StackNode();
   virtual ~StackNode();
   void show();
};

// StackNode method definitions --------------------------
StackNode::StackNode()
{
   next = NULL;
}
StackNode::~StackNode()
{
   // nothing needed
}
void StackNode::show()
{
   cout << "(generic node) ";
}
// end StackNode method definitions ---------------------

// Class Stack ---------------------------------------
class Stack
{
   StackNode *top;
 
 public:
   Stack();
   virtual ~Stack();
   void push(StackNode  *newNode);
   StackNode *pop();
   void showStack();
};

// Stack method definitions --------------------------
Stack::Stack()
{
   top = NULL;
}

Stack::~Stack()
{
   // don't delete the stack nodes on the stack - they belong to client.
   // nothing to do. If we were cloning nodes in push() then we would need
   // to delete the remainder of the list - but we are not cloning nodes
   // in this class.
}
  
StackNode *Stack::pop()
{
   StackNode * prev;
   StackNode * curr;
  
   prev = NULL;
   curr = top;
   
   while (curr != NULL && curr -> next != NULL) {
      prev = curr;
      curr = curr -> next;
   }
   
   if (prev != NULL)
      prev -> next = NULL;
   else
      top = NULL;
   
   return curr;           
}
   
void Stack::push(StackNode  *newNode)
{   
   if (newNode == NULL) 
      return;   // emergency return
   newNode->next = top;
   top = newNode;
}  

void Stack::showStack()
{   
   StackNode *p;
    
   // Display all the nodes in the stack
   for( p = top; p != NULL; p = p->next )
      p->show();
}  

// end Stack method definitions ---------------------

// FloatNode class prototype
class FloatNode : public StackNode
{
 private:
   float data;
 public:
   FloatNode(float x);
   void show();
   float getData();
};

// FloatNode method definitions --------------------------
FloatNode::FloatNode(float x)
{
   data = x;
}

void FloatNode::show()
{
   cout.setf(ios::fixed);
   cout.precision(3);
   cout << "[" << data << "] ";
}

float FloatNode::getData()
{
   return data;  // simple accessor
}
// end FloatNode method definitions ---------------------


// FloatStack class prototype

class FloatStack : private Stack
{
 public:
   ~FloatStack();  // needed this time
   void push(float x);
   bool pop(float &f);
}; 

// FloatStack method definitions --------------------------

void FloatStack::push(float x)
{
   // create a new FloatNode
   FloatNode *fp = new FloatNode(x);

   // push the StackNode onto the stack (base class call)
   Stack::push(fp);
}

bool FloatStack::pop(float &f)
{
   f = 0.0F;      // just in case of trouble

   // pop a node
   FloatNode *fp = (FloatNode *)Stack::pop();
   if (fp == NULL)
      return false;
   
   // copy the data into the formal parameter
   f = fp->getData();

   delete fp; // delete the node (we're done with it)
   return true;
}

FloatStack::~FloatStack()
{
   // because we are creating our own StackNodes internally, we
   // do have to destroy any lingering nodes here.
   StackNode *np;

   while (np = Stack::pop())
      delete np;
}
// end FloatStack method definitions ---------------------

// main method ---------------------------------------
int main()
{

   FloatStack fstk;
   float f;

   fstk.push(1.1);
   fstk.push(2.2);
   fstk.push(3.3);
   fstk.push(4.4);
   
   for (int k = 0; k < 5; k++)
      if (fstk.pop(f))
         cout << f << " ";
      else
         cout << "(empty stack) ";
   cout << endl;

   return 0;
}

// output: 4.4 3.3 2.2 1.1 (empty stack) 
// queue output: 1.1 2.2 3.3 4.4 (empty stack)