//Author: Raj Mahey
//This header file defines hashList
//Hash list a collision prevention mechanism, designed as a linked list
//Hash list uses nodes
//DOC: June 30. 2016

#include "Entry.h"
#include "node.h"
#pragma once


class hashList
{

private:
	node<Entry>* head = nullptr;

public:
	hashList();
	~hashList();

	//inserts given node into location neccesitated
	void insert(node<Entry>* toBeInserted);

	//searches the linked list for the string specified within some data type in the node
	node<Entry>* lookup(string String);
};