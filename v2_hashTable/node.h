//Llt Node 
//node.h
//Raj Mahey
//July 30th 16


/*
 * node.h
 *
 * Authors: Salman Siddiqui and Raj Mahey
 * Date: 2016-07-09
 */
#pragma once
#include <iostream>
using namespace std;

template <class Type>
class node
{

private:
	node<Type>* left; //left pointer (BST)
	node<Type>* right; //right pointer (BST)
	Type data;

public:
	node<Type>* next; //next pointer (LLT)

	/* Constructors and Destructors  */
	node();
	node(Type newData);
	node(Type newData, node* sent);
	~node();


	/* Getters and Setters */
	Type getData();
	bool setData(Type newData);

};

/* Overloaded operators */
/*template <typename Type>
ostream& operator<<(ostream& os, const node<Type>& rhs);*/

/* Constructors and Destructors */
template <class Type>
node<Type>::node()
{
	left = nullptr;
	next = nullptr;
}

template <class Type>
node<Type>::node(Type newData)
{
	next = nullptr;
	data = newData;
}
template <class Type>
node<Type>::node(Type newData, node* sent)
{
	if(sent!=nullptr)
	{
	next = sent;	
	}	
	data = newData;
}
template <class Type>
node<Type>::~node()
{
	next = nullptr;

}

/* Getters and Setters */
template <class Type>
Type node<Type>::getData()
{
	return data;
}

template <class Type>
bool node<Type>::setData(Type newData)
{
	data = newData;
	return true;
}

template <typename Type>
ostream& operator<<(ostream& os, const node<Type>& rhs)
{
	os << rhs.getData();
	return os;
}