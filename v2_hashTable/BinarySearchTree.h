// AVL TREE
/*
 * Authors: Salman Siddiqui and Raj Mahey
 * Date: 2016-07-09
 */

#include "HybridNode.h"
#include <iostream>
using namespace std;


template <class Type>
class BinarySearchTree //AVL TREE MODIFIED FROM ASSIGNMENT 3 -> Guarantee logn avg insertion
{

private:

	/* Private Attributes */
	HybridNode<Type>* rootPtr;

	/* Private Methods */
	HybridNode<Type>* insertInorder(HybridNode<Type>* subTreePtr, HybridNode<Type>* newNodePtr);
	HybridNode<Type>* removeValue(HybridNode<Type>* subTreePtr, Type target, bool& success);
	HybridNode<Type>* removeNode(HybridNode<Type>* nodePtr);
	HybridNode<Type>* removeLeftmostNode(HybridNode<Type>* nodePtr, Type& inorderSuccessor);
	HybridNode<Type>* findNode(HybridNode<Type>* subTreePtr, Type target);
	//Gets the height of the tree from the node sent, returns it
    int height(HybridNode<Type>* givenNode);

    //finds height difference between tree rooted at givenNode
    int difference(HybridNode<Type>* givenNode);


    //all avl rotations (rightright,rightleft,...)
    HybridNode<Type>* rrR(HybridNode<Type>* givenNode);
    HybridNode<Type>* rlR(HybridNode<Type>* givenNode);
    HybridNode<Type>* llR(HybridNode<Type>* givenNode);
    HybridNode<Type>* lrR(HybridNode<Type>* givenNode);

    //balance function
    HybridNode<Type>* balance(HybridNode<Type>*);

public:

	/* Contructors and Destructors */
	BinarySearchTree();
	~BinarySearchTree();

	/* Public Methods */
	bool add(HybridNode<Type>* newData);
	bool remove(Type target);
	HybridNode<Type>* search(Type target);


	/* for use by non-class functions such as operator<< */
	HybridNode<Type>* getRootPtr();

	void printInorder(HybridNode<Type>* subTreePtr);
	
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
HybridNode<Type>* BinarySearchTree<Type>::insertInorder(HybridNode<Type>* subTreePtr, HybridNode<Type>* newNodePtr)
{
	if ( subTreePtr == nullptr )
		return newNodePtr;
	else if ( subTreePtr->getData() > newNodePtr->getData() )
	{
		HybridNode<Type>* tempPtr = insertInorder(subTreePtr->getLeftChild(), newNodePtr);
		subTreePtr->setLeftChild(tempPtr);
		subTreePtr = balance(subTreePtr);
	}
	else
	{
		HybridNode<Type>* tempPtr = insertInorder(subTreePtr->getRightChild(), newNodePtr);
		subTreePtr->setRightChild(tempPtr);
		subTreePtr = balance(subTreePtr);
	}

	return subTreePtr;
}

// removes the given target from the binary search tree to which subTreePtr points
// returns a pointer to the node at this tree location after the value is removed
// sets success to true if the removal is successful, or false otherwise
template <class Type>
HybridNode<Type>* BinarySearchTree<Type>::removeValue(HybridNode<Type>* subTreePtr, Type target, bool& success)
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
		HybridNode<Type>* tempPtr = removeValue(subTreePtr->getLeftChild(), target, success);
		subTreePtr->setLeftChild(tempPtr);
		return subTreePtr;
	}
	else
	{
		// search the right subtree
		HybridNode<Type>* tempPtr = removeValue(subTreePtr->getRightChild(), target, success);
		subTreePtr->setRightChild(tempPtr);
		return subTreePtr;
	}
}

