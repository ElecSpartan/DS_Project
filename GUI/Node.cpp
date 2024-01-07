#include "Node.h"


Node::Node () {
    parent = nullptr;
}

Node::Node(std::string name, Node* parent) {
    this->name = name;
    this->parent = parent;
}

std::string Node::getName() {
    return name;
}

Node* Node::getParent() {
    return parent;
}

std::vector<Node*> Node::getChildren() {
    return children;
}

void Node::setName(std::string name) {
    this->name = name;
}

void Node::appendChild(Node* child) {
    this->children.push_back(child);
}