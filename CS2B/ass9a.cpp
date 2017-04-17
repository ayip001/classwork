#include <iostream>
#include <string>

using namespace std;

// File FHsdTree.h
// Template definitions for FHsdTrees, which are general trees
#ifndef FHsdTree_H
#define FHsdTree_H
//#include <string>

// advanced prototype for the FHsdTreeNode to use to declare a friend
template <class Object>
class FHsdTree;

// ---------------------- FHsdTreeNode Prototype --------------------------
template <class Object>
class FHsdTreeNode
{
   friend class FHsdTree<Object>;

protected: 
   FHsdTreeNode *firstChild, *sib, *prev;
   Object data;
   FHsdTreeNode *myRoot;  // needed to test for certain error
   bool deleted;

public:
   FHsdTreeNode( const Object & d = Object(), 
      FHsdTreeNode *sb = NULL, FHsdTreeNode *chld = NULL, 
      FHsdTreeNode *prv = NULL, bool deleted = false )
      : firstChild(chld), sib(sb), prev(prv), data(d), myRoot(NULL), 
      deleted(false)
   { }
   Object GetData() const { return data; }

protected:
   // for use only by FHsdTree
   FHsdTreeNode( const Object & d, 
      FHsdTreeNode *sb, FHsdTreeNode *chld, FHsdTreeNode *prv,
      FHsdTreeNode *root, bool deleted )
      : firstChild(chld), sib(sb), prev(prv), data(d), myRoot(root), 
      deleted(false)
   { }
}; 

// --------------------------- FHsdTree Prototype ------------------------------
template <class Object>
class FHsdTree
{
protected:
   int mSize;
   FHsdTreeNode<Object> *mRoot;

public:
   FHsdTree() { mSize = 0; mRoot = NULL; }
   FHsdTree(const FHsdTree &rhs) { mRoot = NULL; mSize = 0; *this = rhs; }
   virtual ~FHsdTree() { clear(); }
   bool empty() const { return (mSize == 0); }
   int sizePhysical() const { return mSize; } // counts SD
   void clear() { removeNode(mRoot); }
   const FHsdTree & operator=(const FHsdTree &rhs);

   FHsdTreeNode<Object> *addChild( FHsdTreeNode<Object> *treeNode, 
      const Object &x ); // modified for SD
   FHsdTreeNode<Object> *find(const Object &x) { return find(mRoot, x); }
   FHsdTreeNode<Object> *find(FHsdTreeNode<Object> *root, 
      const Object &x, int level = 0); // modified for SD

   bool remove(const Object &x) { return remove(mRoot, x); }
   bool remove(FHsdTreeNode<Object> *root, const Object &x); 
   void removeNode(FHsdTreeNode<Object> *nodeToDelete);   // modified for SD
   void removeNodePhysical(FHsdTreeNode<Object> *nodeToDelete);
   
   // usual client interfaces (entire tree implied)
   int size() const { return size(mRoot); } // new SD method
   bool collectGarbage() 
      { return collectGarbage(mRoot, 0); } // physical delete SD
   void display() const { display(mRoot, 0); }
   void displayPhysical() const { displayPhysical(mRoot, 0); }
   template <class Processor>
   void traverse(Processor func) const { traverse(func, mRoot, 0); }

   // recursive helpers
   int size(FHsdTreeNode<Object> *treeNode) const; // doesn't count SD
   bool collectGarbage(FHsdTreeNode<Object> *treeNode, int level = 0);
   void display(FHsdTreeNode<Object> *treeNode, int level = 0) const;
   void displayPhysical(FHsdTreeNode<Object> *treeNode, int level = 0) const;
   template <class Processor>
   void traverse(Processor func, FHsdTreeNode<Object> *treeNode, int level = 0)
      const;

protected:
   FHsdTreeNode<Object> *clone( FHsdTreeNode<Object> *root) const;
   void setMyRoots(FHsdTreeNode<Object> *treeNode);
};

// FHsdTree Method Definitions -------------------------------------------------
template <class Object>
FHsdTreeNode<Object>* FHsdTree<Object>::find(FHsdTreeNode<Object> *root, 
   const Object &x, int level)
{
   FHsdTreeNode<Object> *retval;
 
   if (mSize == 0 || root == NULL)
      return NULL;
      
   if (root->deleted == true)
      return NULL;

   if (root->data == x)
      return root;

   // otherwise, recurse.  don't process sibs if this was the original call
   if ( level > 0 && (retval = find(root->sib, x, level)))
      return retval;
   return find(root->firstChild, x, level+1);
}

