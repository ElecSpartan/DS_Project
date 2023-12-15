#include "XML_Parser.h"
void write_to_file(string address, string& content) {
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
vector<string> divide_string_for_graph(string &file) {
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
        }
        else {
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
vector<string> divide_string_for_correction(string &file) {
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
                divided_file.push_back(temp);

                temp = "";
                start = true;
            }
        }
        index++;
    }
    return divided_file;
}
Graph parse(string &file) {
    Graph g;
    vector<string> divided_file = divide_string_for_graph(file);
    User* obj_ptr;
    Post* post_ptr;
    vector<string> topics;
    vector<Post> posts;
    bool inside_followers = false;
    for(int i=0;i<divided_file.size();i++){
        string s = divided_file[i];
        if(s=="<user>")
            obj_ptr = new User;


        if(s=="<id>") {
            if (!inside_followers)
                obj_ptr->set_user_id(stoi(divided_file[i + 1]));
            else {
                g.add_follower(obj_ptr->get_user_id(), stoi(divided_file[i + 1]));
            }
        }

        if(s=="<name>")
            obj_ptr->set_name(divided_file[i+1]);

        if(s == "<followers>")
            inside_followers = true;

        if(s == "</followers>")
            inside_followers = false;

        if(s=="<post>"){
            post_ptr = new Post;
            if(divided_file[i+1]!="<body>")
                post_ptr->set_body(divided_file[i+1]);
        }

        if(s=="<body>")
            post_ptr->set_body(divided_file[i+1]);
        if(s=="<topic>")
            topics.push_back(divided_file[i+1]);


        if(s=="</post>"){
            posts.push_back(*post_ptr);
            delete post_ptr;
        }

        if(s=="</topics>"){
            post_ptr->set_topics(topics);
            topics.clear();
        }


        if(s=="</posts>") {
            obj_ptr->set_posts(posts);
            posts.clear();
        }

        if(s=="</user>"){
            g.add_user(obj_ptr->get_user_id(),*obj_ptr);
            delete obj_ptr;
        }
    }
    return g;
}