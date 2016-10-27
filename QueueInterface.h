/*****************************************************************************
Title:          QueueInterface.h
Author:     Nishad Sharker
Created on:     May 4, 2015
Description:    Header file for the interface for Queues
******************************************************************************/
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Listing 13-1.
 @file QueueInterface.h */

#ifndef TEACH235_QUEUE_QUEUEINTERFACE_H_
#define TEACH235_QUEUE_QUEUEINTERFACE_H_


template<class ItemType>
class QueueInterface

{
public:
   /** Sees whether this queue is empty.
    @return True if the queue is empty, or false if not. */
   virtual bool IsEmpty() const = 0;

   /** Adds a new entry to the back of this queue.
    @post If the operation was successful, newEntry is at the
       back of the queue.
    @param newEntry  The object to be added as a new entry.
    @return True if the addition is successful or false if not. */
   virtual bool Enqueue(const ItemType& newEntry) = 0;

   /** Removes the front of this queue.
    @post If the operation was successful, the front of the queue
       has been removed.
    @return True if the removal is successful or false if not. */
   virtual bool Dequeue() = 0;

   /** Returns the front of this queue.
    @pre The queue is not empty.
    @post The front of the queue has been returned, and the
       queue is unchanged.
    @return The front of the queue. */
   virtual ItemType PeekFront() const = 0;
}; // end QueueInterface
#endif  // TEACH235_QUEUE_QUEUEINTERFACE_H_
