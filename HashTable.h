//File Name: HashTable.h
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

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <cmath>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class HashTable
{
    struct HashNode
    {
        string key;
        string fileName;
        struct HashNode* next;
    };

    static const int TABLE_SIZE = 1000000;

private:
    HashNode* table [TABLE_SIZE];
    int hashFunction(string words);

public:
    HashTable();
    ~HashTable();
    void add(string words, string fileName);
    void checkDuplicates();

};

#endif
