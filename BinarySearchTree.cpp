//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file BinarySearchTree.cpp */
#include <iostream>

#include "BinarySearchTree.h"
#include "BinaryNode.h"
//#include "NotFoundException.h"
#include "NotFoundException.h"
#include <vector>
#include "LinkedQueue.h"//For LevelOrder
// template<class ItemType>
// BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& treePtr)
// {
//    root_ = this->copyTree(treePtr.root_); // Call inherited method
// }  // end copy constructor

template<class ItemType, class OtherType>
BinarySearchTree<ItemType, OtherType>::BinarySearchTree(const BinarySearchTree<ItemType, OtherType>& tree)
{
  root_ = CopyTree(tree.root_);
}  // end copy constructor

template<class ItemType, class OtherType>
BinarySearchTree<ItemType, OtherType>& BinarySearchTree<ItemType, OtherType>::operator=(const BinarySearchTree<ItemType, OtherType>& right_hand_side)
{

    if (this != &right_hand_side) {
        this->Clear();

        CopyTree(right_hand_side);

    }
  return *this;
  // COMPLETE ASSIGNMENT OPERATOR
}  // end operator=


template<class ItemType, class OtherType>
BinarySearchTree<ItemType, OtherType>::~BinarySearchTree()
{
   DestroyTree(root_);
}  // end destructor


template<class ItemType, class OtherType>
bool BinarySearchTree<ItemType, OtherType>::IsEmpty() const
{
   return root_ == nullptr;
}  // end isEmpty

template<class ItemType, class OtherType>
int BinarySearchTree<ItemType, OtherType>::GetHeight() const
{
   return GetHeightHelper(root_);
}  // end getHeight

template<class ItemType, class OtherType>
int BinarySearchTree<ItemType, OtherType>::GetNumberOfNodes() const
{
   return GetNumberOfNodesHelper(root_);
}  // end getNumberOfNodes

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Clear()
{
   DestroyTree(root_);
   root_ = nullptr;
}  // end clear

template<class ItemType, class OtherType>
bool BinarySearchTree<ItemType, OtherType>::Remove(const ItemType& target)
{

    bool success = false;
    RemoveValue(root_,target,success);
    return success;

}  // end remove

template<class ItemType, class OtherType>
OtherType BinarySearchTree<ItemType, OtherType>::GetOther(const ItemType& an_entry) const throw(NotFoundException)
{

  BinaryNode<ItemType, OtherType>* findItem;
  findItem = FindNode(root_,an_entry);
 if (findItem == nullptr)
  {
      throw NotFoundException("The entry was not found!");
  }


  return findItem->GetOther();

}  // end getEntry

template<class ItemType, class OtherType>
OtherType& BinarySearchTree<ItemType, OtherType>::GetOtherReference(const ItemType& an_entry) throw(NotFoundException)
{
  /**cout << "Incomplete GetOtherReference" << endl;



  return OtherType();***/
 BinaryNode<ItemType, OtherType>* findItem;
 findItem = FindNode(root_,an_entry);
 if (findItem == nullptr)
  {
      throw NotFoundException("The entry was not found!");
  }


  return findItem->GetOtherReference();
}  // end getEntry

template<class ItemType, class OtherType>
bool BinarySearchTree<ItemType, OtherType>:: Contains(const ItemType& an_entry) const
{
  BinaryNode<ItemType, OtherType>* findItem;
  findItem = FindNode(root_,an_entry);

  bool success = false;
  if (findItem != nullptr)
  {
      success = true;
  }

  return success;

}  // end contains





//BinaryNode<ItemType, OtherType> findWord(string userWord) const throw(NotFoundException)
template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>:: findWord(void visit(ItemType&,OtherType&), const ItemType& anItem) const throw(NotFoundException)
{
  bool found = Contains(anItem);

  if(found)
  {
      BinaryNode<ItemType, OtherType>* foundWord;
      foundWord = FindNode(root_,anItem);
      ItemType foundItem = foundWord->GetItem();
      OtherType foundOther = foundWord->GetOther();
      visit(foundItem,foundOther);
  }
  else
  {
      throw NotFoundException("Entry was not found!");
  }
}



