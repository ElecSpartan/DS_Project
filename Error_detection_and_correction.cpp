#include "Error_detection_and_correction.h"
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
pair<vector<string>,int> values_correction(vector<string>&file) {
    vector<string> v;
    int x = 2;
    if (is_open_tag(file[0]) && is_open_tag(file[file.size() - 1]))
        x = 1;
    else if (is_closed_tag(file[0]) && is_closed_tag(file[file.size() - 1]))
        x = 0;

    int line = 1;
    int last;
    for (int i = 0; i < file.size(); i++) {
        last = line;
        line += num_of_new_lines(file[i]);
        if (!is_tag(file[i]) && !temp_is_dummy(file[i])) {
            if (i == 1) {
                if (x == 1 || x == 0) {
                    v.push_back(get_open_from_closed(file[i + 1]));
                    v.push_back(file[i]);
                    errors.emplace_back(last, false);
                } else {
                    if (is_closed_tag(file[i + 1])) {
                        v.push_back(get_open_from_closed(file[i + 1]));
                        v.push_back(file[i]);
                        errors.emplace_back(last, false);
                    } else {
                        v.push_back(file[i]);
                        v.push_back(get_closed_from_open(file[i - 1]));
                        errors.emplace_back(line, true);
                        x = 0;
                    }
                }
            } else if (i == file.size() - 2) {
                if (x == 1 || x == 0) {
                    v.push_back(file[i]);
                    v.push_back(get_closed_from_open(file[i - 1]));
                    errors.emplace_back(line, true);
                } else {
                    if (is_open_tag(file[i - 1])) {
                        v.push_back(file[i]);
                        v.push_back(get_closed_from_open(file[i - 1]));
                        errors.emplace_back(line, true);
                    } else {
                        v.push_back(get_open_from_closed(file[i + 1]));
                        v.push_back(file[i]);
                        errors.emplace_back(last, false);
                        x = 1;
                    }
                }
            } else {
                if (!is_the_same(file[i - 1], file[i + 1])) {
                    if (is_open_tag(file[i - 1])) {
                        v.push_back(file[i]);
                        v.push_back(get_closed_from_open(file[i - 1]));
                        errors.emplace_back(line, true);
                    } else {
                        v.push_back(get_open_from_closed(file[i + 1]));
                        v.push_back(file[i]);
                        errors.emplace_back(last, false);
                    }
                }
            }
        } else
            v.push_back(file[i]);

    }
    return {v, x};
}
string correct_xml(string &xml_file) {
    vector<string>file = divide_string_for_correction(xml_file);
    pair<vector<string>,int> p = values_correction(file);
    file = p.first;
    vector<string>valid_file;
    int must_be = p.second;
    int x = 2;
    string to_push;
    if (!is_the_same(file[0], file[file.size() - 1]) || must_be!=2) {
        if (must_be == 1) {
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

    int line = 1;
    if(x!=1) {
        line += num_of_new_lines(file[0]);
    }
    int last;
    stack<string> s;
    for (int i = 1 - (x==1); i <= file.size() - 2 + (x == 0); i++) {

        last = line;
        line+= num_of_new_lines(file[i]);

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
                errors.emplace_back(last, false);
            }
        }
    }

    if(x!=0) {
        errors.emplace_back(line,true);
    }

    while (!s.empty()) {
        valid_file.push_back(get_closed_from_open(s.top()));
        errors.emplace_back(line, true);
        s.pop();
    }

    if (x == 2 || x== 1)
        valid_file.push_back(file[file.size() - 1]);
    else
        valid_file.push_back(to_push);



    return add_new_lines(valid_file);
}
