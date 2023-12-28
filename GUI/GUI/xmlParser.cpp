#include "xmlParser.h"
std::vector<std::pair<int,bool>>errors; // line, type ( 0 >> open , 1 >> closed )

int xmlParser::getTagCount(std::string& input_string, std::string& tag_name, int start_index) {
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

std::string xmlParser::minifyJson(std::string& json_input) {
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

bool xmlParser::is_tag(std::string &s) {
    return (s[0] == '<' && s[s.size() - 1] == '>');
}

bool xmlParser::is_open_tag(std::string &s) {
    return (s[1] != '/') && is_tag(s);
}

bool xmlParser::is_closed_tag(std::string &s) {
    return (s[1] == '/') && is_tag(s);
}

bool xmlParser::is_the_same(std::string &open,std::string &closed) {
    int j = 0;
    bool the_same = true;
    for (int i = 0; i < closed.size(); i++) {
        if (i == 1)
            i++;

        the_same = the_same && (closed[i] == open[j]);
        j++;
    }
    return the_same;
}

std::string xmlParser::get_open_from_closed(std::string &s) {
    std::string open = "<" + s.substr(2);
    return open;
}

std::string xmlParser::get_closed_from_open(std::string &s) {
    std::string closed = "</" + s.substr(1);
    return closed;
}

std::string xmlParser::add_new_lines(std::vector<std::string>&file) {
    std::string valid_file = "";

    for (int i = 0; i < file.size(); i++) {
        if (i == file.size() - 1) {
            valid_file += file[i];
            break;
        }
        if (is_open_tag(file[i]) && is_open_tag(file[i + 1])) {
            valid_file += file[i];
            valid_file += "\n";
        } else if (is_closed_tag(file[i]) && is_closed_tag(file[i + 1])) {
            valid_file += file[i];
            valid_file += "\n";
        } else if (is_closed_tag(file[i]) && is_open_tag(file[i + 1])) {
            valid_file += file[i];
            valid_file += "\n";
        } else {
            valid_file += file[i];
        }
    }
    return valid_file;
}

int xmlParser::num_of_new_lines(std::string &x) {
    int num = 0;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] == '\n')
            num++;
    }
    return num;
}

bool xmlParser::temp_is_dummy(std::string &temp) {
    bool is_dummy = 1;
    for (auto ch: temp)
        is_dummy = is_dummy && (ch == '\n' || ch == ' ');


    return is_dummy;
}

std::vector<std::string> xmlParser::values_correction(std::vector<std::string>&file) {
    std::vector<std::string> v;

    int line = 1;
    int last;
    for (int i = 0; i < file.size(); i++) {
        last = line;
        line += num_of_new_lines(file[i]);
        if (!is_tag(file[i])) {
            if (is_the_same(file[i - 1], file[i + 1]) || temp_is_dummy(file[i])) {
                v.push_back(file[i]);
                continue;
            }

            if (i == 1) {
                v.push_back(get_open_from_closed(file[i + 1]));
                v.push_back(file[i]);
                errors.emplace_back(std::max(1, last - 1), false);
            } else if (i == file.size() - 2) {
                v.push_back(file[i]);
                v.push_back(get_closed_from_open(file[i - 1]));
                errors.emplace_back(std::max(1, line - 1), true);
            } else {
                if (is_open_tag(file[i - 1])) {
                    v.push_back(file[i]);
                    v.push_back(get_closed_from_open(file[i - 1]));
                    errors.emplace_back(std::max(1, line - 1), true);
                } else {
                    v.push_back(get_open_from_closed(file[i + 1]));
                    v.push_back(file[i]);
                    errors.emplace_back(std::max(1, last - 1), false);
                }
            }
        } else
            v.push_back(file[i]);
    }
    return v;
}

std::pair<std::vector<std::string>,int> xmlParser::divide_string_for_correction(std::string &file) {
    std::vector<std::string> divided_file;
    std::string temp = "";
    bool start = true;
    int start_line = 1;
    bool tag;
    int index = 0;
    bool first = true;
    while (index < file.size()) {
        if (start) {
            if (file[index] == '<')
                tag = true;
            else
                tag = false;

            start = false;
        }
        temp += file[index];
        if (tag) {
            if (file[index] == '>') {
                divided_file.push_back(temp);
                temp = "";
                start = true;
                first = false;
            }
        } else {
            if ((index == file.size() - 1 && !temp_is_dummy(temp)) || file[index + 1] == '<') {
                {
                    if (!(first && temp_is_dummy(temp)))
                        divided_file.push_back(temp);
                    else
                        start_line += num_of_new_lines(temp);

                    first = false;
                }

                temp = "";
                start = true;
            }
        }
        index++;
    }
    return {divided_file, start_line};
}

