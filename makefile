# target: dependencies
# <tab> rule

# make (without arguments) executes first rule in file
# Ideally, one target for every object file and a target for final binary.

plagiarismCatcher: plagiarismCatcher_driver.o Hashtable.o
	g++ -o plagiarismCatcher plagiarismCatcher_driver.o Hashtable.o
plagiarismCatcher_driver.o: plagiarismCatcher_driver.cpp Hashtable.h
	g++ -c plagiarismCatcher_driver.cpp Hashtable.h
Hashtable.o: Hashtable.h Hashtable.cpp
	g++ -c Hashtable.h Hashtable.cpp