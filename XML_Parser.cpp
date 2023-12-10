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
string readFile(string address) {
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
string trim(string x) {
    string y = x;
    while (y.back() == ' ' || y.back() == '\n')
        y.pop_back();

    return y;
}
pair<string,Graph> parsing_with_correcting_errors(string address,vector<int>&line_num_error) {
    string initial_file = readFile(address);
    string endFile = "";
    int lineNum = 1;
    vector<string> expected = {"<users>", "<user>", "<id>", "<name>", "<posts>", "<post>", "<body>", "<topics>",
                               "<topic>",
                               "<followers>", "<follower>", "<id>"};
    int expectedIndex = 0;
    stack<string> lastOpening;
    bool nextIsOpening = true;
    bool nextIsClosing = false;

    int id;
    string name, body;
    vector<string> topics;
    vector<Post> posts;
    vector<int> followersIds;
    bool firstId = true;

    Graph g;

    int index = 0;
    while (index < initial_file.length()) {
        char c = initial_file[index];
        if (c == ' ' || c == '\n') {
            endFile += c;
            if (c == '\n') {
                lineNum++;
            }
            index++;
            continue;
        }


        //determine wether it is closing or opening
        if (nextIsOpening || nextIsClosing) {
            if (initial_file[index + 1] == '/') {
                nextIsOpening = false;
                nextIsClosing = true;
            } else {
                nextIsOpening = true;
                nextIsClosing = false;
            }
        }

        if (nextIsOpening && !nextIsClosing) {
            bool flag = true;
            bool endl_needed = false;
            int len = 0;
            for(int i=index;initial_file[i]!='\n';i++)
                len++;
            if(len < expected[expectedIndex].size() ){
                flag = false;
                endl_needed = true;
            }
            else{
                string temp = initial_file.substr(index,expected[expectedIndex].size());
                if(temp != expected[expectedIndex]){
                    flag = false;
                    if(temp[0]=='<'){
                        for(index ; temp[index]!='>' ; index++ )
                            continue;
                        index++;
                    }
                }
            }

            lastOpening.push(expected[expectedIndex]);
            for (char ch: expected[expectedIndex]) {
                endFile += ch;
                if(flag)
                    index++;
            }
            if(endl_needed)
                endFile += '\n';
            if (expected[expectedIndex] == "<id>" || expected[expectedIndex] == "<name>" ||
                expected[expectedIndex] == "<body>" || expected[expectedIndex] == "<topic>") {
                nextIsOpening = false;
                nextIsClosing = false;
            }

            if (expectedIndex != 8 && expectedIndex != 11) {
                expectedIndex++;
            } else if (expectedIndex == 11) {
                expectedIndex--;
            }
        }
        else if (!nextIsOpening && !nextIsClosing) {
            string txt;
            while (initial_file[index] != '<') {
                endFile += initial_file[index];
                txt += initial_file[index];
                if (initial_file[index] == '\n') {
                    lineNum++;
                }
                index++;
            }

            if (lastOpening.top() == "<id>") {
                if (firstId) {
                    firstId = false;
                    id = stoi(txt);
                }
                else
                    followersIds.push_back(stoi(trim(txt)));

            }
            else if (lastOpening.top() == "<name>")
                name = trim(txt);

            else if (lastOpening.top() == "<body>")
                body = trim(txt);

            else if (lastOpening.top() == "<topic>")
                topics.push_back(trim(txt));

            nextIsOpening = false;
            nextIsClosing = true;
        }
        else {
            std::string openTag = lastOpening.top();
            string fc = string(1, openTag[0]);
            std::string closeTag = fc + "/" + openTag.substr(1);
            index += closeTag.length();
            lastOpening.pop();
            for (char ch: closeTag) {
                endFile += ch;
            }

            if (closeTag == "</post>") {
                Post post(body, topics);
                posts.push_back(post);
                body = "";
                topics.clear();
            } else if (closeTag == "</user>") {
                User user(id, name, posts);
                g.add_user(id, user);
                for (const auto &x: followersIds) {
                    g.add_follower(id, x);
                }

                firstId = true;
                name = "";
                posts.clear();
                followersIds.clear();
            } else if (closeTag == "</topics>") {
                expectedIndex = 5;
            } else if (closeTag == "</posts>") {
                expectedIndex = 9;
            } else if (closeTag == "</followers>") {
                expectedIndex = 1;
            } else if (closeTag == "</users>") {
                break;
            }

            nextIsOpening = true;
            nextIsClosing = false;
        }
    }
    return {endFile, g};
}
