#include <bits/stdc++.h>
using namespace std;


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


int main() {
    ifstream in("sample.xml");
    stringstream buffer;
    buffer << in.rdbuf();

    int i = 0, j;
    string input_string = buffer.str(), json = "", indentation_type = "    ";
    int level = 0;
    bool close_tag = false;
    stack<string> tag_names;
    stack<int> tag_count;

    
    while(i < input_string.length()) {
        if (input_string[i] == '<') {
            int check_for_closing_tag = input_string.find_first_not_of(" \n\r\t", i + 1);
            int close_tag_index = input_string.find('>', i + 1);
            string indentation = "";

            if (input_string[check_for_closing_tag] == '/') {
                level--;
                string tag = input_string.substr(check_for_closing_tag + 1, close_tag_index - check_for_closing_tag - 1);
                for(int j = 0; j < level + tag_names.size(); j++) indentation += indentation_type;

                if (close_tag) {
                    json += '\n';
                    json += indentation;
                    json += indentation_type;
                    json += '}';
                }
                
                if (!tag_names.empty() && (tag + to_string(level + 1)) == tag_names.top() && --tag_count.top() == 0) {
                    tag_names.pop();
                    tag_count.pop();
                    json += '\n';
                    json += indentation;
                    json += ']';
                }

                close_tag = true;
                i = input_string.find_first_of('<', i + 1); // bypass the closing tag
                continue;
            
            } else {    // it must be an opening tag
                level++;
                string tag = input_string.substr(i + 1, close_tag_index - i - 1);
                for(int j = 0; j < level + tag_names.size(); j++) indentation += indentation_type;

                int count = get_tag_count(input_string, tag, i);

                if (!close_tag) {
                    json += '{';
                } else {
                    json += ",";
                }
                json += '\n';
                json += indentation;

                close_tag = false;
                i = close_tag_index;

                if (!tag_names.empty() && (tag + to_string(level)) == tag_names.top()) {
                    continue;
                }

                json += '"';
                json += tag;
                json += "\": ";

                if (count != 1) {
                    tag_names.push(tag + to_string(level));
                    tag_count.push(count);
                    json += "[\n";
                    json += indentation;
                    json += indentation_type;
                }

                continue;
            }
        }

        // check if text
        int first_after_open_tag = input_string.find_first_not_of(" \n\r\t", i + 1);
        if (input_string[i] == '>' && input_string[first_after_open_tag] != '<') {

            int closing_tag_start_index = input_string.find_first_of('<', i + 1);
            int data_end_index = input_string.find_last_not_of(" \n\r\t", closing_tag_start_index - 1);
            int first_non_numerical_char_index = input_string.find_first_not_of("0123456789-. \n", first_after_open_tag);

            if (first_non_numerical_char_index >= closing_tag_start_index) {
                json += input_string.substr(first_after_open_tag, data_end_index - first_after_open_tag + 1);
            } else {
                json += '\"';
                json += input_string.substr(first_after_open_tag, data_end_index - first_after_open_tag + 1);
                json += '\"';
            }

            i = closing_tag_start_index;
            continue;
        }

        i = first_after_open_tag;
    }

    json += "\n}";

    ofstream out("output_json.json");
    out << json;
    out.close();

    return 0;
}