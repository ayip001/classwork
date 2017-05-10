#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

template <typename Object>
class Vector
{
public:
	explicit Vector(int initSize = 0) : theSize{ initSize },
		theCapacity{ initSize + SPARE_CAPACITY }
	{
		objects = new Object[theCapacity];
	}

	Vector(const Vector & rhs) : theSize{ rhs.theSize },
		theCapacity{ rhs.theCapacity }, objects{ nullptr }
	{
		objects = new Object[theCapacity];

		for( int k = 0; k < theSize; ++k )
			objects[k] = rhs.objects[k];
	}

	Vector & operator= (const Vector & rhs)
	{
		Vector copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	~Vector() { delete[] objects; }

	Vector(Vector && rhs) : theSize{ rhs.theSize },
		theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
	{
		rhs.objects = nullptr;
		rhs.theSize = 0;
		rhs.theCapacity = 0;
	}

	Vector & operator= (Vector && rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(objects, rhs.objects);
		return *this;
	}

	void resize(int newSize)
	{
		if( newSize > theCapacity )
			reserve(newSize * 2);
		theSize = newSize;
	}

	void reserve(int newCapacity)
	{
		if( newCapacity < theSize )
			return;

		Object *newArray = new Object[newCapacity];
		for( int k = 0; k < theSize; ++k )
			newArray[k] = std::move(objects[k]);

		theCapacity = newCapacity;
		std::swap(objects, newArray);
		delete[] newArray;
	}

	Object & operator[](int index) { return objects[index]; }
	const Object & operator[](int index) const { return objects[index]; }
	bool empty() const { return size() == 0; }
	int size() const { return theSize; }
	int capacity() const { return theCapacity; }

	void push_back(const Object & x)
	{
		if( theSize == theCapacity )
			reserve(2 * theCapacity + 1);
		objects[theSize++] = x;
	}

	void push_back(Object && x)
	{
		if( theSize == theCapacity )
			reserve(2 * theCapacity + 1);
		objects[theSize++] = std::move(x);

	}

	Object pop_back() { --theSize; return objects[theSize]; }
	const Object & back() const { return objects[theSize - 1]; }

	typedef Object * iterator;
	typedef const Object * const_iterator;

	iterator begin() { return &objects[0]; }
	const_iterator begin() const { return &objects[0]; }
	iterator end() { return &objects[size()]; }
	const_iterator end() const { return &objects[size()]; }
	static const int SPARE_CAPACITY = 16;

private:
	int theSize;
	int theCapacity;
	Object * objects;
};

template <typename Object>
class Stack
{
public:
    class OutOfBoundsException {};
    
	Stack() { V = Vector<Object>(); }
	void push(const Object& obj);
	Object pop();
	int getSize(){ return V.size(); }
	bool isEmpty(){ return V.size() == 0; }
	
private:
	Vector<Object> V;
};

template <typename Object>
void Stack<Object>::push(const Object& obj)
{
	V.push_back(obj);
}

template <typename Object>
Object Stack<Object>::pop()
{
	if (V.size() == 0)
		throw OutOfBoundsException();

	return V.pop_back();
}

int main()
{
	Stack<char> S;
	S.push('1');
	S.push('2');
	S.push('3');
	S.push('4');
	
	cout << "should be 4321: ";
	
	for(int i; i < 4; i++)
	    cout << S.pop();
	    
	S.push('4');
	S.push('3');
	S.push('2');
	S.push('1');
	
	cout << "\nshould be 1234: ";
	
	for(int i; i < 4; i++)
	    cout << S.pop();
	    
	S.push('1');
	S.push('2');
	S.push('3');
	
	cout << "\nshould be out of bound: ";
	
	try
	{
    	for(int i; i < 4; i++)
    	    cout << S.pop();
	}
	catch(Stack<char>::OutOfBoundsException)
	{
	    cout << " bound exception caught";
	}
	return 0;
}

/* ----------------------------- TEST -----------------------------------------

should be 4321: 4321
should be 1234: 1234
should be out of bound: 321 bound exception caught

Process exited with code: 0

---------------------------------------------------------------------------- */