#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("sample.xml");
    stringstream buffer;
    buffer << in.rdbuf();

    string s = "";
    int i = 0, j;
    string input_string = buffer.str();
    int indentation_level = -1;
    bool close_tag = false, text = false;

    
    while(i < input_string.length()) {

        if (input_string[i] == '<') {
            int check_for_closing_tag = input_string.find_first_not_of(" \n\r\t", i + 1);
            
            if (input_string[check_for_closing_tag] == '/') {
                close_tag = true;
                indentation_level--;
            } else {    // it must be an opening tag
                if (!close_tag) indentation_level++;
                close_tag = false;
            }

            if(i != 0) s += "\n";
            for(int j = 0; j < indentation_level; j++) s += "    ";
        }

        int first_after_open_tag = input_string.find_first_not_of(" \n\r\t", i + 1);
        if (input_string[i] == '>' && input_string[first_after_open_tag] != '<') {
            text = true;
            indentation_level++;
        }
        
        s += input_string[i];
        i = first_after_open_tag - 1;

        if (text) {
            text = false;
            if(first_after_open_tag == -1) break;

            s += "\n";
            for(int j = 0; j < indentation_level; j++) s += "    ";

            int data_start_index = first_after_open_tag;
            int closing_tag_start_index = input_string.find_first_of('<', i + 1);
            int data_end_index = input_string.find_last_not_of(" \n\r\t", closing_tag_start_index - 1);
            s += input_string.substr(data_start_index, data_end_index - data_start_index + 1);
            i = closing_tag_start_index - 1;
        }

        i++;
    }

    // cout << s;

    ofstream out("output_pretty.xml");
    out << s;
    out.close();

    return 0;
}