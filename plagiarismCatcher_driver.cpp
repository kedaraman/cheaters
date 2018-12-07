#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Hashtable.h"
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>


using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files) //Gets the passed directory's files  (names) in a vector of strings
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl; //If unable to open directory, return an Error message
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name)); //Push file name to the vector
    }
    closedir(dp);
    return 0;
}

struct outputOrdered { //Struct to get each string that we want to output and the corrsponding number of matches to sort them by
    int rank;
    string outputString;
};


vector<outputOrdered> listCheaters(vector< vector<int> > matrix, int limit, vector<string> fileNames)//Go through the 2d matrix of matches and add any interactions over 200 matches
{
    vector<outputOrdered> ret;
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[i].size(); j++)
        {
            if(matrix[i][j] >= limit)
            {
                stringstream num;//Use stringstreamt to convert integer to string
                string outputString;
                num << matrix[i][j];
                outputString = num.str();
                outputString += ": " + fileNames[i+2] + " , " + fileNames[j+2] + "\n";//Concatenate the string to output to the string
                outputOrdered pushed;//Make a struct with the needed data (number matches and the string)
                pushed.rank=matrix[i][j];
                pushed.outputString=outputString;
                ret.push_back(pushed); //Traverse through the matrix and if there are files with more matches than the minimum limit, put this data in the vector
            }
        }
    }
    return ret;
}

void printOrderedCheaters(vector<outputOrdered> list)//Print out the list of similar files in DESCENDING order
{
    cout << "LIST OF SIMILAR FILES"  << endl;
    for(int i = 0; i < list.size(); i++)//Bubble Sort through the list and sort it DECREASING
    {
        for(int j = 0; j < list.size()-i-1; j++)
        {
            if(list[j].rank < list[j+1].rank)
            {
                outputOrdered temp = {list[j].rank, list[j].outputString};//Swap the information  (DATA)
                list[j].rank = list[j+1].rank;
                list[j].outputString = list[j+1].outputString;
                list[j+1].rank = temp.rank;
                list[j+1].outputString = temp.outputString;
            }
        }
    }
    for(int i = 0; i < list.size(); i++)//Go through this sorted vector and print out the strings in order
    {
        cout << list[i].outputString;
    }


}



int main(int argc, char* argv[])
{
    Hashtable htbl; //Creates the HashTable

    string dir = argv[1]; //Directory is arg 1
    vector<string> files = vector<string>(); //vector of files with names

    int n = atoi(argv[2]); //n-word sequence
    int limit = atoi(argv[3]);//threshold for plaigirism

    getdir(dir,files);

    for (unsigned int i = 2;i < files.size();i++) { //Go through each valid file (starting at index 2)
        ifstream myfile;
        string directory = dir+"/"+files[i]; //Get the directory into a string

        char* copyDirectory = new char [directory.length()+1];//Get the file path into a string
        strcpy(copyDirectory, directory.c_str());
        myfile.open(copyDirectory);//Open that file
        string line;

        if(myfile)
        {
            while(getline(myfile,line))//Go through each line
            {
                    vector<string> result;//vector of each word in the line
                    char* str = new char [line.length()+1];//Make a string of the l ength of the line and copy the line into that string
                    strcpy(str, line.c_str());
                    char* token = strtok(str, " ");//Gets the substring of everything until it finds the firs space
                    while (token != NULL)
                    {
                        result.push_back(token);//Push this onto the vector
                        token = strtok(NULL, " ");//Convention- makes it keep going on string
                    }

                    for(int  j = 0; j < result.size(); j++)//Goes through every window (size n) and adds that string to the hashtable. Then goes over by one word
                    {
                        int  m = 0;
                        string toCheck = "";
                        while((m < n) && (j+m < result.size()))
                        {
                            toCheck = toCheck + result[j+m];
                            m++;
                        }
                        htbl.add(toCheck,i);
                    }
            }
        }
        myfile.close();//close the file!!
    }

    int numFiles = files.size() -  2;//Discount the first two files (.) and (..)
    vector<vector< int> > duplicates(numFiles,vector<int>(numFiles,1));//2D matrix of duplicates to chart them out and save the count for each file's  relationship with the other files (how many copies of text they share)
    htbl.getDuplicates(numFiles,duplicates);//Get number of duplicates in the hashtable

    vector<outputOrdered> out = listCheaters(duplicates,limit,files);//Print the similar files based on given duplicate table, limit, and the vector of file names to convert the index to the corresponding string

    printOrderedCheaters(out);


    return 0;
}