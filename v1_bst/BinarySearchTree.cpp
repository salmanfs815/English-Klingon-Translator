/*
 * BinarySearchTree.cpp
 *
 * Inspired by: Walls and Mirrors, Section 16.3
 *
 * Authors: Salman Siddiqui and Raj Mahey
 * Date: 2016-07-09
 */

#include "BinarySearchTree.h"
#include "BinaryNode.h"
#include <iostream>
using namespace std;

/* Private Attributes:
	BinaryNode<Type>* rootPtr; */


/* Constructors and Destructors */

template <class Type>
BinarySearchTree<Type>::BinarySearchTree()
{
	rootPtr = nullptr;
}

template <class Type>
BinarySearchTree<Type>::~BinarySearchTree()
{
	while( rootPtr != nullptr )
	{
		rootPtr = removeNode(rootPtr);
	}
}


/* Private Methods */

// inserts a new item into the binary search tree to which subTreePtr points
template <class Type>
BinaryNode<Type>* BinarySearchTree<Type>::insertInorder(BinaryNode<Type>* subTreePtr, BinaryNode<Type>* newNodePtr)
{
	if ( subTreePtr == nullptr )
		return newNodePtr;
	else if ( subTreePtr->getData() >= newNodePtr->getData() )
	{
		BinaryNode<Type>* tempPtr = insertInorder(subTreePtr->getLeftChild(), newNodePtr);
		subTreePtr->setLeftChild(tempPtr);
	}
	else
	{
		BinaryNode<Type>* tempPtr = insertInorder(subTreePtr->getRightChild(), newNodePtr);
		subTreePtr->setRightChild(tempPtr);
	}
	return subTreePtr;
}

// removes the given target from the binary search tree to which subTreePtr points
// returns a pointer to the node at this tree location after the value is removed
// sets success to true if the removal is successful, or false otherwise
template <class Type>
BinaryNode<Type>* BinarySearchTree<Type>::removeValue(BinaryNode<Type>* subTreePtr, Type target, bool& success)
{
	if ( subTreePtr == nullptr )
	{
		success = false;
		return nullptr;
	}
	else if ( subTreePtr->getData() == target )
	{
		// item is the root of some subtree
		subTreePtr = removeNode(subTreePtr); // remove the item
		success = true;
		return subTreePtr;
	}
	else if ( subTreePtr->getData() >= target )
	{
		// search the left subtree
		BinaryNode<Type>* tempPtr = removeValue(subTreePtr->getLeftChild(), target, success);
		subTreePtr->setLeftChild(tempPtr);
		return subTreePtr;
	}
	else
	{
		// search the right subtree
		BinaryNode<Type>* tempPtr = removeValue(subTreePtr->getRightChild(), target, success);
		subTreePtr->setRightChild(tempPtr);
		return subTreePtr;
	}
}

// removes the item in the node, N, to which nodePtr points
// return a pointer to the node at this tree location after node N is deleted
template <class Type>
BinaryNode<Type>* BinarySearchTree<Type>::removeNode(BinaryNode<Type>* nodePtr)
{
	if ( nodePtr->getLeftChild() == nullptr && nodePtr->getRightChild() == nullptr ) // N is a leaf
	{
		// remove leaf from the tree
		delete nodePtr;
		nodePtr = nullptr;
		return nodePtr;
	}
	else if ( nodePtr->getLeftChild() != nullptr && nodePtr->getRightChild() != nullptr ) // N has 2 children
	{
		// find the inorder successor of the entry in N: it is in the left subtree rooted at N's right child
		Type newNodeValue;
		BinaryNode<Type>* tempPtr = removeLeftmostNode(nodePtr->getRightChild(), newNodeValue);
		nodePtr->setRightChild(tempPtr);
		nodePtr->setData(newNodeValue);
		return nodePtr;
	}
	else // N has only one child C
	{
		if ( nodePtr->getLeftChild() != nullptr ) // C is a left child
			BinaryNode<Type>* nodeToConnectPtr = nodePtr->getLeftChild();
		else
		{
			BinaryNode<Type>* nodeToConnectPtr = nodePtr->getRightChild();
			delete nodePtr;
			nodePtr = nullptr;
			return nodeToConnectPtr;
		}
	}
}

// removes the leftmost node in the left subtree of the node pointed to by nodePtr
// sets the inorderSuccessor to the value in this node
// returns a pointer to the revised subtree
template <class Type>
BinaryNode<Type>* BinarySearchTree<Type>::removeLeftmostNode(BinaryNode<Type>* nodePtr, Type& inorderSuccessor)
{
	if ( nodePtr->getLeftChild() == nullptr )
	{
		// this is the node you want: it has no left child, but it might have a right subtree
		inorderSuccessor = nodePtr->getData();
		return removeNode(nodePtr);
	}
	else
		return removeLeftmostNode(nodePtr->getLeftChild(), inorderSuccessor);
}

// searches a binary search tree for a given target
// return pointer to node with target element
template <class Type>
BinaryNode<Type>* BinarySearchTree<Type>::findNode(BinaryNode<Type>* subTreePtr, Type target)
{
	if ( subTreePtr == nullptr )
		return nullptr; // not found
	else if ( subTreePtr->getData() == target )
		return subTreePtr; // found
	else if ( subTreePtr->getData() >= target )
		return findNode(subTreePtr->getLeftChild(), target); // search left subtree
	else
		return findNode(subTreePtr->getRightChild(), target); // search right subtree
}


/* Public Methods */

template <class Type>
bool BinarySearchTree<Type>::add(const Type& newData)
{
	BinaryNode<Type>* newNodePtr = new BinaryNode<Type>(newData);
	rootPtr = insertInorder(rootPtr, newNodePtr);
	return true;
}

template <class Type>
bool BinarySearchTree<Type>::remove(Type target)
{
	bool success = false;
	rootPtr = removeValue(rootPtr, target, success);
	return success;
}

template <class Type>
BinaryNode<Type>* BinarySearchTree<Type>::search(Type target)
{
	return findNode(rootPtr, target);
}

template <class Type>
BinaryNode<Type>* BinarySearchTree<Type>::getRootPtr()
{
	return rootPtr;
}

template <typename Type>
ostream& operator<<(ostream& os, const BinarySearchTree<Type> rhs)
{
	BinaryNode<Type>* curr = rhs.getRootPtr();
	while( curr != nullptr )
		os << curr.getLeftChild() << curr.getData() << curr.getRightChild();
	return os;
}