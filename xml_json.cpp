#include <bits/stdc++.h>
using namespace std;


string read_file (string path) {
    ifstream in(path);

    stringstream buffer;
    buffer << in.rdbuf();
    in.close();

    return buffer.str();
}

void output_file (string path, string output_string) {
    ofstream out(path);
    out << output_string;
    out.close();
}

int get_tag_count (string &input_string, string &tag_name, int start_index) {
    string opening_tag = "<" + tag_name + ">";
    string closing_tag = "</" + tag_name + ">";
    string next_tag;
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

        start_index = min(next_same_opening_tag , next_same_closing_tag) + 1;
    }
    return count;
}

string toJSON (string& xml_input) {
    int i = 0, j;
    string json_output = "", indentation_type = "    ";
    int level = 0;
    bool close_tag = false;
    stack<string> tag_names;
    stack<int> tag_count;

    
    while(i < xml_input.length()) {
        if (xml_input[i] == '<') {
            int check_for_closing_tag = xml_input.find_first_not_of(" \n\r\t", i + 1);
            int close_tag_index = xml_input.find('>', i + 1);
            string indentation = "";

            if (xml_input[check_for_closing_tag] == '/') {
                level--;
                string tag = xml_input.substr(check_for_closing_tag + 1, close_tag_index - check_for_closing_tag - 1);
                for(int j = 0; j < level + tag_names.size(); j++) indentation += indentation_type;

                if (close_tag) {
                    json_output += '\n';
                    json_output += indentation;
                    json_output += indentation_type;
                    json_output += '}';
                }
                
                if (!tag_names.empty() && (tag + to_string(level + 1)) == tag_names.top() && --tag_count.top() == 0) {
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
                string tag = xml_input.substr(i + 1, close_tag_index - i - 1);
                for(int j = 0; j < level + tag_names.size(); j++) indentation += indentation_type;

                int count = get_tag_count(xml_input, tag, i);

                if (!close_tag) {
                    json_output += '{';
                } else {
                    json_output += ",";
                }
                json_output += '\n';
                json_output += indentation;

                close_tag = false;
                i = close_tag_index;

                if (!tag_names.empty() && (tag + to_string(level)) == tag_names.top()) {
                    continue;
                }

                json_output += '"';
                json_output += tag;
                json_output += "\": ";

                if (count != 1) {
                    tag_names.push(tag + to_string(level));
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

int main() {
    string input_string = read_file("sample.xml");

    string json_string = toJSON(input_string);

    output_file("output_json.json", json_string);

    return 0;
}