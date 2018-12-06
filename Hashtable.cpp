#include "Hashtable.h"
#include <cmath>


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
        if(tbl[index] == NULL)
        {
            tbl[index] = temp;
        }
        else
        {
            temp->next = tbl[index];
            tbl[index] = temp;
        }


    }

    int Hashtable::hash(string s)
    {
        int sum = 0;
        for(int i = 0; i < s.length(); i++)
        {
            sum = static_cast<int>((sum + (static_cast<char>(s[s.size()-i-1])))*pow(23,i));
        }
        return sum % TABLE_SIZE;
    }






