#include "XML_Parser.h"
int num_of_new_lines(string &x) {
    int num = 0;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] == '\n')
            num++;
    }
    return num;
}
bool is_tag(string &s) {
    return (s[0] == '<' && s[s.size() - 1] == '>');
}
bool is_open_tag(string &s) {
    return (s[1] != '/') && is_tag(s);
}
bool is_closed_tag(string &s) {
    return (s[1] == '/') && is_tag(s);
}
bool is_the_same(string &open,string &closed) {
    int j = 0;
    bool the_same = true;
    for (int i = 0; i < closed.size(); i++) {
        if (i == 1)
            i++;

        the_same = the_same && (closed[i] == open[j]);
        j++;
    }
    return the_same;
}
string get_open_from_closed(string &s) {
    string open = "<" + s.substr(2);
    return open;
}
string get_closed_from_open(string &s) {
    string closed = "</" + s.substr(1);
    return closed;
}
string add_new_lines(vector<string>&file) {
    string valid_file = "";

    for (int i = 0; i < file.size(); i++) {
        if (i == file.size() - 1) {
            valid_file += file[i];
            break;
        }
        if (is_open_tag(file[i]) && is_open_tag(file[i + 1])) {
            valid_file += file[i];
            valid_file += "\n";
        } else if (is_closed_tag(file[i]) && is_closed_tag(file[i + 1])) {
            valid_file += file[i];
            valid_file += "\n";
        } else if (is_closed_tag(file[i]) && is_open_tag(file[i + 1])) {
            valid_file += file[i];
            valid_file += "\n";
        } else {
            valid_file += file[i];
        }
    }
    return valid_file;
}
vector<string> values_correction(vector<string>&file) {
    vector<string> v;
    for (int i = 0; i < file.size(); i++) {
        if (!is_tag(file[i]) && !temp_is_dummy(file[i])) {
            if (!is_the_same(file[i - 1], file[i + 1])) {
                if (i!=1 && is_open_tag(file[i - 1])) {
                    v.push_back(file[i]);
                    v.push_back(get_closed_from_open(file[i - 1]));
                } else {
                    v.push_back(get_open_from_closed(file[i + 1]));
                    v.push_back(file[i]);
                }
            } else
                v.push_back(file[i]);
        } else
            v.push_back(file[i]);
    }
    return v;
}
string correct_xml(string &xml_file) {
    vector<string>file = divide_string_for_correction(xml_file);
    file = values_correction(file);
    vector<string> valid_file;
    int x = 2; //  push both ( 1 >> push open / 0 >> push last )
    string to_push;
    if (!is_the_same(file[0], file[file.size() - 1])) {
        if (is_open_tag(file[0])) {
            x = 0;
            to_push = get_closed_from_open(file[0]);
        } else {
            x = 1;
            to_push = get_open_from_closed(file[file.size() - 1]);
        }
    }
    if (x == 2 || x == 0)
        valid_file.push_back(file[0]);
    else
        valid_file.push_back(to_push);


    stack<string> s;
    for (int i = 1 - (x==1); i <= file.size() - 2 + (x == 0); i++) {
        if (!is_tag(file[i])) {
            valid_file.push_back(file[i]);
            continue;
        }

        if (is_open_tag(file[i])) {
            valid_file.push_back(file[i]);
            s.push(file[i]);
        } else {
            if (!s.empty() && is_the_same(s.top(), file[i])) {
                valid_file.push_back(file[i]);
                s.pop();
            } else {
                valid_file.push_back(get_open_from_closed(file[i]));
                valid_file.push_back(file[i]);
            }
        }
    }

    while (!s.empty()) {
        valid_file.push_back(get_closed_from_open(s.top()));
        s.pop();
    }

    if (x == 2 || x== 1)
        valid_file.push_back(file[file.size() - 1]);
    else
        valid_file.push_back(to_push);



    return add_new_lines(valid_file);
}
vector<pair<pair<int, int>, string>> errors(string &xml_file) {
    vector<string> file = divide_string_for_correction(xml_file);
    vector<pair<pair<int, int>, string>> v; // line error , num of errors , string to print
    int add = 0;
    int add2 = 0;
    if (!is_the_same(file[0], file[file.size() - 1])) {
        if (is_open_tag(file[0])) {
            add = 1;
        } else {
            add2 = -1;
            v.push_back({{1, 1}, "Missing 1 open tag in line 1."});
        }
    } else {

    }
    int line = 1;
    if (!add2)
        line += num_of_new_lines(file[0]);

    stack<string> s;

    int last = 0;
    for (int i = 1 + add2; i < file.size() - 1 + add; i++) {
        last = line;
        line += num_of_new_lines(file[i]);
        if (!is_tag(file[i])) {
            if (temp_is_dummy(file[i]))
                continue;

            if (!is_the_same(file[i - 1], file[i + 1])) {
                if ((i!=1) && is_open_tag(file[i - 1])) {
                    v.push_back({{line, 1}, "Missing 1 closed tag in line " + to_string(line) + "."});
                    s.pop();
                } else {
                    s.push(get_open_from_closed(file[i+1]));
                    v.push_back({{last, 1}, "Missing 1 open tag in line " + to_string(last) + "."});
                }
            }
        } else {
            if (is_open_tag(file[i])) {
                s.push(file[i]);
            } else {
                if (!s.empty() && is_the_same(s.top(), file[i]))
                    s.pop();
                else {
                    v.push_back({{line, 1}, "Missing 1 open tag in line " + to_string(line) + "."});
                }
            }
        }
    }

    int num = add;
    while (!s.empty()) {
        num++;
        s.pop();
    }
    if (num)
        v.push_back({{line, num}, "Missing " + to_string(num) + " closed tag in line " + to_string(line) + "."});
    return v;
}