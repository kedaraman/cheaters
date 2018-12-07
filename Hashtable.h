//
// Created by kedar on 12/5/2018.
//

#ifndef CHEATERS_HASHTABLE_H
#define CHEATERS_HASHTABLE_H

#endif //CHEATERS_HASHTABLE_H

#include <string>

using namespace std;

class Hashtable
{
    struct HashNode{
        string key;
        int fileIdx;
        struct HashNode * next;
    };
    static const int TABLE_SIZE = 100;


private:
    HashNode* tbl[TABLE_SIZE];

public:

    Hashtable();
    //~Hashtable();
    void add(string words, int fileName);
    int hash(string s);
    void checkDuplicates();
    void getDuplicates(int,vector<vector<int>>& );






};
