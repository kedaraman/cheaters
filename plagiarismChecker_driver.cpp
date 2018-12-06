#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "Hashtable.h"


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

int main()
{
    //Testing out HashTable First
    Hashtable htbl;
    htbl.add("Hello", "fileA");

    htbl.add("Goodbye", "fileA");
    htbl.add("Hello", "fileB");
    htbl.add("Hello", "fileA");
    htbl.checkDuplicates();




    string dir = string("C:/AA-KEDAR/SOPH-FALL/Cheaters/sm_doc_set");
    vector<string> files = vector<string>();

    int n = 6; //n-word sequence
    int limit = 200;//threshold for plaigirism

    vector<string> temp =  vector<string>();

    getdir(dir,files);




    //for (unsigned int i = 2;i < files.size();i++) {
    for (unsigned int i = 2;i < 7;i++) {
        //cout << i << files[i] << endl;

        ifstream myfile;
        string directory = dir+"/"+files[i];
        //cout << "+++" << directory << "+++\n";
        myfile.open(directory);
        string s;
        if(myfile)
        {
            while(getline(myfile,s))
            {
                //for(int j = 0; j < s.length(); j = j + n)
                //{
                    //cout << s.substr(j,j+n) << "\n";



                    std::vector<std::string> result;
                    std::istringstream iss(s);
                    for(std::string s; iss >> s; )
                        result.push_back(s);

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
                        htbl.add(toCheck,files[i]);
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

    htbl.checkDuplicates();






    return 0;
}