// removes the item in the node, N, to which nodePtr points
// return a pointer to the node at this tree location after node N is deleted
template <class Type>
HybridNode<Type>* BinarySearchTree<Type>::removeNode(HybridNode<Type>* nodePtr)
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
		HybridNode<Type>* tempPtr = removeLeftmostNode(nodePtr->getRightChild(), newNodeValue);
		nodePtr->setRightChild(tempPtr);
		nodePtr->setData(newNodeValue);
		return nodePtr;
	}
	else // N has only one child C
	{
		HybridNode<Type>* nodeToConnectPtr;

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
HybridNode<Type>* BinarySearchTree<Type>::removeLeftmostNode(HybridNode<Type>* nodePtr, Type& inorderSuccessor)
{
	if ( nodePtr->getLeftChild() == nullptr )
	{
		// this is the node you want: it has no left child, but it might have a right subtree
		inorderSuccessor = nodePtr->getData();
		return removeNode(nodePtr);
	}
	else
	{
		HybridNode<Type>* tempPtr = removeLeftmostNode(nodePtr->getLeftChild(), inorderSuccessor);
		nodePtr->setLeftChild(tempPtr);
		return nodePtr;
	}
}

// searches a binary search tree for a given target
// return pointer to node with target element, nullptr if not found
template <class Type>
HybridNode<Type>* BinarySearchTree<Type>::findNode(HybridNode<Type>* subTreePtr, Type target)
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
void BinarySearchTree<Type>::printInorder(HybridNode<Type>* subTreePtr)
{
	if( subTreePtr == nullptr )
		return;

	printInorder(subTreePtr->getLeftChild());

	cout << subTreePtr->getData() << endl;

	printInorder(subTreePtr->getRightChild());
}


/* Public Methods */

template <class Type>
bool BinarySearchTree<Type>::add(HybridNode<Type>* newData)
{
	rootPtr = insertInorder(rootPtr, newData);
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
HybridNode<Type>* BinarySearchTree<Type>::search(Type target)
{
	return findNode(rootPtr, target);
}


 //Gets the height of the tree from the node sent, returns it (max of the two subtrees l and r)
template <class Type>
int BinarySearchTree<Type>::height(HybridNode<Type>* givenNode)
{
    int currHeight = 0;
    if (givenNode != nullptr)
    {
		int leftH = height(givenNode->getLeftChild());
		int rightH = height(givenNode->getRightChild());
		int maxHeight = leftH>rightH?leftH:rightH;
		currHeight = maxHeight + 1;
    }
    return currHeight;
}


//finds height difference between tree rooted at givenNode
template <class Type>
int BinarySearchTree<Type>::difference(HybridNode<Type>* givenNode)
{
	int leftH = height(givenNode->getLeftChild());
	int rightH = height(givenNode->getRightChild());
    return (leftH - rightH);
}

//rightright Rotation
template <class Type>
HybridNode<Type>* BinarySearchTree<Type>::rrR(HybridNode<Type>* givenNode)
{
	if(givenNode==nullptr)
	{
		return nullptr;
	}

    HybridNode<Type>* temp = givenNode->getRightChild();
    if(temp==nullptr)
    {
    	return nullptr;
    }
    givenNode->setRightChild(temp->getLeftChild());
    temp->setLeftChild(givenNode);
    return temp;
}

//leftleft Rotation
template <class Type>
HybridNode<Type>* BinarySearchTree<Type>::llR(HybridNode<Type>* givenNode)
{
	if(givenNode==nullptr)
	{
		return nullptr;
	}
    HybridNode<Type>* temp = givenNode->getLeftChild();
    if(temp == nullptr)
    {
    	return nullptr;
    }
    givenNode->setLeftChild(temp->getRightChild());
    temp->setRightChild(givenNode);
    return temp;
}
 
//leftright rotation
template <class Type>
HybridNode<Type>* BinarySearchTree<Type>::lrR(HybridNode<Type>* givenNode)
{
	if(givenNode==nullptr)
	{
		return nullptr;
	}
    givenNode->setLeftChild(rrR(givenNode->getLeftChild()));
    return llR(givenNode);
}
 
//rghtleft rotation
template <class Type>
HybridNode<Type>* BinarySearchTree<Type>::rlR(HybridNode<Type>* givenNode)
{
	if(givenNode==nullptr)
	{
		return nullptr;
	}
    HybridNode<Type>* temp;
    temp = givenNode->getRightChild();
    givenNode->setRightChild(llR(temp));
    return rrR(givenNode);
}

//balance function
template <class Type>
HybridNode<Type>* BinarySearchTree<Type>::balance(HybridNode<Type>* givenNode)
{
    int bal = difference(givenNode);
    if (bal > 1)
    {
        if (difference(givenNode->getLeftChild()) > 0)
            givenNode = llR(givenNode);
        else
            givenNode = lrR(givenNode);
    }
    else if (bal < -1)
    {
        if (difference(givenNode->getRightChild()) > 0)
            givenNode = rlR(givenNode);
        else
            givenNode = rrR(givenNode);
    }
    return givenNode;
}

template <class Type>
HybridNode<Type>* BinarySearchTree<Type>::getRootPtr()
{
	return rootPtr;
}



template <typename Type>
ostream& operator<<(ostream& os, BinarySearchTree<Type>& rhs)
{
	rhs.printInorder(rhs.getRootPtr());
	return os;
}