//File Name: HashTable.cpp
//
//Cheaters Program
//EE 312
/* Student information for project:
 *
 * Replace <NAME> with your name.
 *
 * On my honor, Aditya Khanna, this programming project is my own work
 * and I have not provided this code to any other student.
 *
 * Name: Aditya Khanna and Kedar Raman
 * email address: adityakhanna22@yahoo.com
 * UTEID: ak34642
 * Section 5 digit ID: 16225
 */

#include "HashTable.h"

HashTable::HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        this->table[i] = NULL;
    }
}

int HashTable::hashFunction(string words)
{
    /*int sum = 0;
    int length = words.length();
    for (int i = 0; i < length; i++)
    {
        sum += static_cast<int>(words[length - i - 1] * pow(23, i));
    }
    return (sum % TABLE_SIZE);*/
    signed int sum = 0;
    for(int i = 0; i < words.length(); i++)
    {
        int comp1 = words.size() - i - 1;
        int comp2 = static_cast<char>(words[comp1]);
        int temp = comp2 * pow(7,i);

        if(sum + temp< 0)
        {
            sum = sum / 4;
            temp = (static_cast<char>(words[words.size()-i-1]));
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

void HashTable::add(string words, int fileIndex)
{
    int index = hashFunction(words);
    HashNode* addedNode = new HashNode;
    addedNode->key = words;
    addedNode->fileIndex = fileIndex;
    HashNode* temp = this->table[index];
    bool alreadyInLinkedList = false;

    while(temp != NULL)
    {
        if ((addedNode->key == temp->key) && (addedNode->fileIndex == temp->fileIndex))
        {
            alreadyInLinkedList = true;
            break;
        }
        temp = temp->next;
    }
    if (!(alreadyInLinkedList))
    {
        addedNode->next = this->table[index];
        this->table[index] = addedNode;
    }
}

void HashTable::getDuplicates (int numFiles, vector<vector <int> > &duplicates)
{
    for (int i = 0; i < numFiles; i++) {
        for (int j = 0; j < numFiles; j++) {
            duplicates[i][j] = 0;
        }
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL) {
            HashNode* temp = table[i];
            HashNode* afterTemp = table[i];
            while (temp != NULL) {
                afterTemp = temp->next;
                while (afterTemp != NULL) {
                    if (temp->key == afterTemp->key && temp->fileIndex != afterTemp->fileIndex) {
                        //cout << "MATCHED \"" << temp->key << "\" FROM FILES " << temp->fileIdx  << " AND " << prev->fileIdx << "\n";
                        duplicates[temp->fileIndex - 2][afterTemp->fileIndex - 2]++;
                    }
                    afterTemp = afterTemp->next;
                }
                temp = temp->next;
            }
        }
    }
}

HashTable::~HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        //delete every linked list
    }
}
