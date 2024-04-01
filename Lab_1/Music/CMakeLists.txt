cmake_minimum_required(VERSION 3.26)
project(Music)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Music
        lab1.cpp
        sorting.h
        getopt.c)
