#include "xmlParser.h"


int xmlParser::getTagCount (std::string &input_string, std::string &tag_name, int start_index) {
    std::string opening_tag = "<" + tag_name + ">";
    std::string closing_tag = "</" + tag_name + ">";
    std::string next_tag;
    int next_same_opening_tag = 0, next_same_closing_tag = 0;
    int next_different_opening_tag_start = 0, next_different_opening_tag_end = 0;
    int count = 1, base = 0;
    
    while (1) {
        next_same_opening_tag = input_string.find(opening_tag, start_index);
        next_same_closing_tag = input_string.find(closing_tag, start_index);

        if (next_same_opening_tag == -1) {
            return count;
        }

        if (next_same_opening_tag < next_same_closing_tag) {
            base++;
        } else {
            base--;
        }

        if (base == 0) {
            next_different_opening_tag_start = input_string.find_first_of("<", next_same_closing_tag + closing_tag.length());
            if (next_different_opening_tag_start == -1) {
                break;
            }

            next_different_opening_tag_end = input_string.find_first_of(">", next_different_opening_tag_start);
            next_tag = input_string.substr(next_different_opening_tag_start, next_different_opening_tag_end - next_different_opening_tag_start + 1);
            if (next_tag != opening_tag) {
                break;
            }

            count++;
        }

        start_index = std::min(next_same_opening_tag , next_same_closing_tag) + 1;
    }
    return count;
}

void xmlParser::createTree(std::string& xml_input, Node* root) {
    int i = 0, start;
    while (i < xml_input.length()) {
        if (xml_input[i] != '<') {
            start = xml_input.find('<', i);
            root->appendChild(new Node(xml_input.substr(i, start - i), root));
            i = start;
        }

        if (xml_input[i + 1] == '/') {
            root = root->getParent();
            i = xml_input.find('>', i) + 1;
            continue;
        }

        int end = xml_input.find('>', i);
        std::string tag_name = xml_input.substr(i + 1, end - i - 1);
        Node *node = new Node(tag_name, root);
        root->appendChild(node);
        root = node;
        i = end + 1;
    }
}

void xmlParser::createJsonFromTree(Node* root, std::string& json_output, int level, bool is_array) {
    std::string indentation = "    ", indent = "";
    for (int i = 0; i < level; i++) indent += indentation;

    int children_count = root->getChildren().size();

    bool are_same_children = false;
    if (children_count > 1 && root->getChildren()[0]->getName() == root->getChildren()[1]->getName()) {
        are_same_children = true;
    }

    if (children_count == 0) {
        int first_non_numeric_char = root->getName().find_first_not_of("0123456789");
        if (!root->getName().empty() && (first_non_numeric_char == -1 || (first_non_numeric_char == 0 && root->getName()[0] == '-'))) {
            json_output += root->getName();
            return;
        }
        json_output += '"';
        json_output += root->getName();
        json_output += '"';
        return;
    }

    json_output += indent;

    if (!is_array && root->getName() != "") {
        json_output += '"';
        json_output += root->getName();
        json_output += "\": ";
    }

    if (root->getChildren()[0]->getChildren().size() != 0 && root->getName() != "") {
        json_output += "{\n";
    }

    if (are_same_children) {
        json_output += indent;
        json_output += indentation;
        json_output += '"';
        json_output += root->getChildren()[0]->getName();
        json_output += "\": [\n";
    }

    for (int j = 0; j < children_count; j++) {
        xmlParser::createJsonFromTree(root->getChildren()[j], json_output, level + 1 + are_same_children, are_same_children);
        if (j < children_count - 1) {
            json_output += ",\n";
        }
    }

    if (are_same_children) {
        json_output += '\n';
        json_output += indent;
        json_output += indentation;
        json_output += ']';
    }

    if (root->getChildren()[0]->getChildren().size() != 0 && root->getName() != "") {
        json_output += '\n';
        json_output += indent;
        json_output += '}';
    }
}

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

std::string xmlParser::toJsonByStrings(std::string &xml_input) {
    int i = 0, j;
    std::string json_output = "", indentation_type = "    ";
    int level = 0;
    bool close_tag = false;
    std::stack<std::string> tag_names;
    std::stack<int> tag_count;

    
    while(i < xml_input.length()) {
        if (xml_input[i] == '<') {
            int check_for_closing_tag = xml_input.find_first_not_of(" \n\r\t", i + 1);
            int close_tag_index = xml_input.find('>', i + 1);
            std::string indentation = "";

            if (xml_input[check_for_closing_tag] == '/') {
                level--;
                std::string tag = xml_input.substr(check_for_closing_tag + 1, close_tag_index - check_for_closing_tag - 1);
                for(int j = 0; j < level + tag_names.size(); j++) indentation += indentation_type;

                if (close_tag) {
                    json_output += '\n';
                    json_output += indentation;
                    json_output += indentation_type;
                    json_output += '}';
                }
                
                if (!tag_names.empty() && (tag + std::to_string(level + 1)) == tag_names.top() && --tag_count.top() == 0) {
                    tag_names.pop();
                    tag_count.pop();
                    json_output += '\n';
                    json_output += indentation;
                    json_output += ']';
                }

                close_tag = true;
                i = xml_input.find_first_of('<', i + 1); // bypass the closing tag
                continue;
            
            } else {    // it must be an opening tag
                level++;
                std::string tag = xml_input.substr(i + 1, close_tag_index - i - 1);
                for(int j = 0; j < level + tag_names.size(); j++) indentation += indentation_type;

                int count = xmlParser::getTagCount(xml_input, tag, i);

                if (!close_tag) {
                    json_output += '{';
                } else {
                    json_output += ",";
                }
                json_output += '\n';
                json_output += indentation;

                close_tag = false;
                i = close_tag_index;

                if (!tag_names.empty() && (tag + std::to_string(level)) == tag_names.top()) {
                    continue;
                }

                json_output += '"';
                json_output += tag;
                json_output += "\": ";

                if (count != 1) {
                    tag_names.push(tag + std::to_string(level));
                    tag_count.push(count);
                    json_output += "[\n";
                    json_output += indentation;
                    json_output += indentation_type;
                }

                continue;
            }
        }

        // check if text
        int first_after_open_tag = xml_input.find_first_not_of(" \n\r\t", i + 1);
        if (xml_input[i] == '>' && xml_input[first_after_open_tag] != '<') {

            int closing_tag_start_index = xml_input.find_first_of('<', i + 1);
            int data_end_index = xml_input.find_last_not_of(" \n\r\t", closing_tag_start_index - 1);
            int first_non_numerical_char_index = xml_input.find_first_not_of("0123456789-. \n", first_after_open_tag);

            if (first_non_numerical_char_index >= closing_tag_start_index) {
                json_output += xml_input.substr(first_after_open_tag, data_end_index - first_after_open_tag + 1);
            } else {
                json_output += '\"';
                json_output += xml_input.substr(first_after_open_tag, data_end_index - first_after_open_tag + 1);
                json_output += '\"';
            }

            i = closing_tag_start_index;
            continue;
        }

        i = first_after_open_tag;
    }

    json_output += "\n}";
    return json_output;
}

std::string xmlParser::toJsonByTrees(std::string& xml_input) {
    std::string minified_string = xmlParser::minify(xml_input);

    Node *root = new Node();
    createTree(minified_string, root);

    std::string json_string = "{\n";
    xmlParser::createJsonFromTree(root, json_string, 0, false);
    json_string += "\n}";
    return json_string;
}

std::string xmlParser::compress(std::string input) {
    return std::string();
}

std::string xmlParser::decompress(std::string compressed_input) {
    return std::string();
}
