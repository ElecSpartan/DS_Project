#ifndef DS_PROJECT_GRAPH_H
#define DS_PROJECT_GRAPH_H
#include "User.h"

class Graph {
    vector<User> users;
    vector<vector<int>> followersOfUser;
public:
    Graph();
    void add_user(int userId, User& user);
    void add_follower(int userId, int followerId);
};

#endif
