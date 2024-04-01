cmake_minimum_required(VERSION 3.26)
project(Lab_7)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab_7 hash.cpp
                    hashtable.h)

add_executable(Lab_7_bad badhash.cpp
        badtable.h)

add_executable(written replace_words.cpp
        written_test.cpp)
