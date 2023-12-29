#pragma once
#include <iostream>
#include <fstream>

class File {
public:
        static std::string readFile(std::string path);
        static void outputFile(std::string path,std::string &s);
};