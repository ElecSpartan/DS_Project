#include "User.h"

User::User() {
    user_id = 0;
    name = "";
}
User::User(int userId,string &name, vector<Post> &posts) {
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
void User::set_user_id(int userId) {
    user_id = userId;
}
void User::set_name(string &name2) {
    name = name2;
}
void User::set_posts(vector<Post>&posts2) {
    posts = posts2;
}