#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

class File {
    private:
        std::string path;

    public:
        File(const std::string path);
        std::string readFile();
        void outputFile(const std::string& output_string);
};