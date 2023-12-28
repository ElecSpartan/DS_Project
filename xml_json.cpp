#include <bits/stdc++.h>
using namespace std;

struct mypair {
    string first;
    int second;

    mypair(){
        this->first = "";
        this->second = 0;
    }

    mypair(string first, int second){
        this->first = first;
        this->second = second;
    }
        
};

stack<mypair*> tags;

int get_tag_count(string &input_string, string &tag_name, int start_index, int end_index) {
    string tag = "<" + tag_name + ">";
    bool flag = true;
    int count = 0;
    
    while(start_index < end_index && start_index != -1) {
        count++;
        int check_next_closing_tag = input_string.find_first_not_of(" \n\r\t", start_index + tag.length());
        if (input_string[check_next_closing_tag] !=  '<') return 1;
        start_index = input_string.find(tag, start_index + tag.length());
    }
    return count;
}

int main() {
    ifstream in("sample.xml");
    stringstream buffer;
    buffer << in.rdbuf();

    string s = "";
    int i = 0, j;
    string input_string = buffer.str(), tag;
    int indentation_level = 0;
    bool close_tag = false, text = false, flag = true;
    int count;

    
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

                if(!close_tag) { 
                    indentation_level--;
                }
                
                if (close_tag && tags.top()->second == 1 && tags.size() != 1) {
                    indentation_level--;
                    s += '\n';
                    for(int j = 0; j < indentation_level; j++) s += "    ";
                    s += ']';
                }

                if (--tags.top()->second == 0) {
                    tags.pop();
                }

                close_tag = true;
                i = input_string.find_first_of('<', i + 1) - 1; // bypass the closing tag
            
            } else {    // it must be an opening tag
                int close_tag_index = input_string.find('>', i + 1);
                tag = input_string.substr(i + 1, close_tag_index - i - 1);
                int parent_close_tag_index = INT_MAX;
                if(!tags.empty()) {
                    parent_close_tag_index = input_string.find("</" + tags.top()->first + ">", i);
                }

                count = get_tag_count(input_string, tag, close_tag_index, parent_close_tag_index);

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

                if (tags.empty() || tag != tags.top()->first) {
                    s += '"';
                    s += tag;
                }

                i = close_tag_index - 1;
            }
            
            i++;
            continue;
        }


        int first_after_open_tag = input_string.find_first_not_of(" \n\r\t", i + 1);
        if (input_string[i] == '>' && input_string[first_after_open_tag] != '<') {
            text = true;
            indentation_level++;
        }


        if (input_string[i] == '>') {
            if (tags.empty() || tag != tags.top()->first) {
                s += "\": ";
            }
            
            if(flag) {
                tags.push(new mypair(tag, count));
                flag = false;
            }
            if(!flag && tag != tags.top()->first) tags.push(new mypair(tag, count));

            // CHECK IF DATA OR TAG CONTAINER
            if(count > 1) {
                s+= "[\n";
                indentation_level++;
                for(int j = 0; j < indentation_level; j++) s += "    ";
            }

        } else {
            s += input_string[i];
        }
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