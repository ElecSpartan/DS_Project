cmake_minimum_required(VERSION 3.23)
project(DS_Project)

set(CMAKE_CXX_STANDARD 23)

add_executable(DS_Project
        main.cpp
        xmlParser.cpp
        xmlParser.h
        Node.cpp
        Node.h
        File.cpp
        File.h
        Network_Analysis.cpp
        Network_Analysis.h
        )
