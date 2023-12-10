#ifndef DS_PROJECT_USER_H
#define DS_PROJECT_USER_H
#include "Post.h"

class User {
    int user_id;
    string name;
    vector<Post> posts;
public:
    User();
    User(int& userId,string& name,vector<Post>& posts);
    int get_user_id();
    string get_name();
    vector<Post> get_posts();
};


#endif
