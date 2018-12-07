//
// Created by kedar on 12/5/2018.
//

#ifndef CHEATERS_HASHTABLE_H
#define CHEATERS_HASHTABLE_H

#endif //CHEATERS_HASHTABLE_H

#include <string>
#include <vector>

using namespace std;

class Hashtable
{
    struct HashNode{
        string key;
        int fileIdx;
        struct HashNode * next;//Node for the LinkedList in the Hashtable
    };
    static const int TABLE_SIZE = 100000;//Size of the Hash Table Array


private:
    HashNode* tbl[TABLE_SIZE];//The table containing references to the LinkedList at each index

public:
    Hashtable();//Constructor (Default)
    ~Hashtable(); //Destructor
    void add(string words, int fileName);//Adds a word-fileIdx pair  to the Hashtable
    int hash(string s);//Hashes the key (word string)
    void checkDuplicates();//Checks for duplicates and prints them out (used for debugging ONLY)
    void getDuplicates(int,vector< vector<int> >& );//Gets the duplicates and puts it into a vector of int vectors (2D matrix) passed as a parameter
};
