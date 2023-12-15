#include "XML_Parser.h"

bool xml_is_correct(string &detected_file) {
    int opened_tag = 0;
    int closed_tag = 0;
    for (int i = 0; i < detected_file.size(); i++) {
        if (detected_file[i] == '<') {
            if (detected_file[i + 1] == '/')
                closed_tag++;
            else
                opened_tag++;
        }
        if (closed_tag > opened_tag)
            return false;
    }
    if (closed_tag != opened_tag)
        return false;

    stack<string> name_check;

    for (int i = 0; i < detected_file.size(); i++) {
        if (detected_file[i] == '<') {
            if (detected_file[i + 1] == '/') {
                string tag = "</";
                for (int j = i + 2; j < detected_file.size(); j++) {
                    tag.push_back(detected_file[j]);
                    if (detected_file[j] == '>')
                        break;
                }
                if (name_check.empty() ||
                    name_check.top().substr(1, name_check.top().size() - 2) != tag.substr(2, tag.size() - 3))
                    return false;
                name_check.pop();
            } else {
                string tag = "<";
                for (int j = i + 1; j < detected_file.size(); j++) {
                    tag.push_back(detected_file[j]);
                    if (detected_file[j] == '>')
                        break;
                }
                name_check.push(tag);
            }
        }
    }

    if (!name_check.empty())
        return false;


    return true;
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
string correct_xml(string &xml_file) {
    vector<string>file = divide_string_for_correction(xml_file);
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
    else if (x == 1)
        valid_file.push_back(to_push);


    stack<string> s;
    for (int i = 1; i <= file.size() - 2; i++) {
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
    else if (x == 0)
        valid_file.push_back(to_push);



    return add_new_lines(valid_file);
}
