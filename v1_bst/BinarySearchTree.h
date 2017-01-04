/*
 * BinarySearchTree.h
 *
 * Authors: Salman Siddiqui and Raj Mahey
 * Date: 2016-07-09
 */

#include "BinaryNode.h"
#include <iostream>
using namespace std;


template <class Type>
class BinarySearchTree
{

private:

	/* Private Attributes */
	BinaryNode<Type>* rootPtr;

	/* Private Methods */
	BinaryNode<Type>* insertInorder(BinaryNode<Type>* subTreePtr, BinaryNode<Type>* newNodePtr);
	BinaryNode<Type>* removeValue(BinaryNode<Type>* subTreePtr, Type target, bool& success);
	BinaryNode<Type>* removeNode(BinaryNode<Type>* nodePtr);
	BinaryNode<Type>* removeLeftmostNode(BinaryNode<Type>* nodePtr, Type& inorderSuccessor);
	BinaryNode<Type>* findNode(BinaryNode<Type>* subTreePtr, Type target);

public:

	/* Contructors and Destructors */
	BinarySearchTree();
	~BinarySearchTree();

	/* Public Methods */
	bool add(const Type& newData);
	bool remove(Type target);
	BinaryNode<Type>* search(Type target);

	/* for use by non-class functions such as operator<< */
	BinaryNode<Type>* getRootPtr();
	void printInorder(BinaryNode<Type>* subTreePtr);
	
};

/* Overloaded Operators */
/*template <typename Type>
ostream& operator<<(ostream& os, const BinarySearchTree<Type> rhs);*/

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
	else if ( subTreePtr->getData() > newNodePtr->getData() )
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
	else if ( subTreePtr->getData() > target )
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
		BinaryNode<Type>* nodeToConnectPtr;

		if ( nodePtr->getLeftChild() != nullptr ) // C is a left child
			nodeToConnectPtr = nodePtr->getLeftChild();
		else
			nodeToConnectPtr = nodePtr->getRightChild();

		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
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
	{
		BinaryNode<Type>* tempPtr = removeLeftmostNode(nodePtr->getLeftChild(), inorderSuccessor);
		nodePtr->setLeftChild(tempPtr);
		return nodePtr;
	}
}

// searches a binary search tree for a given target
// return pointer to node with target element, nullptr if not found
template <class Type>
BinaryNode<Type>* BinarySearchTree<Type>::findNode(BinaryNode<Type>* subTreePtr, Type target)
{
	if ( subTreePtr == nullptr )
		return nullptr; // not found
	else if ( subTreePtr->getData() == target )
		return subTreePtr; // found
	else if ( subTreePtr->getData() > target )
		return findNode(subTreePtr->getLeftChild(), target); // search left subtree
	else
		return findNode(subTreePtr->getRightChild(), target); // search right subtree
}

template <class Type>
void BinarySearchTree<Type>::printInorder(BinaryNode<Type>* subTreePtr)
{
	if( subTreePtr == nullptr )
		return;

	printInorder(subTreePtr->getLeftChild());

	cout << subTreePtr->getData() << endl;

	printInorder(subTreePtr->getRightChild());
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
ostream& operator<<(ostream& os, BinarySearchTree<Type>& rhs)
{
	rhs.printInorder(rhs.getRootPtr());
	return os;
}