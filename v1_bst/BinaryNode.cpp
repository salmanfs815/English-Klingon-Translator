/*
 * BinaryNode.cpp
 *
 * Authors: Salman Siddiqui and Raj Mahey
 * Date: 2016-07-09
 */

#include "BinaryNode.h"
#include <iostream>
using namespace std;

/* 
private attributes:
	BinaryNode<Type>* left;
	BinaryNode<Type>* right;
	Type data;
*/


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
