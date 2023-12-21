#include <bits/stdc++.h>
using namespace std;

string read_file(string path) {
    ifstream in(path);

    stringstream buffer;
    buffer << in.rdbuf();
    in.close();

    return buffer.str();
}

void output_file(string path, string output_string) {
    ifstream in(path);

    ofstream out(path);
    out << output_string;
    out.close();
}

string minify (string xml_input) {
    string intermediate_string;
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
    string minified_string;

    while (i >= 0) {
        minified_string += intermediate_string[i];

        if (intermediate_string[i] == '>' && i != 0) {
            i = intermediate_string.find_last_not_of(" \n\r\t", i - 1) + 1;
        }

        i--;
    }

    return minified_string;
}

int main() {
    string input_string = read_file("sample.xml");
    string output = minify(input_string);
    output_file("output_minified.xml", output);
    return 0;
}