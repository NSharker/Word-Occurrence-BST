/*****************************************************************************
Title:          main.cpp
Author:         Nishad Sharker
Created on:     May 22, 2015
Description:    Creates a binary search tree of words from a document
******************************************************************************/

#include <iostream>
#include <string>
#include <fstream> //Opening and closing the word document
#include <cctype> //converting characters to lower case
#include <cstring> //pull out words from a string, strtok
#include <cstdlib>

#include "BinarySearchTree.h"  // ADT binary tree operations
#include "LinkedQueue.h" //Linked Queue operations
using namespace std;



//This will be used to display the Word, the number of occurrence and then listing all the occurences
void display(string& anItem,LinkedQueue<int>& otherItem)
{
   cout << anItem << " :: " << "Count: " << otherItem.getQueCounter() << " Lines: " << otherItem << endl;
   //cout << otherItem << endl;
}  // end display


int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        cerr << "The number of arguments provided is incorrect! Closing program.\n";
        exit(1);
    }
    //Opening user identified word document
    ifstream inStream;
    inStream.open(argv[1]);

    if(inStream.fail())
    {
        cerr << "Input file could not be opened! Closing program.\n";
        exit(1);
    }


    BinarySearchTree<string,LinkedQueue<int> > binary_tree;
    vector<string> wordList;


    int lineCounter = 0;
    string full_line;

    //Going to get each line and filter out any none letter characters
    while (getline(inStream,full_line))
    {
        lineCounter++;
        char *lineStr;
        int lineLength = full_line.length();
        //Add 1 to lineLength so that we can add the '\0' to the end
        lineStr = new char[lineLength+1];

        for(int index = 0; index < lineLength; index++)
        {
            lineStr[index] = full_line[index];
        }

        //Adding null character to end the cstring
        lineStr[lineLength] = '\0';

        char* word;
        word = strtok(lineStr," ,.-!?0123456789\"");

        while(word != nullptr)
        {
            int wordLength = strlen(word);
            //Convert the words to lower case letters
            for(int index = 0; index < wordLength; index++)
            {
                word[index] = tolower(word[index]);
            }

            //Check BST if word is in it
            bool inTree;
            inTree = binary_tree.Contains(word);

            //If word avaliable then Enqueue the line Counter
            if(inTree == true)
            {
                binary_tree.GetOtherReference(word).Enqueue(lineCounter);

            }
            //If word not in tree add word and enqueue line counter
            else
            {
                LinkedQueue<int> lineQue;
                lineQue.Enqueue(lineCounter);
                binary_tree.Add(word,lineQue);
                //We will want to search all the words later for maximum occurence.
                wordList.push_back(word);

            }


            word = strtok(nullptr," ,.-!?0123456789");
        }

    }

try{


   cout << "Tree 1 Inorder: \n";
   binary_tree.InorderTraverse(display);

   //Print total number of nodes in Tree
   cout << "Total number of nodes in tree :" << binary_tree.GetNumberOfNodes() << endl;

   //Print out hieght of the tree.
   cout << "Height of the tree is : " << binary_tree.GetHeight() << endl;

   //Testing max occurrence display function


    // We make a second vector of all the addresses of the que so we can check their counters for the max
    vector<LinkedQueue<int>> lineList;
    int wordListSize = wordList.size();
    for(int i = 0; i < wordListSize; i++)
    {
        lineList.push_back(binary_tree.GetOtherReference(wordList[i]));
    }

    int maxOccPos = 0;
    for(int i = 0; i < wordListSize; i++)
    {
        if(lineList[maxOccPos].getQueCounter() < lineList[i].getQueCounter())
        {
            maxOccPos = i;
        }
    }

    cout << "The word with the maximum occurrence is: " << wordList[maxOccPos] << endl;
    cout << "Count: " << lineList[maxOccPos].getQueCounter() << endl;
    cout << "On the lines: " << lineList[maxOccPos] << endl;


    //Asking the user to input a word so we can output it
    string userInput;

    cout << "Enter a word that you want to find in the tree: ";
    cin >> userInput;

    binary_tree.findWord(display,userInput);


    /*********************
    // Extra Credit
    *********************/

    //Displaying the tree in Levelorder
    cout << "Displaying tree in levelorder: " << endl;
    binary_tree.LevelorderTraverse(display);



    //Removing a value from the tree
    string userDelete;
    cout << "Enter a word that you want to delete in the tree: ";
    cin >> userDelete;
    bool itemDeleted = binary_tree.Remove(userDelete);
    if(itemDeleted)
    {
        cout << "Word was deleted, the Contains() function on the word returns: " <<binary_tree.Contains(userDelete) << endl;
        cout << "Displaying tree again:" << endl;
        binary_tree.InorderTraverse(display);
    }
    else
    {
        cout << "Word was not deleted.";
    }





} catch (NotFoundException an_exception)
{
    cout << an_exception.what() << endl;
} catch (PreconditionViolatedException an_exception)
{
    cout << an_exception.what() << endl;
}




    //Closing our word document
    inStream.close();

    return 0;
} //end main

