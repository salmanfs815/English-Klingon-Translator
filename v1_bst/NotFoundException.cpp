/*
 * NotFoundException.h
 *
 * Class Description: Defines the exception that is thrown when a
 *					  requested element is not found in data collection ADT.
 *
 * Authors: Salman Siddiqui, Raj Mahey
 */


#include "NotFoundException.h"  

//A logic error is created 
// This logic error will accept a string and return a not found exception logic_error type
NotFoundException::NotFoundException(const string& message): 
logic_error("Not found exception: " + message)
{
} 