// butt
std::string xmlParser::correct_xml(std::string &xml_file) {
    std::pair<std::vector<std::string>, int> p = divide_string_for_correction(xml_file);
    std::vector<std::string> file = p.first;
    bool push_last_line = false;

    bool must_push_opening = false;
    if (file.size() >= 3)
        must_push_opening = !is_tag(file[1]) && is_open_tag(file[2]) && !temp_is_dummy(file[1]);

    if (!is_the_same(file[0], file[file.size() - 1])) {
        if (is_open_tag(file[0]) && !must_push_opening) {
            file.push_back(get_closed_from_open(file[0]));
            push_last_line = true;
        } else {
            file.insert(file.begin(), get_open_from_closed(file[file.size() - 1]));
            errors.emplace_back(1, false);
        }
    } else {
        if (file.size() >= 3) {
            if (!is_tag(file[1]) && is_open_tag(file[2]) && !temp_is_dummy(file[file.size() - 2])) {
                file.insert(file.begin(), get_open_from_closed(file[file.size() - 1]));
                errors.emplace_back(1, false);
            } else if (!is_tag(file[file.size() - 2]) && is_closed_tag(file[file.size() - 3]) &&
                       !temp_is_dummy(file[file.size() - 2])) {
                file.push_back(get_closed_from_open(file[0]));
                push_last_line = true;
            }
        }
    }


    std::vector<std::string> valid_file;
    valid_file.push_back(file[0]);
    file = values_correction(file);


    std::stack<std::string> s;
    int line = num_of_new_lines(valid_file[0]) + p.second;
    int last;

    for (int i = 1; i < file.size() - 1; i++) {
        last = line;
        line += num_of_new_lines(file[i]);

        if (!is_tag(file[i])) {
            valid_file.push_back(file[i]);
            continue;
        }

        if (is_open_tag(file[i])) {
            valid_file.push_back(file[i]);
            s.push(file[i]);
        } else {
            if (!s.empty() && is_the_same(s.top(), file[i])) {
                valid_file.push_back(file[i]);
                s.pop();
            } else {
                valid_file.push_back(get_open_from_closed(file[i]));
                valid_file.push_back(file[i]);
                errors.emplace_back(last, false);
            }
        }
    }


    while (!s.empty()) {
        valid_file.push_back(get_closed_from_open(s.top()));
        errors.emplace_back(line, true);
        s.pop();
    }

    valid_file.push_back(file[file.size() - 1]);
    if (push_last_line) {
        errors.emplace_back(line, true);
    }

    return add_new_lines(valid_file);
}

// butt
std::string xmlParser::get_errors(std::string &xml_file) {
    errors.clear();
    std::string s = correct_xml(xml_file);

    std::string ans = "";
    std::sort(errors.begin(), errors.end());
    for (int i = 0; i < errors.size(); i++) {
        ans += "Missing ";
        if (errors[i].second)
            ans += " Closing tag after line ";
        else
            ans += " Opening tag in line ";

        ans += std::to_string(errors[i].first);
        ans += '\n';
    }
    return ans;
}

// butt
std::string xmlParser::minify(std::string& xml_input) {
    std::string intermediate_string, minified_xml;
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
        minified_xml += intermediate_string[i];

        if (intermediate_string[i] == '>' && i != 0) {
            i = intermediate_string.find_last_not_of(" \n\r\t", i - 1) + 1;
        }

        i--;
    }

    return minified_xml;
}

// butt
std::string xmlParser::prettify(std::string& xml_input) {
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

// buttl
std::string xmlParser::toJsonByStrings(std::string& xml_input) {
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

// butt
std::string xmlParser::toJsonByTrees(std::string& xml_input) {
    std::string minified_xml = xmlParser::minify(xml_input);

    Node *root = new Node();
    xmlParser::createTree(minified_xml, root);

    std::string json_output = "{\n";
    xmlParser::createJsonFromTree(root, json_output, 0, false);
    json_output += "\n}";
    return json_output;
}

// butt
std::string xmlParser::compress(std::string& input) {
    return std::string();
}

// butt
std::string xmlParser::decompress(std::string& compressed_input) {
    return std::string();
}
