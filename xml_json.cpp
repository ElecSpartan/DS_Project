#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("sample.xml");
    stringstream buffer;
    buffer << in.rdbuf();

    string s = "";
    int i = 0, j;
    string input_string = buffer.str();
    int indentation_level = 0;
    bool close_tag = false, text = false;

    
    while(i < input_string.length()) {

        if (input_string[i] == '<') {
            int check_for_closing_tag = input_string.find_first_not_of(" \n\r\t", i + 1);
            
            if (input_string[check_for_closing_tag] == '/') {
                if (text && close_tag) {
                    indentation_level--;
                    s += '\n';
                    for(int j = 0; j < indentation_level; j++) s += "    ";
                    s += '}';
                }

                if(!close_tag) indentation_level--;

                close_tag = true;
                i = input_string.find_first_of('<', i + 1) - 1; // bypass the closing tag
            
            } else {    // it must be an opening tag
                close_tag = false;

                if (!text) {
                    indentation_level++;
                    s += '{';
                } else {
                    s += ",";
                }

                text = false;

                s += '\n';
                for(int j = 0; j < indentation_level; j++) s += "    ";
                // if(!close_tag) do the code below
                s += '"';
            }
            
            i++;
            continue;
        }


        int first_after_open_tag = input_string.find_first_not_of(" \n\r\t", i + 1);
        if (input_string[i] == '>' && input_string[first_after_open_tag] != '<') {
            text = true;
            indentation_level++;
        }


        if (input_string[i] == '>') s += "\": ";
        else s += input_string[i];
        i = first_after_open_tag - 1;


        if (text) {
            if(first_after_open_tag == -1) break;

            int data_start_index = first_after_open_tag;
            int closing_tag_start_index = input_string.find_first_of('<', i + 1);
            int data_end_index = input_string.find_last_not_of(" \n\r\t", closing_tag_start_index - 1);
            int first_non_numerical_char_index = input_string.find_first_not_of("0123456789-.", data_start_index);

            if (first_non_numerical_char_index >= closing_tag_start_index) {
                s += input_string.substr(data_start_index, data_end_index - data_start_index + 1);
            } else {
                s += '\"';
                s += input_string.substr(data_start_index, data_end_index - data_start_index + 1);
                s += '\"';
            }

            i = closing_tag_start_index - 1;
        }

        i++;
    }

    s += "\n}";

    // cout << s;

    ofstream out("output_json.json");
    out << s;
    out.close();

    return 0;
}