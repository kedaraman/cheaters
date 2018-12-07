# target: dependencies
# <tab> rule

# make (without arguments) executes first rule in file
# Ideally, one target for every object file and a target for final binary.

plagiarismCatcher: plagiarismCatcher_driver.o HashTable.o
	g++ -o plagiarismCatcher plagiarismCatcher_driver.o HashTable.o
plagiarismCatcher_driver.o: plagiarismCatcher_driver.cpp HashTable.h
	g++ -c plagiarismCatcher_driver.cpp HashTable.h
HashTable.o: HashTable.h HashTable.cpp
	g++ -c HashTable.h HashTable.cpp
