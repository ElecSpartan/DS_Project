#pragma once
#include <iostream>
#include <stack>
#include "Node.h"

class xmlParser {
    private:
        static int getTagCount(std::string& input_string, std::string &tag_name, int start_index);
        static void createTree(std::string& xml_input, Node* root);
        static void createJsonFromTree(Node* root, std::string& json_output, int level, bool is_array);
        static std::string minifyJson(std::string& xml_input);
    public:
        xmlParser() = delete;
        static std::string verify(std::string& xml_input);
        static std::string correct(std::string& xml_input);
        static std::string minify(std::string& xml_input);
        static std::string prettify(std::string& xml_input);
        static std::string toJsonByStrings(std::string& xml_input);
        static std::string toJsonByTrees(std::string& xml_input);
        static std::string compress(std::string& input);
        static std::string decompress(std::string& compressed_input);
};


