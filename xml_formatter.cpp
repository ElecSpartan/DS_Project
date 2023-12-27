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

int main() {
    string input_string = read_file("sample.xml");

    string s = "";
    int i = input_string.find('<'), j;
    int indentation_level = -1;
    bool close_tag = false, file_start = true;

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

            if(!file_start) s += "\n";
            for(int j = 0; j < indentation_level; j++) s += "    ";
            file_start = false;
        }

        int first_after_open_tag = input_string.find_first_not_of(" \n\r\t", i + 1);
        if (first_after_open_tag == -1) {
            s += '>';
            break;
        }

        if (input_string[i] == '>' && input_string[first_after_open_tag] != '<') {
            indentation_level++;

            s += ">\n";
            for(int j = 0; j < indentation_level; j++) s += "    ";

            int closing_tag_start_index = input_string.find_first_of('<', i + 1);
            int data_end_index = input_string.find_last_not_of(" \n\r\t", closing_tag_start_index - 1);
            s += input_string.substr(first_after_open_tag, data_end_index - first_after_open_tag + 1);
            i = closing_tag_start_index;
            continue;
        }
        
        s += input_string[i];
        i = first_after_open_tag - 1;

        i++;
    }

    output_file("output_pretty.xml", s);

    return 0;
}