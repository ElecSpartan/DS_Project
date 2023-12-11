#ifndef DS_PROJECT_POST_H
#define DS_PROJECT_POST_H
#include<iostream>
#include<vector>
using namespace std;

class Post {
    string body;
    vector<string> topics;
public:
    Post();
    Post( string& body, vector<string>& topics);
    string get_body();
    vector<string> get_topics();
    void set_body(string &body);
    void set_topics(vector<string>&topics);
};


#endif
