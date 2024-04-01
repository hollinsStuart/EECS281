cmake_minimum_required(VERSION 3.26)
project(puzzle)

set(CMAKE_CXX_STANDARD 17)

add_executable(puzzle main.cpp commandLine.cpp debug.cpp helpers.cpp)
