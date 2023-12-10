#include "User.h"

User::User(){}
User::User(int &userId,string &name, vector<Post> &posts) {
    this->user_id = userId;
    this->name = name;
    this->posts = posts;
}
int User::get_user_id() {
    return user_id;
}
string User::get_name() {
    return name;
}
vector<Post> User::get_posts() {
    return posts;
}