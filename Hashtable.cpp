#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Hashtable.h"
#include <cmath>
#include <vector>
#include<cstdio>


    Hashtable::Hashtable()
    {
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            tbl[i] = NULL;//Initialize each pointer in the array of the table to NULL
        }
    }

    void Hashtable::add(string words, int fileIdx)
    {
        int index = hash(words);//Get the hash value to get the proper index to add at
        HashNode * temp = new HashNode;//Create a new node for the new data to be added
        temp->key = words;
        temp->fileIdx = fileIdx;
        temp->next = NULL;

        HashNode * iter = tbl[index];//Go through the LinkedList at the index and make sure the key-value pair is not already there. If it is, dont do anything
        bool alreadyInLinkedList = false;
        while(iter != NULL)
        {
            if(temp->key == iter->key && temp->fileIdx == iter->fileIdx)
            {
                alreadyInLinkedList = true;
                break;
            }
            iter = iter->next;
        }
        if(!alreadyInLinkedList)//If the pair is not there, add it to the LinkedList
        {
            temp->next = tbl[index];
            tbl[index] = temp;
        }
    }

    int Hashtable::hash(string s)
    {
        signed int sum = 0;
        for(int i = 0; i < s.length(); i++)//For each letter, starting at the back, multiply it by 7^i
        {
            int comp1 = s.size() - i - 1;
            int comp2 = static_cast<char>(s[comp1]);
            int temp = comp2 * pow(7,i);

            if(sum + temp< 0)//If the number will cause overflow, then divide it by 4 and then add it so that overflow doesnt occur
            {
                sum = sum / 4;
                temp = (static_cast<char>(s[s.size()-i-1]));
                sum = sum + temp;
            } else{
                sum = sum + temp; //If the addition doesnt cause overflow, then just add the hashed value to the hashed sum value
            }
        }
        int result = sum % TABLE_SIZE;//Mod the sum by the Table Size to get it within the bounds of the table
        if(result < 0)//If we get a negative value, then make it positive (absolute value function)
        {
            result = result * -1;
        }

        return result;//Return this number
    }

    void Hashtable::checkDuplicates()//Function to print out all duplicates in the Hashtable (Used ONLY for debugging the  Lab!)
    {
        vector<string> fNames;
        for(int i = 0; i < TABLE_SIZE; i++)
        {
             if(tbl[i] != NULL)
             {
                 HashNode * temp = tbl[i];
                 HashNode * prev = tbl[i];
                 while(temp != NULL)
                 {
                     prev = temp->next;
                     while(prev != NULL)
                     {
                        if(temp->key == prev->key && temp->fileIdx != prev->fileIdx)
                        {
                            cout << "MATCHED \"" << temp->key << "\" FROM FILES " << temp->fileIdx  << " AND " << prev->fileIdx << "\n";
                        }
                        prev = prev->next;
                     }
                     temp = temp->next;


                 }
             }
        }
    }

void Hashtable::getDuplicates (int numFiles, vector< vector<int> > &duplicates)//Gets all the duplicates of the array and adds the sum into the duplicates vector at the indices for the respective files
{

    for(int i = 0; i < numFiles; i++){
        for(int j = 0; j < numFiles;  j++)
        {
            duplicates[i][j] = 0;//Initialize all points in the matrix to 0
        }
    }


    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(tbl[i] != NULL)
        {
            HashNode * temp = tbl[i];
            HashNode * prev = tbl[i];
            while(temp != NULL)//Go through each node
            {
                prev = temp->next;
                while(prev != NULL)//Go through each node after this node and check if it is the same key (string of words) but different doc (file index in the files array)
                {
                    if(temp->key == prev->key && temp->fileIdx != prev->fileIdx)
                    {
                        //cout << "MATCHED \"" << temp->key << "\" FROM FILES " << temp->fileIdx  << " AND " << prev->fileIdx << "\n";
                        duplicates[temp->fileIdx-2][prev->fileIdx-2]++;//If it is a duplicate (same string in two different files) then increment the count of similarities for that file-intersection's index
                    }
                    prev = prev->next;//Move prev over until you get to the end of the linked list
                }
                temp = temp->next;//Move temp over until you get to the end of the linked list


            }
        }
    }

}

Hashtable::~Hashtable()//Goes through linked list and destructs every node that was allocated dynamically
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode * temp = tbl[i];
        HashNode * prev = NULL;
        while(temp != NULL)
        {
            prev = temp;
            temp = temp->next;
            delete prev;
        }
    }
}






