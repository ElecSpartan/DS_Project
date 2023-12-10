#include "Graph.h"

Graph::Graph() {
    users.resize(2e5 + 5);
    followersOfUser.resize(2e5 + 5);
}
void Graph::add_user(const int& userId, const User& user) {
    users[userId] = user;
}

void Graph::add_follower(const int userId, const int& followerId) {
    followersOfUser[userId].push_back(followerId);
}