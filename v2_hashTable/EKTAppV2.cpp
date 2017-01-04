/*
 * 
 *
 * Assignment 3 - CMPT 255 - Summer 2016
 *
 * Description: 
 *
 *
 * Authors: Salman Siddiqui and Raj Mahey
 *EKTAppV2.cpp
 * Date: 2016-07-05
 */

#include <iostream>
#include <fstream>
#include <string>
#include "HybridNode.h"
#include "node.h"
#include "BinarySearchTree.h"
#include "Entry.h"
#include "hash.h"

using namespace std;

//returns number of elements inserted into BST; -1 if failed
//PRE: bst BinarySearchTree is setup properly and initialized as <Entry> type. 
// Filename is the name of a discernable existing file with at least one word followed by its klingon translation
// in the structure "english:klingon\nenglish:klingon\n...english:klingon\nE0F"
int populate(BinarySearchTree<Entry>& bst, hashTable& hsh, const string& filename)
{
	ifstream myfile (filename); //open the file
	string line = ""; //initialize a string variable to blank
	if (myfile.is_open()) //make sure file is open
	{
		int count = 0; //initialize elements count to 0
		//cout << "Reading from file:" << endl; //flag to let user know reading from file  
		while ( getline (myfile,line) )
		{
			//cout << "reading line: " << line << endl; // for debugging purposes
			//int str_len = line.length(); //get the length of the line
			//cout << "line length: " << str_len << endl; // for debugging purposes
			int colon_pos = line.find(":"); //find colon in the line
			//cout << "colon pos: " << colon_pos << endl; // for debugging purposes
			string engWord(line,0,colon_pos); //set english word to what was left of colon
			//cout << "english word read: " << endl; // for debugging purposes
			string klingWord(line,colon_pos+1); //set klingon word to what was right of coon
			//cout << "klingon word read: " << endl; // for debugging purposes
			Entry newEntry(engWord,klingWord); //make a new Entry type with the english and klingon word
			//cout << "new entry created: " << newEntry << endl; // for debugging purposes
			HybridNode<Entry> * newHybridNode = new(nothrow) HybridNode<Entry>(newEntry);
			node<Entry> * newNode = new(nothrow) node<Entry>(newEntry);
			if(bst.search(newEntry) == nullptr && hsh.lookup(engWord) == nullptr) // make sure that newEntry isn't already in the bst or hsh
				bst.add(newHybridNode); //add this entry to the binary search tree
				hsh.insert(newNode);
			//cout << "new entry added to bst" << endl; // for debugging purposes
			count++; //increment the HybridNode variable
		}
		myfile.close(); //close the file
		//cout << "elements inserted: " << HybridNode << endl; // for debugging purposes
		return count;
	}
	else 
	{
		//cout << "Unable to open file" << endl; // for debugging purposes
		return -1;
	}
}

Entry translate(hashTable& hsh, string word) //translate Entry from klingon to english
{
	node<Entry>* translation = hsh.lookup(word);
	if ( translation != nullptr ) // word was found
		return translation->getData();
	else
		return Entry(word);
}

int main(int argc, char* argv[])
{

	//cout << "Starting program ..." << endl; // for debugging purposes

	const string dataFile = "dataFile.txt"; // data file for dictionary population

	// new BST for storing words
	BinarySearchTree<Entry> DictTree; // DictTree == Dictionary Tree
	hashTable DictTable; // DictTable == Dictionary Table

	//cout << "returned from BST constructor" << endl; // for debugging purposes

	populate(DictTree, DictTable, dataFile);
	//cout << "return from populate()" << endl; // for debugging purposes

	// if command line argument "display" was given; display then terminate
	if( argc >= 2 && (string)argv[1] == "display" )
	{
		cout << "display option selected: displaying ..." << endl; // for debugging purposes
		cout << DictTree;
		return 0;
	}

	cout << "begin reading stdin for word translation requests" << endl; // for debugging purposes

	// begin reading stdin and make array of words
	const int INIT_SIZE = 50;
	int capacity = INIT_SIZE; // current size of array
	Entry* translations = new Entry[INIT_SIZE];
	int i = 0;
	string engWord;
	while(getline(cin,engWord))
	{

		// resize if array is full
		if( i == capacity )
		{
			capacity *= 2; //double the capacity each time we exceed capacity (dynamic array)
			Entry* newArr = new Entry[capacity];
			for(int j=0; j<i; j++)
			{
				newArr[j] = translations[j];
			}
			delete[] translations;
			translations = newArr;
		}

		translations[i++] = translate(DictTable, engWord);
	}

	cout << "displaying translated words ..." << endl; // for debugging purposes
	// display translated words
	for(int j=0; j<i; j++) //display translated in O(n) where n is the amount of words to translate
	{
		cout << translations[j] << endl;
	}

	return 0;
}