template <class Object>
bool FHsdTree<Object>::remove(FHsdTreeNode<Object> *root, const Object &x)
{
   FHsdTreeNode<Object> *tn = NULL;

   if (mSize == 0 || root == NULL)
      return false;
  
   if ( (tn = find(root, x)) != NULL )
   {
      removeNode(tn);
      return true;
   }
   return false;
}

template <class Object>
const FHsdTree<Object> &FHsdTree<Object>::operator=
   (const FHsdTree &rhs)
{
   if (&rhs != this) 
   {
      clear();
      mRoot = clone(rhs.mRoot);
      mSize = rhs.mSize;
      setMyRoots(mRoot);
   }
   return *this;
}

template <class Object>
void FHsdTree<Object>::removeNode(FHsdTreeNode<Object> *nodeToDelete)
{
   if (nodeToDelete == NULL || mRoot == NULL)
      return;
   if (nodeToDelete->myRoot != mRoot)
      return;  // silent error, node does not belong to this tree
   if (nodeToDelete->deleted == true)
      return; // ALREADY DELETED

   // remove all the children of this node
   
   /* //for hard deletion
   while (nodeToDelete->firstChild)
      removeNode(nodeToDelete->firstChild);

   if (nodeToDelete->prev == NULL)
      mRoot = NULL;  // last node in tree
   else if (nodeToDelete->prev->sib == nodeToDelete)
      nodeToDelete->prev->sib = nodeToDelete->sib; // adjust left sibling
   else
      nodeToDelete->prev->firstChild = nodeToDelete->sib;  // adjust parent

   // adjust the successor sib's prev pointer
   if (nodeToDelete->sib != NULL)
      nodeToDelete->sib->prev = nodeToDelete->prev;

   delete nodeToDelete;
   --mSize; */
   
   nodeToDelete->deleted = true;
}

template <class Object>
void FHsdTree<Object>::removeNodePhysical(FHsdTreeNode<Object> *nodeToDelete)
{
   if (nodeToDelete == NULL || mRoot == NULL)
      return;
   if (nodeToDelete->myRoot != mRoot)
      return;  // silent error, node does not belong to this tree

   // remove all the children of this node IF SD
   while (nodeToDelete->firstChild)
      removeNodePhysical(nodeToDelete->firstChild);

   if (nodeToDelete->prev == NULL)
      mRoot = NULL;  // last node in tree
   else if (nodeToDelete->prev->sib == nodeToDelete)
      nodeToDelete->prev->sib = nodeToDelete->sib; // adjust left sibling
   else
      nodeToDelete->prev->firstChild = nodeToDelete->sib;  // adjust parent

   // adjust the successor sib's prev pointer
   if (nodeToDelete->sib != NULL)
      nodeToDelete->sib->prev = nodeToDelete->prev;

   delete nodeToDelete;
   --mSize;
}

template <class Object>
FHsdTreeNode<Object> *FHsdTree<Object>::addChild( 
   FHsdTreeNode<Object> *treeNode, const Object &x )
{
   // empty tree? - create a root node if user passes in NULL
   if (mSize == 0)
   {
      if (treeNode != NULL)
         return NULL; // silent error something's fishy.  treeNode can't right
      mRoot = new FHsdTreeNode<Object>(x, NULL, NULL, NULL, false);
      mRoot->myRoot = mRoot;
      mSize = 1;
      return mRoot;
   }
   if (treeNode == NULL)
      return NULL; // inserting into a non_null tree with a null parent
   if (treeNode->myRoot != mRoot)
      return NULL;  // silent error, node does not belong to this tree
   if (treeNode->deleted)
      return NULL; // IF DELETED THEN NODE SHOULD NOT ADD CHILD

   // push this node into the head of the sibling list; adjust prev pointers
   FHsdTreeNode<Object> *newNode = new FHsdTreeNode<Object>(x, 
      treeNode->firstChild, NULL, treeNode, mRoot, false);  
      // sib, child, prev, root
   treeNode->firstChild = newNode;
   if (newNode->sib != NULL)
      newNode->sib->prev = newNode;
   ++mSize;
   return newNode;
}

