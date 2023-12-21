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
    ifstream in(path);

    ofstream out(path);
    out << output_string;
    out.close();
}

string json_minify (string json_input) {
    string minified_json;
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

int main() {
    string input_string = read_file("sample.json");
    string output = json_minify(input_string);
    output_file("output_json_minified.json", output);

    return 0;
}