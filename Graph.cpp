#include <bits/stdc++.h>
#include "Graph.h"

void Graph::add_user(int userId, User& user) {
    users[userId] = user;
}

void Graph::add_follower(int userId, int followerId) {
    followersOfUser[userId].push_back(followerId);
    freq[followerId]++;
}

vector<User> Graph::most_connections() {
    vector<User> ret;

    int mx = -1;
    for (auto x: freq)
        mx = max(mx, x.second);

    for (auto x: freq) {
        if (x.second == mx)
            ret.push_back(users[x.first]);
    }
    return ret;
}

vector<User> Graph::most_followers() {
    int mx = -1;
    vector<User> ret;
    for (auto &x: users) {
        if (followersOfUser[x.first].size() > mx)
            mx = followersOfUser[x.first].size();
    }
    for (auto &x: users) {
        if (followersOfUser[x.first].size() == mx)
            ret.push_back(x.second);
    }
    return ret;
}

vector<User> Graph::user_suggestion(User user){
    vector<User> ret;
    int id = user.get_user_id();
    queue<pair<int,int>> q;
    q.push({id,0});
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

vector<User> Graph::mutual_followers(User user1 , User user2){
    vector<User> ret;
    sort(followersOfUser[user1.get_user_id()].begin(),followersOfUser[user1.get_user_id()].end());
    sort(followersOfUser[user2.get_user_id()].begin(),followersOfUser[user2.get_user_id()].end());
    int p1 = 0 , p2 = 0;
    while(p1<followersOfUser[user1.get_user_id()].size() && p2 < followersOfUser[user2.get_user_id()].size()){
        if(followersOfUser[user1.get_user_id()][p1] == followersOfUser[user2.get_user_id()][p2] ){
            ret.push_back(users[followersOfUser[user1.get_user_id()][p1]]);
            p1++;
            p2++;
        }
        else if(followersOfUser[user1.get_user_id()][p1] > followersOfUser[user2.get_user_id()][p2] )
            p2++;
        else
            p1++;
    }
    return ret;
}

map<int,User> Graph::get_users() {
    return users;
}

map<int,vector<int>> Graph::get_followersOfUsers() {
    return followersOfUser;
}