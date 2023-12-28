#ifndef DS_PROJECT_GRAPH_H
#define DS_PROJECT_GRAPH_H
#include "User.h"
#include <map>

class Graph {
    map<int, User> users;
    map<int, vector<int>> followersOfUser;
    map<int,int> freq;
public:

    void add_user(int userId, User &user);

    void add_follower(int userId, int followerId);

    vector<User> most_followers();

    vector<User> most_connections();

    vector<User> mutual_followers(User user1, User user2);

    vector<User> user_suggestion(User user);

    map<int,User> get_users();

    map<int,vector<int>> get_followersOfUsers();
};

#endif
