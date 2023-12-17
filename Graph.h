#ifndef DS_PROJECT_GRAPH_H
#define DS_PROJECT_GRAPH_H
#include "User.h"

class Graph {
    vector<User> users;
    vector<vector<int>> followersOfUser;
    vector<int> freq;
public:
    Graph();
    void add_user(int userId, User& user);
    void add_follower(int userId, int followerId);
    vector<User> most_followers();
    vector<User> most_connections();
    vector<User> mutual_followers(User user1 , User user2);
    vector<User> user_suggestion(User user);
};

#endif
