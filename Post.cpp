//
// Created by Mazen on 10-Dec-23.
//

#include "Post.h"


Post::Post(std::string &body,vector<string> &topics) {
    this->body = body;
    this->topics = topics;
}

string Post::get_body() {
    return body;
}

vector<string> Post::get_topics() {
    return topics;
}