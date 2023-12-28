#include "xmlParser.h"


std::string xmlParser::minifyJson(std::string json_input) {
    std::string minified_json;
    int i = 0;
    bool text = false;

    while (i < json_input.length()) {
        if (json_input[i] == '"') {
            text = !text;
        }
        
        if (text || (json_input[i] != ' ' && json_input[i] != '\t' && json_input[i] != '\n')) {
            minified_json += json_input[i];
        }

        i++;
    }

    return minified_json;
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
    std::string prettified_xml = "<";
    int i = xml_input.find('<') + 1, j;
    int indentation_level = 0;
    bool close_tag = false;

    while(i < xml_input.length()) {

        if (xml_input[i] == '<') {
            int check_for_closing_tag = xml_input.find_first_not_of(" \n\r\t", i + 1);
            
            if (xml_input[check_for_closing_tag] == '/') {
                close_tag = true;
                indentation_level--;
            } else {
                if (!close_tag) indentation_level++;
                close_tag = false;
            }

            prettified_xml += "\n";
            for(int j = 0; j < indentation_level; j++) prettified_xml += "    ";
        }

        int first_after_open_tag = xml_input.find_first_not_of(" \n\r\t", i + 1);
        if (first_after_open_tag == -1) {
            prettified_xml += '>';
            break;
        }

        if (xml_input[i] == '>' && xml_input[first_after_open_tag] != '<') {
            indentation_level++;

            prettified_xml += ">\n";
            for(int j = 0; j < indentation_level; j++) prettified_xml += "    ";

            int closing_tag_start_index = xml_input.find_first_of('<', i + 1);
            int data_end_index = xml_input.find_last_not_of(" \n\r\t", closing_tag_start_index - 1);
            prettified_xml += xml_input.substr(first_after_open_tag, data_end_index - first_after_open_tag + 1);
            i = closing_tag_start_index;
            continue;
        }
        
        prettified_xml += xml_input[i];
        i = first_after_open_tag - 1;
        i++;
    }

    return prettified_xml;
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
