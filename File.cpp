#include "File.h"

File::File(std::string path) {
    this->path = path;
}

std::string File::readFile() {
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

void File::outputFile(const std::string& output_string) {
    std::ofstream file(path);
    if (file.is_open()) {
        file << output_string;
        file.close();
    } else {
        std::cerr << "Error: Unable to write to file" << std::endl;
    }
}