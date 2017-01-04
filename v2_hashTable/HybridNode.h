/*
 * HybridNode.h
 *
 * Authors: Salman Siddiqui and Raj Mahey
 * Date: 2016-07-09
 */
#pragma once
#include <iostream>
using namespace std;

template <class Type>
class HybridNode
{

private:
	HybridNode<Type>* left; //left pointer (BST)
	HybridNode<Type>* right; //right pointer (BST)
	Type data;

public:
	HybridNode<Type>* next; //next pointer (LLT)

	/* Constructors and Destructors  */
	HybridNode();
	HybridNode(Type newData);
	HybridNode(Type newData, HybridNode<Type>* newLeftChild, HybridNode<Type>* newRightChild);
	~HybridNode();


	/* Getters and Setters */
	Type getData();
	bool setData(Type newData);

	HybridNode<Type>* getLeftChild();
	bool setLeftChild(HybridNode<Type>* newLeftChild);

	HybridNode<Type>* getRightChild();
	bool setRightChild(HybridNode<Type>* newRightChild);

};

/* Overloaded operators */
/*template <typename Type>
ostream& operator<<(ostream& os, const HybridNode<Type>& rhs);*/

/* Constructors and Destructors */
template <class Type>
HybridNode<Type>::HybridNode()
{
	left = nullptr;
	right = nullptr;
	next = nullptr;
}

template <class Type>
HybridNode<Type>::HybridNode(Type newData)
{
	left = nullptr;
	right = nullptr;
	next = nullptr;
	data = newData;
}

template <class Type>
HybridNode<Type>::HybridNode(Type newData, HybridNode<Type>* newLeftChild, HybridNode<Type>* newRightChild)
{
	left = newLeftChild;
	right = newRightChild;
	data = newData;
}

template <class Type>
HybridNode<Type>::~HybridNode()
{
	left = nullptr;
	right = nullptr;
	next = nullptr;

}


/* Getters and Setters */
template <class Type>
Type HybridNode<Type>::getData()
{
	return data;
}

template <class Type>
bool HybridNode<Type>::setData(Type newData)
{
	data = newData;
	return true;
}

template <class Type>
HybridNode<Type>* HybridNode<Type>::getLeftChild()
{
	return left;
}

template <class Type>
bool HybridNode<Type>::setLeftChild(HybridNode<Type>* newLeftChild)
{
	left = newLeftChild;
	return true;
}

template <class Type>
HybridNode<Type>* HybridNode<Type>::getRightChild()
{
	return right;
}

template <class Type>
bool HybridNode<Type>::setRightChild(HybridNode<Type>* newRightChild)
{
	right = newRightChild;
	return true;
}

template <typename Type>
ostream& operator<<(ostream& os, const HybridNode<Type>& rhs)
{
	os << rhs.getData();
	return os;
}