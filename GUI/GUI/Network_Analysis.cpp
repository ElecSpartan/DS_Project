#include "Network_Analysis.h"
Graph g;

// lesa el post search

// post class methods
Post::Post() {
    body = "";
}

Post::Post(std::string &body,std::vector<std::string> &topics) {
    this->body = body;
    this->topics = topics;
}

std::string Post::get_body() {
    return body;
}

std::vector<std::string> Post::get_topics() {
    return topics;
}

void Post::set_body(std::string &body2) {
    body = body2;
}

void Post::set_topics(std::vector<std::string> &topics2) {
    topics = topics2;
}


// user class methods
User::User() {
    user_id = 0;
    name = "";
}

User::User(int userId,std::string &name, std::vector<Post> &posts) {
    this->user_id = userId;
    this->name = name;
    this->posts = posts;
}

int User::get_user_id() {
    return user_id;
}

std::string User::get_name() {
    return name;
}

std::vector<Post> User::get_posts() {
    return posts;
}

void User::set_user_id(int userId) {
    user_id = userId;
}

void User::set_name(std::string &name2) {
    name = name2;
}

void User::set_posts(std::vector<Post>&posts2) {
    posts = posts2;
}



// Graph class methods
void Graph::add_user(int userId, User& user) {
    users[userId] = user;
}

void Graph::add_follower(int userId, int followerId) {
    followersOfUser[userId].push_back(followerId);
    freq[followerId]++;
}

std::vector<User> Graph::most_connections() {
    std::vector<User> ret;

    int mx = -1;
    for (auto x: freq)
        mx = std::max(mx, x.second);

    for (auto x: freq) {
        if (x.second == mx)
            ret.push_back(users[x.first]);
    }
    return ret;
}

std::vector<User> Graph::most_followers() {
    int mx = -1;
    std::vector<User> ret;
    for (auto &x: users) {
        mx = std::max(mx,(int)followersOfUser[x.first].size());
    }
    for (auto &x: users) {
        if (followersOfUser[x.first].size() == mx)
            ret.push_back(x.second);
    }
    return ret;
}

std::vector<User> Graph::user_suggestion(User user){
    std::vector<User> ret;
    int id = user.get_user_id();
    std::queue<int> q;
    std::map<int,int> dis;
    q.push(id);
    dis[id] = 0;
    while(!q.empty()){
        int cur_user = q.front();
        int cur_level = dis[cur_user]+1;
        if(cur_level>=3)
            break;
        q.pop();
        for(auto ch : followersOfUser[cur_user]){
            if(dis[ch] > cur_level || (!dis[ch]&&ch!=id)){
                dis[ch] = cur_level;
                q.push(ch);
                if(cur_level==2)
                    ret.push_back(users[ch]);
            }
        }
    }
    return ret;
}

std::vector<User> Graph::mutual_followers(User user1 , User user2) {
    std::vector<User> ret;
    std::vector<int> v1 = followersOfUser[user1.get_user_id()], v2 = followersOfUser[user2.get_user_id()];

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    int p1 = 0, p2 = 0;
    while (p1 < v1.size() && p2 < v2.size()) {
        if (v1[p1] == v2[p2] && v1[p1] != user1.get_user_id() && v1[p1] != user2.get_user_id()) {
            ret.push_back(users[v1[p1]]);
            p1++;
            p2++;
        } else if (v1[p1] > v2[p2])
            p2++;
        else
            p1++;
    }
    return ret;
}
std::map<int,User> Graph::get_users() {
    return users;
}

User Graph::get_user_by_id(int id) {
    return users[id];
}

std::map<int,std::vector<int>> Graph::get_followersOfUsers() {
    return followersOfUser;
}

std::vector<User> Graph::Search_in_post(std::string word) {
    std::vector<User> ret;
    std::map<int, User> userss = g.get_users();
    for (auto x: userss) {
        std::vector<Post> v = x.second.get_posts();
        for (auto y: v) {
            std::string Body = y.get_body();
            std::vector<std::string> Topics = y.get_topics();
            if (Body.find(word) != std::string::npos) {
                ret.push_back(x.second);
                break;
            } else {
                bool break_flag = false;
                for (auto &t: Topics) {
                    if (t.find(word) != std::string::npos) {
                        ret.push_back(x.second);
                        break_flag = true;
                        break;
                    }
                }
                if (break_flag) break;
            }
        }
    }
    return ret;
}


// Network Analysis class methods
bool Network_Analysis::temp_is_dummy(std::string &temp) {
    bool is_dummy = 1;
    for (auto ch: temp)
        is_dummy = is_dummy && (ch == '\n' || ch == ' ');


    return is_dummy;
}

