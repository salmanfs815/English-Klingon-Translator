//Hash table class
//Author Raj Mahey
//Date of creation: June 30, 2016
#pragma once
#include "hashList.h"
#include "node.h"
#include <iostream>
#include <string>
#include "Entry.h"

using namespace std;

class hashTable
{
private:
	hashList * table;
	const int DEFAULT_MAX_SIZE = 100; //default assigned size
	const int MAX_SIZE; //the max allocated size

	int size; //the elementcount/size current

	const int hashAlgorithm(string String) const; //algorithm to find position

public:
	hashTable(); //default constructor, size set to 0, max size DEFAULT_MAX_SIZE;
	hashTable(int sentSize); //constructor making table of size sentSize

	~hashTable();

	//PRE: 
	//POST: inserts entry into some location as calculated by hashAlgorithm
	//Invariant:
	void insert(node<Entry>* toBeInserted);

	//PRE: 
	//POST: inserts string into some location as calculated by hashAlgorithm
	//Invariant:
	node<Entry>* lookup(string String) const;

};