cmake_minimum_required(VERSION 3.26)
project(Trees)

set(CMAKE_CXX_STANDARD 17)

add_executable(Trees main.cpp
        BinarySearchTree.cpp
        BinarySearchTree.h
        AVLTree.cpp
        AVLTree.h
        Node.cpp
        Node.h)
