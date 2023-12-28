#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("sample_minified.xml");
    stringstream buffer;
    buffer << in.rdbuf();

    string s = "<";
    int i = 1, j;
    string input_string = buffer.str();
    int indentation_level = 0;
    bool open_tag = false, close_tag = false, text = false, flag = false;

    
    while(i < input_string.length()) {
        if (input_string[i] == '<' && input_string[i+1] == '/') {
            close_tag = true;
            indentation_level--;
            s += "\n";
            for(int j = 0; j < indentation_level; j++) s += "    ";

        } else if (input_string[i] == '<') {
            open_tag = true;
            if (!close_tag) indentation_level++;
            close_tag = false;
            s += "\n";
            for(int j = 0; j < indentation_level; j++) s += "    ";
        }

        // this part can be optimised further
        if (input_string[i] == '>' && input_string[i + 1] != '<') {
            text = true;
            flag = true;
            indentation_level++;
        }
        
        
        s += input_string[i];
        if (flag) { // we can change it bychecking for i-1 && i instead of i && i+1
            s += "\n";
            for(int j = 0; j < indentation_level; j++) s += "    ";
            flag = false;
        }

        if (text) {
            text = false;
            int data_start_index = input_string.find_first_not_of(" \n\r\t", i + 1);
            if(data_start_index == -1) {
                i++;
                continue;
            }
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