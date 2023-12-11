#include "Post.h"

Post::Post() {
    body = "";
}

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

void Post::set_body(string &body2) {
    body = body2;
}
void Post::set_topics(vector<std::string> &topics2) {
    topics = topics2;
}