/*
 * PrecondViolatedExcep.h
 *
 * Class Description: Defines the exception that is thrown when a
 *					  precondition is violated.
 *
 * Authors: Salman Siddiqui, Raj Mahey
 */

#pragma once

#include <stdexcept>
#include <string>

using namespace std;

//A logic error is created 
class PrecondViolatedExcep : public logic_error
{
	public:
   		PrecondViolatedExcep(const string& message = "");  
};