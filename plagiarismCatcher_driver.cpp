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


void printCheaters(vector< vector<int> > matrix, int limit, vector<string> fileNames)
{
    cout << "LIST OF SIMILAR FILES"  << endl;
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[i].size(); j++)
        {
            if(matrix[i][j] >= limit)
            {
                cout << matrix[i][j] << ": " << fileNames[i+2] << " , " << fileNames[j+2] << "\n";
            }
        }
    }
}




int main(int argc, char* argv[])
{
    //Testing out HashTable First
    Hashtable htbl;
//    htbl.add("Hello", 2);
//
//    htbl.add("Goodbye", 2);
//    htbl.add("Hello", 3);
//    htbl.add("Hello", 2);
//    htbl.checkDuplicates();





    string dir = argv[1];
    vector<string> files = vector<string>();

    int n = atoi(argv[2]); //n-word sequence
    int limit = atoi(argv[3]);//threshold for plaigirism

    vector<string> temp =  vector<string>();

    getdir(dir,files);




    for (unsigned int i = 2;i < files.size();i++) {
    //for (unsigned int i = 2;i < 7;i++) {
        //cout << i << files[i] << endl;

        ifstream myfile;
        string directory = dir+"/"+files[i];
        //cout << "+++" << directory << "+++\n";
        char* copyDirectory = new char [directory.length()+1];//ADI
        strcpy(copyDirectory, directory.c_str());//ADI
        myfile.open(copyDirectory);//ADI
        string line;
        if(myfile)
        {
            while(getline(myfile,line))
            {
                //for(int j = 0; j < s.length(); j = j + n)
                //{
                    //cout << s.substr(j,j+n) << "\n";



//                    std::vector<std::string> result;
//                    std::istringstream iss(s);
//                    for(std::string s; iss >> s; )
//                        result.push_back(s);
                    vector<string> result;//ADI
                    char* str = new char [line.length()+1];//ADI
                    strcpy(str, line.c_str());//ADI
                    char* token = strtok(str, " ");//ADI
                    while (token != NULL)//ADI
                    {
                        result.push_back(token);
                        token = strtok(NULL, " ");
                    }
                    vector<string>::iterator iter;//ADI

                    for(int  j = 0; j < result.size(); j++)
                    {
                        int  m = 0;
                        string toCheck = "";
                        while((m < n) && (j+m < result.size()))
                        {
                            toCheck = toCheck + result[j+m];
                            //cout << toCheck << "\n";
                            m++;
                        }
                        htbl.add(toCheck,i);
                        //cout << "********\n";
                    }



                //}
            }
        }
        myfile.close();

//        if (!myfile) {
//            cout << "Unable to open file";
//            exit(1); // terminate with error
//        }
//
//        while (myfile >> s) {
//            cout << "--" << *s << "--\n";
//        }


    }

    int numFiles = files.size() -  2;
    //vector<vector<int>>  dup;
    vector<vector< int> > duplicates(numFiles,vector<int>(numFiles,1));
    htbl.getDuplicates(numFiles,duplicates);

//    for(int i = 0; i < duplicates.size(); i++)
//    {
//        for(int  j =  0; j < duplicates.size(); j++)
//        {
//            cout << "   " << duplicates[i][j] << "   ";
//        }
//        cout << "\n";
//    }

    printCheaters(duplicates,limit,files);






    return 0;
}