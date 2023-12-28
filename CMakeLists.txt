cmake_minimum_required(VERSION 3.23)
project(DS_Project)

set(CMAKE_CXX_STANDARD 23)

add_executable(DS_Project
        main.cpp
        Graph.cpp
        Post.cpp
        User.cpp
        Graph.h
        User.h
        Post.h
        huffman.cpp
        huffman.h)