template <class Object>
void FHsdTree<Object>::display(FHsdTreeNode<Object> *treeNode, int level) const
{
   // this will be static and so will be shared by all calls - a special technique to
   // be avoided in recursion, usually
   static string blankString = "                                    ";
   string indent;

   // stop runaway indentation/recursion
   if  (level > (int)blankString.length() - 1)
   {
      cout << blankString << " ... " << endl;
      return;
   }

   if (treeNode == NULL)
      return;

   indent = blankString.substr(0, level);
   if (!treeNode->deleted)
   {
      cout << indent << treeNode->data  << endl;
      display( treeNode->firstChild, level + 1 );
   }
   if (level > 0)
      display( treeNode->sib, level );
}

template <class Object>
void FHsdTree<Object>::displayPhysical(FHsdTreeNode<Object> *treeNode, int level) const
{
   // this will be static and so will be shared by all calls - a special technique to
   // be avoided in recursion, usually
   static string blankString = "                                    ";
   string indent;

   // stop runaway indentation/recursion
   if  (level > (int)blankString.length() - 1)
   {
      cout << blankString << " ... " << endl;
      return;
   }

   if (treeNode == NULL)
      return;

   indent = blankString.substr(0, level);

   cout << indent << treeNode->data << 
      (treeNode->deleted ? " (D)" : "") << endl;
   displayPhysical( treeNode->firstChild, level + 1 );
   if (level > 0)
      displayPhysical( treeNode->sib, level );
}

template <class Object>
int FHsdTree<Object>::size(FHsdTreeNode<Object> *treeNode)
   const
{
   int temp = 0;
   if (treeNode == NULL)
      return 0;
      
   if (!treeNode->deleted)
      temp += size(treeNode->firstChild);
      
   return temp + (treeNode->deleted ? 0 : 1) + size(treeNode->sib);
}

template <class Object>
bool FHsdTree<Object>::collectGarbage(FHsdTreeNode<Object> *treeNode, int level)
{
   if (treeNode == NULL)
      return false;
   
   
   if(treeNode->deleted)
   {
      removeNodePhysical(treeNode);
      return true;
   }
   collectGarbage(treeNode->firstChild, level+1);
   
   
   if (level > 0)
      collectGarbage(treeNode->sib, level);
}

template <class Object>
template <class Processor>
void FHsdTree<Object>::traverse(Processor func, FHsdTreeNode<Object> *treeNode, int level)
   const
{
   if (treeNode == NULL)
      return;
   
   if (!treeNode->deleted)
   {
      func(treeNode->data);
      traverse(func, treeNode->firstChild, level+1);
   }
   
   if (level > 0)
      traverse(func, treeNode->sib, level);
}

template <class Object>
FHsdTreeNode<Object> *FHsdTree<Object>::clone(
   FHsdTreeNode<Object> *root) const
{
   FHsdTreeNode<Object> *newNode;
   if (root == NULL)
      return NULL;

   // does not set myRoot which must be done by caller
   newNode = new FHsdTreeNode<Object>(
      root->data, 
      clone(root->sib), clone(root->firstChild), false);

   // entire subtree is cloned, but wire this node into its sib and first chld
   if (newNode->sib)
      newNode->sib->prev = newNode;
   if (newNode->firstChild)
      newNode->firstChild->prev = newNode;
   return newNode;
}

template <class Object>
void FHsdTree<Object>::setMyRoots(FHsdTreeNode<Object> *treeNode)
{
   if (treeNode == NULL)
      return;

   treeNode->myRoot = mRoot;
   setMyRoots(treeNode->sib);
   setMyRoots(treeNode->firstChild);
}

#endif

// FHsdTree main

//#include <iostream>
//#include <string>
//using namespace std;
//#include "FHsdTree.h"

template <typename Object>
class PrintObject
{
public:
   void operator()(Object obj)
   {
      cout << obj << " ";
   }
};


