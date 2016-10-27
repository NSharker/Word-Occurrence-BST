/*****************************************************************************
Title:          PreconditionViolatedException.cpp
Author:     Nishad Sharker
Created on:     May 4, 2015
Description:    Implementation of precondition violations
******************************************************************************/
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Listing 7-6.
    @file PrecondViolatedExcep.cpp */
#include "PreconditionViolatedException.h"

PreconditionViolatedException::PreconditionViolatedException(const string& message): logic_error("Precondition Violated Exception: " + message)
{
}  // end constructor

// End of implementation file.

