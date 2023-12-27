#include "xmlParser.h"


std::string xmlParser::minifyJson(std::string json_input) {
    return std::string();
}

std::string xmlParser::verify(std::string xml_input) {
    return std::string();
}

std::string xmlParser::correct(std::string xml_input) {
    return std::string();
}

std::string xmlParser::minify(std::string xml_input) {
    std::string intermediate_string, minified_string;
    int i = xml_input.length()- 1;
    bool text = false;

    while (i >= 0) {
        if (xml_input[i] == '<' && i != 0) {
            intermediate_string += '<';

            i = xml_input.find_last_not_of(" \n\r\t", i - 1);

            if (xml_input[i] != '>') {
                text = true;
            }
        }

        if (text && xml_input[i] == '>') {
            text = false;
        }
        
        if (text || (xml_input[i] != ' ' && xml_input[i] != '\t' && xml_input[i] != '\n')) {
            intermediate_string += xml_input[i];
        }

        i--;
    }

    i = intermediate_string.length() - 1;

    while (i >= 0) {
        minified_string += intermediate_string[i];

        if (intermediate_string[i] == '>' && i != 0) {
            i = intermediate_string.find_last_not_of(" \n\r\t", i - 1) + 1;
        }

        i--;
    }

    return minified_string;
}

std::string xmlParser::prettify(std::string xml_input) {
    return std::string();
}

std::string xmlParser::toJson(std::string xml_input) {
    return std::string();
}

std::string xmlParser::compress(std::string input) {
    return std::string();
}

std::string xmlParser::decompress(std::string compressed_input) {
    return std::string();
}
