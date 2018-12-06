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
        int key;
        std::string fileName;
        struct HashNode * next;
    };

private:
    HashNode* tbl[1000000];
public:
    Hashtable();
    ~Hashtable();





};
