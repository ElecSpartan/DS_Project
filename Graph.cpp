#include "Graph.h"

Graph::Graph() {
    users.resize(2e5 + 5);
    followersOfUser.resize(2e5 + 5);
}
void Graph::add_user(int userId, User& user) {
    users[userId] = user;
}

void Graph::add_follower(int userId, int followerId) {
    followersOfUser[userId].push_back(followerId);
}