template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::PreorderTraverse(void visit(ItemType&)) const
{
   Preorder(visit, root_);
}  // end preorderTraverse

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::InorderTraverse(void visit(ItemType&)) const
{
   Inorder(visit, root_);
}  // end inorderTraverse

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::PostorderTraverse(void visit(ItemType&)) const
{
   Postorder(visit, root_);
}  // end postorderTraverse

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::LevelorderTraverse(void visit(ItemType&)) const
{
   Levelorder(visit, root_);
}  // end LevelorderTraverse

//////////////////////////////////////////////////////////////
//// Overloaded Traversals
/////////////////////////////////////////////////////////////
template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::PreorderTraverse(void visit(ItemType&,OtherType&)) const
{
   Preorder(visit, root_);
}  // end preorderTraverse

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::InorderTraverse(void visit(ItemType&,OtherType&)) const
{
   Inorder(visit, root_);
}  // end inorderTraverse

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::PostorderTraverse(void visit(ItemType&,OtherType&)) const
{
   Postorder(visit, root_);
}  // end postorderTraverse

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::LevelorderTraverse(void visit(ItemType&,OtherType&)) const
{
   Levelorder(visit, root_);
}  // end LevelorderTraverse




//////////////////////////////////////////////////////////////
//      Protected Utility Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType, class OtherType>
int BinarySearchTree<ItemType, OtherType>::GetHeightHelper(BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr == nullptr)
      return 0;
   else
      return 1 + max(GetHeightHelper(node_ptr->GetLeftPtr()),
                     GetHeightHelper(node_ptr->GetRightPtr()));
}  // end GetHeightHelper

template<class ItemType, class OtherType>
int BinarySearchTree<ItemType, OtherType>::GetNumberOfNodesHelper(BinaryNode<ItemType, OtherType>* node_ptr) const
{
    if (node_ptr == nullptr)
      return 0;
   else
      return 1 + GetNumberOfNodesHelper(node_ptr->GetLeftPtr()) + GetNumberOfNodesHelper(node_ptr->GetRightPtr());
}  // end GetNumberOfNodesHelper


template<class ItemType, class OtherType>
bool BinarySearchTree<ItemType, OtherType>::Add(const ItemType& new_item, const OtherType& new_other)
{
   BinaryNode<ItemType, OtherType>* new_node = new BinaryNode<ItemType, OtherType>(new_item);
   new_node->SetOther(new_other);

   root_ = InsertInorder(root_, new_node);

   return true;
}  // end add


//////////////////////////////////////////////////////////////
//
//      Protected Utility Methods Section
//
//////////////////////////////////////////////////////////////

template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::InsertInorder(BinaryNode<ItemType, OtherType>* subTreePtr,
										      BinaryNode<ItemType, OtherType>* newNodePtr)
{

  if (subTreePtr == nullptr)
  {

      return newNodePtr;
  }
  else if(subTreePtr->GetItem() > newNodePtr->GetItem())
  {
      subTreePtr->SetLeftPtr(InsertInorder(subTreePtr->GetLeftPtr(), newNodePtr));
  }
  else
  {
      subTreePtr->SetRightPtr(InsertInorder(subTreePtr->GetRightPtr(), newNodePtr));
  }

  //if(subTreePtr->GetItem() < newNodePtr->GetItem())
  //BinaryNode<ItemType, OtherType>* new_node = new BinaryNode<ItemType, OtherType>;
  return subTreePtr;
}  // end insertInorder

