/*
 * Entry.cpp
 *
 * Entry Class to be used in nodes of BST for assn3-cmpt225
 *
 * Authors: Salman Siddiqui and Raj Mahey
 * Date: 2016-07-05
 */

#include "Entry.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

/* private attributes:
string english;
string klingon;
*/


//This is the default constructor, english and klingon remain unset
Entry::Entry()
{
	english = "";
	klingon = "<not found>";
}


//This constructor sets only the english word to engWord 
Entry::Entry(string engWord)
{
	english = engWord;
	klingon = "<not found>";
}


//This constructor accepts both an english word and its klingon conversion and sets both variables
Entry::Entry(string engWord, string klingWord)
{
	english = engWord;
	klingon = klingWord;
}

//default destructor, doesnt do anything interesting
Entry::~Entry()
{

}


//Gets the english version of this Entry objects "word"
string Entry::getEnglish() const
{
	return english;
}

//Sets the english version of this Entry objects "word"
void Entry::setEnglish(string engWord)
{
	english = engWord;
}

//Gets the klingon version of this Entry objects "word"
string Entry::getKlingon() const
{
	return klingon;
}

//Sets the klingon version of this Entry objects "word"
void Entry::setKlingon(string klingWord)
{
	klingon = klingWord;
}



//returns true if  rhs Entry objects english word is same as this 
bool Entry::operator==(const Entry& rhs) const
{
	string word1 = english;
	string word2 = rhs.getEnglish();
	transform(word1.begin(), word1.end(), word1.begin(),::tolower);
	transform(word2.begin(), word2.end(), word2.begin(),::tolower);
	return word1.compare(word2) == 0;
}

//returns true if  rhs Entry objects english word is <= as this 
bool Entry::operator>(const Entry& rhs) const
{
	string word1 = english;
	string word2 = rhs.getEnglish();
	transform(word1.begin(), word1.end(), word1.begin(),::tolower);
	transform(word2.begin(), word2.end(), word2.begin(),::tolower);
	return word1.compare(word2) > 0;
}

//returns true if  rhs Entry objects english word is > same as this 
bool Entry::operator<(const Entry& rhs) const
{
	string word1 = english;
	string word2 = rhs.getEnglish();
	transform(word1.begin(), word1.end(), word1.begin(),::tolower);
	transform(word2.begin(), word2.end(), word2.begin(),::tolower);
	return word1.compare(word2) < 0;
}


//Outputs the entry objects english word, followed by a colon, followed by the klingon translation
ostream& operator<<(ostream& os, const Entry& rhs)
{
	os << rhs.getEnglish() << ":" << rhs.getKlingon();
	return os;
}