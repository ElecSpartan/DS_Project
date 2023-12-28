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



int get_tag_count(string &input_string, string &tag_name, int start_index, int end_index) {
    string tag = "<" + tag_name + ">";
    bool flag = true;
    int count = 0;
    
    while(start_index < end_index && start_index != -1) {
        count++;
        if (flag) {
            flag = false;
            int next_same_opening_tag = input_string.find(tag, start_index + 1);
            int my_closing_tag = input_string.find("</" + tag_name + ">", start_index) + 1;
            int next_opening_tag = input_string.find_first_not_of(" \n\r\t", my_closing_tag + tag.length());
            if (next_same_opening_tag != -1 && next_same_opening_tag > next_opening_tag) {
                return count;
            }
        }
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
    stack<mypair*> tags;

    
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

                if(!close_tag && count < 2) { 
                    indentation_level--;
                }

                int close_tag_index = input_string.find_first_of('>', check_for_closing_tag + 1);
                tag = input_string.substr(check_for_closing_tag + 1, close_tag_index - check_for_closing_tag - 1);
                
                if (!tags.empty() && tag == tags.top()->first && tags.top()->second == 1) {
                    indentation_level--;
                    s += '\n';
                    for(int j = 0; j < indentation_level; j++) s += "    ";
                    s += ']';
                }
                
                // IMPORTANT second condition
                if (!tags.empty() && tag == tags.top()->first && --tags.top()->second == 0) {
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

                if (!text) {
                    indentation_level++;
                    s += '{';
                } else {
                    s += ",";
                }

                close_tag = false;
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
            if(count < 2) {
                indentation_level++;
            }
        }


        if (input_string[i] == '>') {
            if (tags.empty() || tag != tags.top()->first) {
                s += "\": ";
            }
            
            if (flag && count != 1) {
                tags.push(new mypair(tag, count));
                flag = false;
            }
            if (!flag && (tags.empty() || tag != tags.top()->first) && count != 1) {
                tags.push(new mypair(tag, count));
            }

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