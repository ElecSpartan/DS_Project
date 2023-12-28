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

string prettify (string& xml_input) {
    string prettified_xml = "<";
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

int main() {
    string input_string = read_file("sample.xml");
    string output = prettify(input_string);
    output_file("output_pretty.xml", output);

    return 0;
}