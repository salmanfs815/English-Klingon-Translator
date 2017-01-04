/*
 * BinaryNode.h
 *
 * Authors: Salman Siddiqui and Raj Mahey
 * Date: 2016-07-09
 */

#include <iostream>
using namespace std;

template <class Type>
class BinaryNode
{

private:
	BinaryNode<Type>* left;
	BinaryNode<Type>* right;
	Type data;

public:

	/* Constructors and Destructors  */
	BinaryNode();
	BinaryNode(Type newData);
	BinaryNode(Type newData, BinaryNode<Type>* newLeftChild, BinaryNode<Type>* newRightChild);
	~BinaryNode();


	/* Getters and Setters */
	Type getData();
	bool setData(Type newData);

	BinaryNode<Type>* getLeftChild();
	bool setLeftChild(BinaryNode<Type>* newLeftChild);

	BinaryNode<Type>* getRightChild();
	bool setRightChild(BinaryNode<Type>* newRightChild);

};

/* Overloaded operators */
/*template <typename Type>
ostream& operator<<(ostream& os, const BinaryNode<Type>& rhs);*/

/* Constructors and Destructors */
template <class Type>
BinaryNode<Type>::BinaryNode()
{
	left = nullptr;
	right = nullptr;
}

template <class Type>
BinaryNode<Type>::BinaryNode(Type newData)
{
	left = nullptr;
	right = nullptr;
	data = newData;
}

template <class Type>
BinaryNode<Type>::BinaryNode(Type newData, BinaryNode<Type>* newLeftChild, BinaryNode<Type>* newRightChild)
{
	left = newLeftChild;
	right = newRightChild;
	data = newData;
}

template <class Type>
BinaryNode<Type>::~BinaryNode()
{
	left = nullptr;
	right = nullptr;
}


/* Getters and Setters */
template <class Type>
Type BinaryNode<Type>::getData()
{
	return data;
}

template <class Type>
bool BinaryNode<Type>::setData(Type newData)
{
	data = newData;
	return true;
}

template <class Type>
BinaryNode<Type>* BinaryNode<Type>::getLeftChild()
{
	return left;
}

template <class Type>
bool BinaryNode<Type>::setLeftChild(BinaryNode<Type>* newLeftChild)
{
	left = newLeftChild;
	return true;
}

template <class Type>
BinaryNode<Type>* BinaryNode<Type>::getRightChild()
{
	return right;
}

template <class Type>
bool BinaryNode<Type>::setRightChild(BinaryNode<Type>* newRightChild)
{
	right = newRightChild;
	return true;
}

template <typename Type>
ostream& operator<<(ostream& os, const BinaryNode<Type>& rhs)
{
	os << rhs.getData();
	return os;
}