#pragma once
#include <iostream>

class xmlParser {
    private:
        static std::string minifyJson(std::string xml_input);
    public:
        xmlParser() = delete;
        static std::string verify(std::string xml_input);
        static std::string correct(std::string xml_input);
        static std::string minify(std::string xml_input);
        static std::string prettify(std::string xml_input);
        static std::string toJson(std::string xml_input);
        static std::string compress(std::string input);
        static std::string decompress(std::string compressed_input);
};