std::string Network_Analysis::trim(std::string&x) {
    std::string y = "";
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

std::vector<std::string> Network_Analysis::divide_string_for_graph(std::string &file) {
    std::vector<std::string> divided_file;
    std::string temp = "";
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

Graph Network_Analysis::parse(std::string &file) {
    Graph gg;
    std::vector<std::string> divided_file = divide_string_for_graph(file);
    User* obj_ptr;
    Post* post_ptr;
    std::vector<std::string> topics;
    std::vector<Post> posts;
    bool inside_followers = false;
    for(int i=0;i<divided_file.size();i++){
        std::string s = divided_file[i];
        if(s=="<user>")
            obj_ptr = new User;


        if(s=="<id>") {
            if (!inside_followers)
                obj_ptr->set_user_id(stoi(divided_file[i + 1]));
            else {
                gg.add_follower(obj_ptr->get_user_id(), stoi(divided_file[i + 1]));
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
            gg.add_user(obj_ptr->get_user_id(),*obj_ptr);
            delete obj_ptr;
        }
    }
    g = gg;
    return g;
}

void Network_Analysis::UsingParse(std::string file){
    g=parse(file);
}


std::string Network_Analysis::visualize_graph() {
    std::string s = "";
    s += "digraph test{\n";

    std::map<int, User> users = g.get_users();
    std::map<int, std::vector<int>> followersOfUser = g.get_followersOfUsers();
    for (auto x: users) {
        s+= "\"";
        s += x.second.get_name();
        s+="\"";
        s += "  ->  { ";
        int num = 0;
        for (auto id: followersOfUser[x.first]) {
            s += "\"";
            s += users[id].get_name();
            s += "\"";
            if (num != followersOfUser[x.first].size() - 1)
                s += " ";

            num++;
        }
        s += " }\n";
    }

    s += "\n}";
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path filePath = currentPath / "graph.dot";

    File::outputFile(filePath.string(), s);
    system((currentPath.string() + "\\GraphViz\\dot -Tpng -O graph.dot").c_str());

    return (currentPath /"graph.dot.png").string();
}



std::string Network_Analysis::most_followers() {
    std::vector<User> users = g.most_followers();
    std::string s = "";
    int i = 1;
    for (auto &u: users) {
        s += std::to_string(i) + ") " + "User with id : " + std::to_string(u.get_user_id()) + " and name : ";
        s += u.get_name();
        s += '\n';
        i++;
    }
    return s;
}

std::string Network_Analysis::most_connections() {
    std::vector<User> users = g.most_connections();
    std::string s = "";
    int i = 1;
    for (auto &u: users) {
        s += std::to_string(i) + ") " + "User with id : " + std::to_string(u.get_user_id()) + " and name : ";
        s += u.get_name();
        s += '\n';
        i++;
    }
    return s;
}

std::string Network_Analysis::mutual_followers(int user1_id, int user2_id) {
    User user1 = g.get_user_by_id(user1_id);
    User user2 = g.get_user_by_id(user2_id);
    std::vector<User> users = g.mutual_followers(user1,user2);
    std::string s = "";
    if(users.empty())
        return "There are no mutual followers";
    int i = 1;
    std::set<int>ss;
    for (auto &u: users) {

        if (!ss.count(u.get_user_id())) {
            s += std::to_string(i) + ") " + "User with id : " + std::to_string(u.get_user_id()) + " and name : ";
            s += u.get_name();
            s += '\n';
            i++;
        }

        ss.insert(u.get_user_id());
    }
    return s;
}
std::string Network_Analysis::user_suggestion(int user_id) {
    User user = g.get_user_by_id(user_id);
    std::string s = "";
    std::vector<User> users = g.user_suggestion(user);
    if(users.empty())
        return "There are no suggestions";
    int i = 1;
    std::set<int>ss;
    for (auto &u: users) {

        if (!ss.count(u.get_user_id())) {
            s += std::to_string(i) + ") " + "User with id : " + std::to_string(u.get_user_id()) + " and name : ";
            s += u.get_name();
            s += '\n';
            i++;
        }

        ss.insert(u.get_user_id());
    }
    return s;
}

std::string Network_Analysis::post_search(std::string word) {
    std::vector<User> users = g.Search_in_post(word);
    std::string s = "";
    int i = 1;
    for (auto &u: users) {
        s += std::to_string(i) + ") " + "User with id : " + std::to_string(u.get_user_id()) + " and name : ";
        s += u.get_name();
        s += " posted about the word ( " + word + " ).";
        s += '\n';
        i++;
    }
    return s;
}

