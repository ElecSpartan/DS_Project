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

vector<User> Graph::user_suggestion(User user){
    vector<User> ret;
    int id = user.get_user_id();
    queue<pair<int,int>> q;
    q.push({id,0});
    int level = 0;
    while(!q.empty()){
        int cur_user = q.front().first;
        int cur_level = q.front().second;
        if(cur_level>=3)
            break;
        q.pop();
        for(auto ch : followersOfUser[cur_user]){
            q.push({ch,cur_level+1});
            if(cur_level+1==2)
                ret.push_back(users[ch]);
        }
    }
    return ret;
}