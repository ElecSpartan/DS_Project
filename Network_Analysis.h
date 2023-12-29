#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include "File.h"

class Post {
    std::string body;
    std::vector<std::string> topics;
public:
    Post();
    Post(std::string& body,std::vector<std::string>& topics);
    std::string get_body();
    std::vector<std::string> get_topics();
    void set_body(std::string &body);
    void set_topics(std::vector<std::string>&topics);
};
class User {
    int user_id;
    std::string name;
    std::vector<Post> posts;
public:
    User();
    User(int userId,std::string& name,std::vector<Post>& posts);
    int get_user_id();
    std::string get_name();
    std::vector<Post> get_posts();
    void set_user_id(int userId);
    void set_name(std::string &name2);
    void set_posts(std::vector<Post>&posts2);
};
class Graph {
    std::map<int, User> users;
    std::map<int, std::vector<int>> followersOfUser;
    std::map<int,int> freq;
public:

    void add_user(int userId, User &user);

    void add_follower(int userId, int followerId);

    std::vector<User> most_followers();

    std::vector<User> most_connections();

    std::vector<User> mutual_followers(User user1, User user2);

    std::vector<User> user_suggestion(User user);

    std::map<int,User> get_users();

    std::vector<std::pair<std::string,std::string>> Search_in_post(std::string word);

    User get_user_by_id(int id);

    std::map<int,std::vector<int>> get_followersOfUsers();
};
class Network_Analysis {
private:

    static bool temp_is_dummy(std::string &temp);
    static std::string trim(std::string&x);
    static std::vector<std::string> divide_string_for_graph(std::string &file);
    static Graph parse(std::string &file);
    static void visualize_graph();
public:
    static void graph_and_visualization(std::string file);

    static std::string most_followers();

    static std::string most_connections();

    static std::string mutual_followers(int user1_id, int user2_id) ;

    static std::string user_suggestion(int user_id);

    static std::string post_search(std::string word);
};


