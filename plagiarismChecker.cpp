#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


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
    string dir = string("C:/AA-KEDAR/SOPH-FALL/Cheaters/sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir,files);

    for (unsigned int i = 2;i < files.size();i++) {
        cout << i << files[i] << endl;

        ifstream myfile;
        string directory = dir+"/"+files[i];
        cout << "+++" << directory << "+++\n";
        myfile.open(directory);
        string s;
        if(myfile)
        {
            while(getline(myfile,s))
            {
                cout << "--" << s << "--\n";
            }
        }

//        if (!myfile) {
//            cout << "Unable to open file";
//            exit(1); // terminate with error
//        }
//
//        while (myfile >> s) {
//            cout << "--" << *s << "--\n";
//        }


    }






    return 0;
}