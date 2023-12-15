#include <bits/stdc++.h>
#include "Graph.h"

Graph::Graph() {
    users.resize(2e5 + 5);
    followersOfUser.resize(2e5 + 5);
    people_that_user_follow.resize(2e5+5);
}
void Graph::add_user(int userId, User& user) {
    users[userId] = user;
}

void Graph::add_follower(int userId, int followerId) {
    followersOfUser[userId].push_back(followerId);
    people_that_user_follow[followerId].push_back(userId);
}

vector<User> Graph::most_connections() {
    int mx = -1;
    vector<User> ret;
    for(auto x : users){
        if(people_that_user_follow[x.get_user_id()].size() > mx)
            mx = people_that_user_follow[x.get_user_id()].size();
    }
    for(auto x : users){
        if(people_that_user_follow[x.get_user_id()].size() == mx)
            ret.push_back(x);
    }
    return ret;
}


vector<User> Graph::most_followers() {
    int mx = -1;
    vector<User> ret;
    for(auto x : users){
        if(followersOfUser[x.get_user_id()].size() > mx)
            mx = followersOfUser[x.get_user_id()].size();
    }
    for(auto x : users){
        if(followersOfUser[x.get_user_id()].size() == mx)
            ret.push_back(x);
    }
    return ret;
}