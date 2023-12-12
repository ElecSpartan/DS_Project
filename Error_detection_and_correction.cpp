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
void correct_users_xml(vector<string>&file) {

}
void correct_general_xml(vector<string>&file) {


}
void correct_xml(vector<string>&file) {
    if (file[0] == "<users>" || file[file.size() - 1] == "</users")
        correct_users_xml(file);
    else
        correct_general_xml(file);
}
