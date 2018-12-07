//File Name: driver.cpp
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

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "HashTable.h"
#include <cstdlib>
# include <cstring>

using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main(int argc, char* argv[])
{
    //string dir = argv[1];
    //const int CHUNK_SIZE = atoi(argv[2]);
    //const int SIMILARITY_THRESHOLD = atoi(argv[3]);
    vector<string> files = vector<string>();

    int n = 6; //n-word sequence

    string dir = "C:/Users/adity/CLionProjects/Cheaters!/sm_doc_set";
    getdir(dir,files);

    HashTable hashTable;

    for (unsigned int i = 2; i < files.size(); i++)
    {
        cout << i << files[i] << endl;

        ifstream myFile;
        string directory = dir+"/"+files[i];
        //cout << "+++" << directory << "+++\n";
        char* copyDirectory = new char [directory.length()+1];
        strcpy(copyDirectory, directory.c_str());
        myFile.open(copyDirectory);
        string line;
        if(myFile)
        {
            while(getline(myFile, line))
            {
                vector<string> results;
                char* str = new char [line.length()+1];
                strcpy(str, line.c_str());
                char* token = strtok(str, " ");
                while (token != NULL)
                {
                    results.push_back(token);
                    token = strtok(NULL, " ");
                }
                vector<string>::iterator iter;

                for(int  j = 0; j < results.size(); j++)
                {
                    int  m = 0;
                    string toCheck = "";
                    while(m < n)
                    {
                        toCheck = toCheck + results[j + m];
                        cout << toCheck << "\n";
                        m++;
                    }
                    hashTable.add(toCheck,files[i]);
                    cout << "********\n";
                }
            }
        }
        myFile.close();
    }
    return 0;
}
