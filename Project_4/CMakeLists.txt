cmake_minimum_required(VERSION 3.26)
project(Project_4)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project_4 main.cpp
                commandLine.cpp
                commandLine.h
        Node.cpp
        Node.h
        MST.cpp
        MST.h
        FastTSP.cpp
        FastTSP.h
        OptTSP.cpp
        OptTSP.h
        Graph.cpp
        Graph.h)
