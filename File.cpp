#include "File.h"


std::string File::readFile(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file" << std::endl;
        return "";
    }
    std::string file_string, line;
    while (getline(file, line)) {
        file_string += line + '\n';
    }
    file.close();
    return file_string;
}

void File::outputFile(std::string address,std::string &content) {
    std::ofstream file(address);
    if (file.is_open()) {
        file << content;
        file.close();
    } else {
        std::cerr << "Error: Unable to write to file" << std::endl;
    }
}