#include "XML_Parser.h"
void write_to_file(string& address, string& content) {
    ofstream file(address);
    if (file.is_open()) {
        file << content;
        file.close();
    } else {
        cerr << "Error: Unable to write to file" << std::endl;
    }
}
string read_file(string address) {
    ifstream file(address);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file" << std::endl;
        return "";
    }
    string initial_file;
    string line;
    while (getline(file, line)) {
        initial_file += line + '\n';
    }
    file.close();
    return initial_file;
}
bool temp_is_dummy(string &temp) {
    bool is_dummy = 1;
    for (auto ch: temp)
        is_dummy = is_dummy && (ch == '\n' || ch == ' ');


    return is_dummy;
}
string trim(string&x) {
    string y = "";
    int start = 0;
    for (char c: x) {
        if (c != '\n' && c != ' ')
            break;

        start++;
    }
    int end = x.size() - 1;
    for (int i = x.size() - 1; i >= 0; i--) {
        if (x[i] != '\n' && x[i] != ' ')
            break;

        end--;
    }

    for (int i = start; i <= end; i++) {
        y += x[i];
    }
    return y;
}
vector<string> divide_string(string &file) {
    vector<string> divided_file;
    string temp = "";
    bool start = true;
    bool tag;
    int index = 0;
    while (index < file.size()) {
        if (start) {
            if (file[index] == '<')
                tag = true;
            else
                tag = false;

            start = false;
        }
        temp += file[index];
        if (tag) {
            if (file[index] == '>') {
                divided_file.push_back(temp);
                temp = "";
                start = true;
            }
        } else {
            if (file[index + 1] == '<') {
                if (!temp_is_dummy(temp)) {
                    divided_file.push_back(trim(temp));
                }
                temp = "";
                start = true;
            }
        }
        index++;
    }
    return divided_file;
}
