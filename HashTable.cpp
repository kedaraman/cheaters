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
    int sum = 0;
    int length = words.length();
    for (int i = 0; i < length; i++)
    {
        sum += static_cast<int>(words[length - i - 1] * pow(23, i));
    }
    return (sum % TABLE_SIZE);
    //sum += (sum (int)words[i])^2
    //
    //sum % length
}

void HashTable::add(string words, string fileName)
{
    int index = hashFunction(words);
    HashNode* addedNode = new HashNode;
    addedNode->key = words;
    addedNode->fileName = fileName;
    HashNode* temp = this->table[index];
    bool alreadyInLinkedList = false;

    while(temp != NULL)
    {
        if ((addedNode->key == temp->key) && (addedNode->fileName == temp->fileName))
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

void HashTable::checkDuplicates()
{
    vector<string> fNames;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (this->table[i] != NULL) {
            HashNode *temp = this->table[i];
            HashNode *next = this->table[i];
            while (temp != NULL) {
                next = temp->next;
                while (next != NULL) {
                    if (temp->key == next->key && temp->fileName != next->fileName) {
                        cout << "MATCHED \"" << temp->key << "\" FROM FILES " << temp->fileName << " AND "
                             << next->fileName << "\n";
                    }
                    next = next->next;
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