template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::RemoveValue(BinaryNode<ItemType, OtherType>* subTreePtr,
										    const ItemType target,
										    bool& success)
{

    if(subTreePtr == nullptr)
    {
        success = false;
        return subTreePtr;
    }
    else if (subTreePtr->GetItem() == target)
    {
        subTreePtr = RemoveNode(subTreePtr);
        success = true;
        return subTreePtr;
    }
    else if(subTreePtr->GetItem() < target)
    {
        subTreePtr->SetRightPtr(RemoveValue(subTreePtr->GetRightPtr(), target, success));

    }
    else if(subTreePtr->GetItem() > target)
    {
        subTreePtr->SetLeftPtr(RemoveValue(subTreePtr->GetLeftPtr(), target, success));

    }
    return subTreePtr;


}  // end RemoveValue

template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::RemoveNode(BinaryNode<ItemType, OtherType>* nodePtr)
{
  //Case with no children
  if(nodePtr->GetLeftPtr() == nullptr && nodePtr->GetRightPtr() == nullptr)
  {
      //BinaryNode<ItemType, OtherType>* tempPtr;
      //tempPtr = nodePtr;
      delete nodePtr;
      nodePtr = nullptr;
      return nodePtr;
  }
  //Case with 1 child, the right child
  else if(nodePtr->GetLeftPtr() == nullptr)
  {
      BinaryNode<ItemType, OtherType>* tempPtr;
      tempPtr = nodePtr;
      nodePtr = nodePtr->GetRightPtr();
      delete tempPtr;
      tempPtr = nullptr;
      return nodePtr;
  }
  //Case with 1 child, the left child
  else if(nodePtr->GetRightPtr() == nullptr)
  {
      BinaryNode<ItemType, OtherType>* tempPtr;
      tempPtr = nodePtr;
      nodePtr = nodePtr->GetLeftPtr();
      delete tempPtr;
      tempPtr = nullptr;
      return tempPtr;
  }
  //Case with 2 children, need to find inorderSuccessor
  else
  {
      //BinaryNode<ItemType, OtherType>* tempPtr;
      ItemType successor = nodePtr->GetItem();
      OtherType otherSuccessor = nodePtr->GetOther();
      //tempPtr = RemoveLeftmostNode(nodePtr->GetRightPtr(), successor, otherSuccessor);
      nodePtr->SetRightPtr(RemoveLeftmostNode(nodePtr->GetRightPtr(), successor, otherSuccessor));
      nodePtr->SetItem(successor);
      nodePtr->SetOther(otherSuccessor);
      return nodePtr;
  }



}  // end RemoveNode

template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::RemoveLeftmostNode(BinaryNode<ItemType, OtherType>* nodePtr,
                                                                     ItemType& inorderSuccessor, OtherType& otherOfInorderSuccessor)
{

  if(nodePtr->GetLeftPtr() == nullptr)
  {
      inorderSuccessor = nodePtr->GetItem();
      otherOfInorderSuccessor = nodePtr->GetOther();
      return RemoveNode(nodePtr);

  }
  nodePtr->SetLeftPtr(RemoveLeftmostNode(nodePtr->GetLeftPtr(), inorderSuccessor, otherOfInorderSuccessor));
  return nodePtr;


}  // end RemoveLeftmostNode


template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::FindNode(BinaryNode<ItemType, OtherType>* subTreePtr,
                                                           const ItemType& target) const
{

  if(subTreePtr == nullptr)
  {
      return nullptr;
  }
  else if(subTreePtr->GetItem() == target)
  {
      return subTreePtr;
  }
  else if(subTreePtr->GetItem() > target)
  {
      return FindNode(subTreePtr->GetLeftPtr(),target);
  }
  else if(subTreePtr->GetItem() < target)
  {
      return FindNode(subTreePtr->GetRightPtr(),target);
  }

  return nullptr;


}  // end findNode

