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
            tbl[i] = NULL;
        }
    }

    void Hashtable::add(string words, int fileIdx)
    {
        int index = hash(words);
        HashNode * temp = new HashNode;
        temp->key = words;
        temp->fileIdx = fileIdx;
        temp->next = NULL;

        HashNode * iter = tbl[index];
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
        if(!alreadyInLinkedList)
        {
            temp->next = tbl[index];
            tbl[index] = temp;
        }
    }

    int Hashtable::hash(string s)
    {
        signed int sum = 0;
        for(int i = 0; i < s.length(); i++)
        {
            int comp1 = s.size() - i - 1;
            int comp2 = static_cast<char>(s[comp1]);
            int temp = comp2 * pow(7,i);

            //int temp = (static_cast<char>(s[s.size()-i-1]))*pow(7,i);
            if(sum + temp< 0)
            {
                sum = sum / 4;
                temp = (static_cast<char>(s[s.size()-i-1]));
                sum = sum + temp;
            } else{
                sum = sum + temp;
            }
        }
        int result = sum % TABLE_SIZE;
        if(result < 0)
        {
            result = result * -1;
        }

        return result;
    }

    void Hashtable::checkDuplicates()
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

void Hashtable::getDuplicates (int numFiles, vector< vector<int> > &duplicates)
{

    for(int i = 0; i < numFiles; i++){
        for(int j = 0; j < numFiles;  j++)
        {
            duplicates[i][j] = 0;
        }
    }


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
                        //cout << "MATCHED \"" << temp->key << "\" FROM FILES " << temp->fileIdx  << " AND " << prev->fileIdx << "\n";
                        duplicates[temp->fileIdx-2][prev->fileIdx-2]++;
                    }
                    prev = prev->next;
                }
                temp = temp->next;


            }
        }
    }

}






