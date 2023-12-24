#include <bits/stdc++.h>
using namespace std;


struct mypair {
    string first;
    int second;

    mypair () {
        this->first = "";
        this->second = 0;
    }

    mypair (string first, int second) {
        this->first = first;
        this->second = second;
    }
        
};



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

        if (base == -1) {
            return count;
        }

        start_index = min(next_same_opening_tag , next_same_closing_tag) + 1;
    }
    return count;
}


int main() {
    ifstream in("sample.xml");
    stringstream buffer;
    buffer << in.rdbuf();

    string s = "";
    int i = 0, j;
    string input_string = buffer.str(), tag = "", indentation = "";
    int level = 0;
    bool close_tag = false;
    int count;
    stack<mypair*> tags;

    
    while(i < input_string.length()) {

        if (input_string[i] == '<') {
            int check_for_closing_tag = input_string.find_first_not_of(" \n\r\t", i + 1);
            int close_tag_index = input_string.find('>', i + 1);
            indentation = "";

            if (input_string[check_for_closing_tag] == '/') {
                level--;
                tag = input_string.substr(check_for_closing_tag + 1, close_tag_index - check_for_closing_tag - 1);
                for(int j = 0; j < level + tags.size(); j++) indentation += "    ";

                if (close_tag) {
                    s += '\n';
                    s += indentation;
                    s += "    ";
                    s += '}';
                }
                
                if (!tags.empty() && (tag + to_string(level + 1)) == tags.top()->first && --tags.top()->second == 0) {
                    tags.pop();
                    s += '\n';
                    s += indentation;
                    s += ']';
                }

                close_tag = true;
                i = input_string.find_first_of('<', i + 1); // bypass the closing tag
                continue;
            
            } else {    // it must be an opening tag
                level++;
                tag = input_string.substr(i + 1, close_tag_index - i - 1);
                for(int j = 0; j < level + tags.size(); j++) indentation += "    ";

                count = get_tag_count(input_string, tag, i);

                if (!close_tag) {
                    s += '{';
                } else {
                    s += ",";
                }
                s += '\n';
                s += indentation;

                close_tag = false;
                i = close_tag_index;

                if (!tags.empty() && (tag + to_string(level)) == tags.top()->first) {
                    continue;
                }

                s += '"';
                s += tag;
                s += "\": ";

                if ( count != 1) {
                    tags.push(new mypair(tag + to_string(level), count));
                    s += "[\n";
                    s += indentation;
                    s += "    ";
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
                s += input_string.substr(first_after_open_tag, data_end_index - first_after_open_tag + 1);
            } else {
                s += '\"';
                s += input_string.substr(first_after_open_tag, data_end_index - first_after_open_tag + 1);
                s += '\"';
            }

            i = closing_tag_start_index;
            continue;
        }

        i = first_after_open_tag;
    }

    s += "\n}";

    ofstream out("output_json.json");
    out << s;
    out.close();

    return 0;
}