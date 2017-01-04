//Hash table class
//Author Raj Mahey
//Date of creation: June 30, 2016

#include "hash.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;



//constructor for when size is sent
hashTable::hashTable(int sentSize): 
	MAX_SIZE(sentSize)
{
	size = 0;
	table = new hashList[MAX_SIZE];
}


//sets max size to default max size (Default constructor)
hashTable::hashTable():
	MAX_SIZE(DEFAULT_MAX_SIZE)
{
	size = 0;
	table = new hashList[MAX_SIZE];
}

//default destructor
hashTable::~hashTable()
{
	delete[] table;
}


//This algorithm takes a string, and runs an algorithm on String to get a index within the bounds of [0,MAX_SIZE).
const int hashTable::hashAlgorithm(string String) const
{
	int len = String.length();
	int hashNumber = 3;
	if(len > 11580) //prevent overflow 
	{
		return len/31*String[17*String[len-77]] % MAX_SIZE; //hash algo to handle overflow
	}

	for(int i = 0; i < len; i++)
	{
		hashNumber += ((hashNumber << 5) - hashNumber + String[i]);
	}
	if(hashNumber<0)
	{
		hashNumber *= -1;
	}
	//cout << String << " :  " << hashNumber % MAX_SIZE << endl;
	return hashNumber % MAX_SIZE;

}
//PRE: 
//POST: inserts entry into some location as calculated by hashAlgorithm
//Invariant:
void hashTable::insert(node<Entry>* toBeInserted)
{
	if(table==nullptr)
	{
		return;
	}
	int index = hashAlgorithm((toBeInserted->getData()).getEnglish());
	if(index>MAX_SIZE)
	{
		return;
	}
	size++;
	return table[index].insert(toBeInserted);
}

//PRE: 
//POST:  inserts string into some location as calculated by hashAlgorithm
//Invariant:
node<Entry>* hashTable::lookup(string String) const
{
	int index = hashAlgorithm(String);
	return table[index].lookup(String);
	return nullptr;
}

