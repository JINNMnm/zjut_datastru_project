cmake_minimum_required(VERSION 3.26)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(code
        cpp/main.cpp
        h/Node.h
        cpp/Node.cpp
        h/AVLTree.h
        cpp/AVLTree.cpp
        h/Console.h
        cpp/Console.cpp
        h/BitMap.h
        cpp/BitMap.cpp
        cpp/BitMap.cpp
        h/const.h)
