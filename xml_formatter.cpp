#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("sample_minified.xml");
    stringstream buffer;
    buffer << in.rdbuf();

    string s;
    int i = 0, j;
    string input_string = buffer.str();
    int indentation_level = -1;
    bool open_tag = false, close_tag = false, flag = false;

    
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

        if (input_string[i] == '>' && input_string[i+1] != '<') {
            indentation_level++;
            flag = true;
        }

        
        
        s += input_string[i];
        if (flag) { // we can change it bychecking for i-1 && i instead of i && i+1
            s += "\n";
            for(int j = 0; j < indentation_level; j++) s += "    ";
            flag = false;
        }

        i++;
    }

    cout << s;

    ofstream out("output.xml");
    out << s;
    out.close();

    return 0;
}