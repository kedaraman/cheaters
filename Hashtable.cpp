#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "Hashtable.h"
#include <cmath>
#include <vector>


    Hashtable::Hashtable()
    {
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            tbl[i] = NULL;
        }
    }

    void Hashtable::add(string words, string fileName)
    {
        int index = hash(words);
        HashNode * temp = new HashNode;
        temp->key = words;
        temp->fileName = fileName;
        temp->next = NULL;

        HashNode * iter = tbl[index];
        bool alreadyInLinkedList = false;
        while(iter != NULL)
        {
            if(temp->key == iter->key && temp->fileName == iter->fileName)
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
        return abs(sum % TABLE_SIZE);
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
                        if(temp->key == prev->key && temp->fileName != prev->fileName)
                        {
                            cout << "MATCHED \"" << temp->key << "\" FROM FILES " << temp->fileName  << " AND " << prev->fileName << "\n";
                        }
                        prev = prev->next;
                     }
                     temp = temp->next;


                 }
             }
        }


    }






