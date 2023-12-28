#include "Error_detection_and_correction.h"
vector<pair<int,bool>>errors; // line, type ( 0 >> open , 1 >> closed )
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

    int line = 1;
    int last;
    for (int i = 0; i < file.size(); i++) {
        last = line;
        line += num_of_new_lines(file[i]);
        if (!is_tag(file[i])) {
            if (is_the_same(file[i - 1], file[i + 1]) || temp_is_dummy(file[i])) {
                v.push_back(file[i]);
                continue;
            }

            if (i == 1) {
                v.push_back(get_open_from_closed(file[i + 1]));
                v.push_back(file[i]);
                errors.emplace_back(max(1, last - 1), false);
            } else if (i == file.size() - 2) {
                v.push_back(file[i]);
                v.push_back(get_closed_from_open(file[i - 1]));
                errors.emplace_back(max(1, line - 1), true);
            } else {
                if (is_open_tag(file[i - 1])) {
                    v.push_back(file[i]);
                    v.push_back(get_closed_from_open(file[i - 1]));
                    errors.emplace_back(max(1, line - 1), true);
                } else {
                    v.push_back(get_open_from_closed(file[i + 1]));
                    v.push_back(file[i]);
                    errors.emplace_back(max(1, last - 1), false);
                }
            }
        } else
            v.push_back(file[i]);
    }
    return v;
}
string correct_xml(string &xml_file) {
    pair<vector<string>, int> p = divide_string_for_correction(xml_file);
    vector<string> file = p.first;
    bool push_last_line = false;

    bool must_push_opening = false;
    if (file.size() >= 3)
        must_push_opening = !is_tag(file[1]) && is_open_tag(file[2]) && !temp_is_dummy(file[1]);

    if (!is_the_same(file[0], file[file.size() - 1])) {
        if (is_open_tag(file[0]) && !must_push_opening) {
            file.push_back(get_closed_from_open(file[0]));
            push_last_line = true;
        } else {
            file.insert(file.begin(), get_open_from_closed(file[file.size() - 1]));
            errors.emplace_back(1, false);
        }
    }
    else {
        if (file.size() >= 3) {
            if (!is_tag(file[1]) && is_open_tag(file[2]) && !temp_is_dummy(file[file.size()-2])) {
                file.insert(file.begin(), get_open_from_closed(file[file.size() - 1]));
                errors.emplace_back(1, false);
            } else if (!is_tag(file[file.size() - 2]) && is_closed_tag(file[file.size() - 3]) && !temp_is_dummy(file[file.size()-2])) {
                file.push_back(get_closed_from_open(file[0]));
                push_last_line = true;
            }
        }
    }


    vector<string> valid_file;
    valid_file.push_back(file[0]);
    file = values_correction(file);


    stack<string> s;
    int line = num_of_new_lines(valid_file[0]) + p.second;
    int last;

    for (int i = 1; i < file.size() - 1; i++) {
        last = line;
        line += num_of_new_lines(file[i]);

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


    while (!s.empty()) {
        valid_file.push_back(get_closed_from_open(s.top()));
        errors.emplace_back(line, true);
        s.pop();
    }

    valid_file.push_back(file[file.size() - 1]);
    if (push_last_line) {
        errors.emplace_back(line, true);
    }

    return add_new_lines(valid_file);
}
vector<pair<int,bool>> get_errors(string &xml_file) {
    errors.clear();
    string s = correct_xml(xml_file); // dummy
    sort(errors.begin(), errors.end());
    return errors;
}
