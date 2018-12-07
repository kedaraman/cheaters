Hello! This is a guide on how to run the program! - Aditya Khanna and Kedar Raman (ak34642 and kvr336)

1) Unzip the folder (cheaters_ak34642.zip) and extract all of the
files (plagiarismCatcher_driver.cpp, HashTable.h, HashTable.cpp, makefile, and the readme.txt)
2) Compile the code by using the linux command make -f makefile
3) Run the executable (plagiarismCatcher) bu using the linux command ./plagiarismCatcher path/to/files chunk_size limit
where path/to files is the path to the directory that contains the files that you want to check for similarities,
chunk_size is the number of words to group (for the window), and the limit is the minimum number of similarities required for
files to be considered plagiarized

What the Program Does:
- The program will run a plagiarism checker (finds similarities between files in a directory
and outputs a list of files and the number of similarities between them to the console)

What Works:
- The small and medium directories work (they output quickly and accurately)

What Does Not Work:
- The large directory does not work (it does not output quickly)