int main()
{
   FHsdTree<string> sceneTree;
   FHsdTreeNode<string> *tn;

   cout << "Starting tree empty? " << sceneTree.empty() << endl << endl;

   // create a scene in a room
   tn = sceneTree.addChild(NULL, "room");

   // add three objects to the scene tree
   sceneTree.addChild(tn, "Lily the canine");

   sceneTree.addChild(tn, "Miguel the human");
   sceneTree.addChild(tn, "table");

   // add some parts to Miguel
   tn = sceneTree.find("Miguel the human");

   // Miguel's left arm
   tn = sceneTree.addChild(tn, "torso");
   tn = sceneTree.addChild(tn, "left arm");
   tn =  sceneTree.addChild(tn, "left hand");
   sceneTree.addChild(tn, "thumb");
   sceneTree.addChild(tn, "index finger");
   sceneTree.addChild(tn, "middle finger");
   sceneTree.addChild(tn, "ring finger");
   sceneTree.addChild(tn, "pinky");

   // Miguel's right arm
   tn = sceneTree.find("Miguel the human");
   tn = sceneTree.find(tn, "torso");
   tn = sceneTree.addChild(tn, "right arm");
   tn =  sceneTree.addChild(tn, "right hand");
   sceneTree.addChild(tn, "thumb");
   sceneTree.addChild(tn, "index finger");
   sceneTree.addChild(tn, "middle finger");
   sceneTree.addChild(tn, "ring finger");
   sceneTree.addChild(tn, "pinky");

   // add some parts to Lily
   tn = sceneTree.find("Lily the canine");
   tn = sceneTree.addChild(tn, "torso");
   sceneTree.addChild(tn, "right front paw");
   sceneTree.addChild(tn, "left front paw");
   sceneTree.addChild(tn, "right rear paw");
   sceneTree.addChild(tn, "left rear paw");
   sceneTree.addChild(tn, "spare mutant paw");
   sceneTree.addChild(tn, "wagging tail");

   // add some parts to table
   tn = sceneTree.find("table");
   sceneTree.addChild(tn, "north east leg");
   sceneTree.addChild(tn, "north west leg");
   sceneTree.addChild(tn, "south east leg");
   sceneTree.addChild(tn, "south west leg");

   cout << "\n------------ Loaded Tree ----------------- \n";
   sceneTree.display();

   sceneTree.remove("spare mutant paw");
   sceneTree.remove("Miguel the human");
   sceneTree.remove("an imagined higgs boson");

   cout << "\n------------ Virtual (soft) Tree ----------------- \n";
   sceneTree.display();

   cout << "\n------------ Physical (hard) Display ----------------- \n";
   sceneTree.displayPhysical();

   cout << "------- Testing Sizes (compare with above)----------- \n";
   cout << "virtual (soft) size: " << sceneTree.size() << endl;
   cout << "physical (hard) size: " << sceneTree.sizePhysical() << endl;

   cout << "------------ Collecting Garbage -------------------- \n";
   cout << "found soft-deleted nodes? " << sceneTree.collectGarbage() << endl;
   cout << "immediate collect again? " << sceneTree.collectGarbage() << endl;

   cout << "--------- Hard Display after garb col ------------ \n";

   sceneTree.displayPhysical();

   cout << "Semi-deleted tree empty? " << sceneTree.empty() << endl << endl;
   sceneTree.remove("room");
   sceneTree.collectGarbage();
   cout << "Completely-deleted tree empty? " << sceneTree.empty() << endl << endl;

   return 0;
}

/* ---------------------------- test run --------------------------------------

Starting tree empty? 1


------------ Loaded Tree ----------------- 
room
 table
  south west leg
  south east leg
  north west leg
  north east leg
 Miguel the human
  torso
   right arm
    right hand
     pinky
     ring finger
     middle finger
     index finger
     thumb
   left arm
    left hand
     pinky
     ring finger
     middle finger
     index finger
     thumb
 Lily the canine
  torso
   wagging tail
   spare mutant paw
   left rear paw
   right rear paw
   left front paw
   right front paw

------------ Virtual (soft) Tree ----------------- 
room
 table
  south west leg
  south east leg
  north west leg
  north east leg
 Lily the canine
  torso
   wagging tail
   left rear paw
   right rear paw
   left front paw
   right front paw

------------ Physical (hard) Display ----------------- 
room
 table
  south west leg
  south east leg
  north west leg
  north east leg
 Miguel the human (D)
  torso
   right arm
    right hand
     pinky
     ring finger
     middle finger
     index finger
     thumb
   left arm
    left hand
     pinky
     ring finger
     middle finger
     index finger
     thumb
 Lily the canine
  torso
   wagging tail
   spare mutant paw (D)
   left rear paw
   right rear paw
   left front paw
   right front paw
------- Testing Sizes (compare with above)----------- 
virtual (soft) size: 13
physical (hard) size: 30
------------ Collecting Garbage -------------------- 
found soft-deleted nodes? 1
immediate collect again? 0
--------- Hard Display after garb col ------------ 
room
 table
  south west leg
  south east leg
  north west leg
  north east leg
 Lily the canine
  torso
   wagging tail
   left rear paw
   right rear paw
   left front paw
   right front paw
Semi-deleted tree empty? 0

Completely-deleted tree empty? 1



Process exited with code: 0

---------------------------------------------------------------------------- */