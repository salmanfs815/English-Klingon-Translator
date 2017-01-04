/*
 * Entry.h
 *
 * Entry Class to be used in nodes of BST for assn3-cmpt225
 *
 * Authors: Salman Siddiqui and Raj Mahey
 * Date: 2016-07-05
 */

#pragma once
#include <string>
#include <iostream>

using namespace std;

class Entry
{
private:
	string english; //english version of word
	string klingon; //klingon version of word
public:
//**********************************************************//
				//Constructors!
//**********************************************************//

	//This is the default constructor, english and klingon remain unset
	Entry();

	//This constructor sets only the english word to engWord 
	Entry(string engWord);

	//This constructor accepts both an english word and its klingon conversion and sets both variables
	Entry(string engWord, string klingWord);

	//default destructor, doesnt do anything interesting
	~Entry();

//**********************************************************//
				//Getters and Setters!
//**********************************************************//
	//Gets the english version of this Entry objects "word"
	//PRE: English word is set!
	string getEnglish() const; 

	//Sets the english version of this Entry object "word"
	void setEnglish(string engWord);

	//Gets the klingon version of this Entry objects "word"
	//PRE: klingon word is set!
	string getKlingon() const;
	
	//Sets the klingon version of this Entry objects "word"
	void setKlingon(string klingWord);


//**********************************************************//
				//Overloaded operators!
//**********************************************************//

	//returns true if  rhs Entry objects english word is same as this 
	bool operator==(const Entry& rhs) const;

	//returns true if  rhs Entry objects english word is same as this 
	bool operator>(const Entry& rhs) const;

	bool operator<(const Entry& rhs) const;

	//prints: english:klingon 
	//PRE: english and klingon words are set!!!!
	//POST: n/a
	friend ostream& operator<<(ostream& os, const Entry& rhs);
};