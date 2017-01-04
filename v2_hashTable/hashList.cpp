//hash list class 
//Author: Raj Mahey
//DOC: June 30. 2016

#include "hashList.h"
#include <iostream>
using namespace std;

hashList::hashList()
{
	head = nullptr;
}

hashList::~hashList()
{
	node<Entry> * curr = head;
	node<Entry> * nextEl;
	while(curr!=nullptr)
	{
		nextEl = curr->next;
		delete curr;
		curr = nextEl;
	}
}

void hashList::insert(node<Entry>*toBeInserted)
{
	if(head == nullptr)
	{
		
		head = toBeInserted;
		return ;
	}
	node<Entry> * curr = head;
	while(curr->next!=nullptr)
	{
		curr = curr->next;
	}
	curr->next = toBeInserted;
	return ;

}

node<Entry>* hashList::lookup(string String)
{
	if(head == nullptr)
	{
		return nullptr;
	}
	node<Entry> * curr = head;
	if(curr==nullptr)
	{
		return nullptr;
	}
	while((curr->getData()).getEnglish()!=String)
	{
		if(curr->next==nullptr)
		{
			return nullptr;
		}
		curr = curr->next;
	}
	return curr;
}