template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::CopyTree(const BinaryNode<ItemType, OtherType>* node_ptr) const
{
   BinaryNode<ItemType, OtherType>* new_tree_ptr = nullptr;
   // Copy tree nodes during a preorder traversal
   if (node_ptr != nullptr) {
     // Copy node
     new_tree_ptr = new BinaryNode<ItemType, OtherType>(node_ptr->GetItem());
     new_tree_ptr->SetOther(node_ptr->GetOther());

     new_tree_ptr->SetLeftPtr(CopyTree(node_ptr->GetLeftPtr()));
     new_tree_ptr->SetRightPtr(CopyTree(node_ptr->GetRightPtr()));
   }  // end if
   return new_tree_ptr;
}  // end copyTree

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::DestroyTree(BinaryNode<ItemType, OtherType>* node_ptr)
{
   if (node_ptr != nullptr) {
      DestroyTree(node_ptr->GetLeftPtr());
      DestroyTree(node_ptr->GetRightPtr());
      delete node_ptr;
   }  // end if
}  // end destroyTree

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Preorder(void visit(ItemType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      ItemType theItem = node_ptr->GetItem();
      visit(theItem);
      Preorder(visit, node_ptr->GetLeftPtr());
      Preorder(visit, node_ptr->GetRightPtr());
   }  // end if
}  // end preorder

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Inorder(void visit(ItemType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      Inorder(visit, node_ptr->GetLeftPtr());
      ItemType theItem = node_ptr->GetItem();
      visit(theItem);
      Inorder(visit, node_ptr->GetRightPtr());
   }  // end if
}  // end inorder

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Postorder(void visit(ItemType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      Postorder(visit, node_ptr->GetLeftPtr());
      Postorder(visit, node_ptr->GetRightPtr());
      ItemType theItem = node_ptr->GetItem();
      visit(theItem);
   } // end if
}  // end postorder

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Levelorder(void visit(ItemType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      LinkedQueue<BinaryNode<ItemType, OtherType>* > nodeQue;
      nodeQue.Enqueue(node_ptr);
      while(!nodeQue.IsEmpty())
      {
          BinaryNode<ItemType, OtherType>* current = nodeQue.PeekFront();
          ItemType theItem = current->GetItem();
          visit(theItem);
          if(current->GetLeftPtr() != nullptr)
          {
              nodeQue.Enqueue(current->GetLeftPtr());
          }
          if(current->GetRightPtr() != nullptr)
          {
              nodeQue.Enqueue(current->GetRightPtr());
          }
          nodeQue.Dequeue();
      }

   } // end if
}  // end postorder







//----------------------------------------
// Overloaded Traversals
//----------------------------------------
template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Preorder(void visit(ItemType&,OtherType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      ItemType theItem = node_ptr->GetItem();
      OtherType otherItem = node_ptr->GetOther();
      visit(theItem,otherItem);
      Preorder(visit, node_ptr->GetLeftPtr());
      Preorder(visit, node_ptr->GetRightPtr());
   }  // end if
}  // end preorder

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Inorder(void visit(ItemType&,OtherType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      Inorder(visit, node_ptr->GetLeftPtr());
      ItemType theItem = node_ptr->GetItem();
      OtherType otherItem = node_ptr->GetOther();
      visit(theItem,otherItem);
      Inorder(visit, node_ptr->GetRightPtr());
   }  // end if
}  // end inorder

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Postorder(void visit(ItemType&,OtherType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      Postorder(visit, node_ptr->GetLeftPtr());
      Postorder(visit, node_ptr->GetRightPtr());
      ItemType theItem = node_ptr->GetItem();
      OtherType otherItem = node_ptr->GetOther();
      visit(theItem,otherItem);
   } // end if
}  // end postorder

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Levelorder(void visit(ItemType&,OtherType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      LinkedQueue<BinaryNode<ItemType, OtherType>* > nodeQue;
      nodeQue.Enqueue(node_ptr);
      while(!nodeQue.IsEmpty())
      {
          BinaryNode<ItemType, OtherType>* current = nodeQue.PeekFront();
          ItemType theItem = current->GetItem();
          OtherType otherItem = current->GetOther();
          visit(theItem,otherItem);
          if(current->GetLeftPtr() != nullptr)
          {
              nodeQue.Enqueue(current->GetLeftPtr());
          }
          if(current->GetRightPtr() != nullptr)
          {
              nodeQue.Enqueue(current->GetRightPtr());
          }
          nodeQue.Dequeue();
      }

   } // end if
}  // end postorder





