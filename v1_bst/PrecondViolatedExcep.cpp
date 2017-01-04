/*
 * PrecondViolatedExcep.h
 *
 * Class Description: Defines the exception that is thrown when a
 *					  precondition is violated.
 *
 * Authors: Salman Siddiqui, Raj Mahey
 */

#include "PrecondViolatedExcep.h"  

//A logic error is created 
PrecondViolatedExcep::PrecondViolatedExcep(const string& message): 
logic_error("Pre-condition violated exception: " + message)
{
}