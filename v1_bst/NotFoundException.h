/*
 * NotFoundException.h
 *
 * Class Description: Defines the exception that is thrown when a
 *					  requested element is not found in data collection ADT.
 *
 * Authors: Salman Siddiqui, Raj Mahey
 */

#pragma once

#include <stdexcept>
#include <string>

using namespace std;

//A logic error is created 
class NotFoundException : public logic_error
{
	public:
   		NotFoundException(const string& message = "");  
};