cmake_minimum_required(VERSION 3.12)
project(Cheaters)

set(CMAKE_CXX_STANDARD 14)

add_executable(Cheaters plagiarismCatcher_driver.cpp Hashtable.cpp Hashtable.h)