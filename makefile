# target: dependencies
# <tab> rule

# make (without arguments) executes first rule in file
# Ideally, one target for every object file and a target for final binary.

plagiarismChecker: plagiarismChecker.o
    g++ -otest plagiarismChecker.o
plagChk: plagiarismChecker.cpp
    g++ -c plagiarismChecker.cpp

