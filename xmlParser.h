#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include "Node.h"

class xmlParser {
private:
    static int getTagCount(std::string &input_string, std::string &tag_name, int start_index);

    static void createTree(std::string &xml_input, Node *root);

    static void createJsonFromTree(Node *root, std::string &json_output, int level, bool is_array);

    static std::string minifyJson(std::string &xml_input);

    static int num_of_new_lines(std::string &x);

    static bool temp_is_dummy(std::string &temp);

    static bool is_open_tag(std::string &s);

    static bool is_tag(std::string &s);

    static bool is_the_same(std::string &open, std::string &closed);

    static std::pair<std::vector<std::string>,int>  divide_string_for_correction(std::string &file);

    static std::string get_open_from_closed(std::string &s);

    static std::string get_closed_from_open(std::string &s);

    static std::string add_new_lines(std::vector<std::string> &file);

    static bool is_closed_tag(std::string &s);

    static std::vector<std::string> values_correction(std::vector<std::string> &file);

public:
    xmlParser() = delete;

    static std::string correct_xml(std::string &xml_file);

    static std::string get_errors(std::string &xml_file);

    static std::string minify(std::string& xml_input);

    static std::string prettify(std::string &xml_input);

    static std::string toJsonByStrings(std::string &xml_input);

    static std::string toJsonByTrees(std::string &xml_input);

    static std::string compress(std::string &input);

    static std::string decompress(std::string &compressed_input);
};


