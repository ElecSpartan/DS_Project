#pragma once
#include <iostream>
#include <vector>

class Node {
    private:
        std::string name;
        Node* parent;
        std::vector<Node*> children;

    public:
        Node();
        Node(std::string name, Node *parent);
        std::string getName();
        Node* getParent();
        std::vector<Node*> getChildren();
        void setName(std::string name);
        void appendChild(Node *child);
};