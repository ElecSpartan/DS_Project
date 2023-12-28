#include <bits/stdc++.h>
#include "xmlParser.cpp"
using namespace std;

string read_file (string path) {
    ifstream in(path);

    stringstream buffer;
    buffer << in.rdbuf();
    in.close();

    return buffer.str();
}

void output_file (string path, string output_string) {
    ifstream in(path);

    ofstream out(path);
    out << output_string;
    out.close();
}

class Node {
    private:
        string name;
        Node* parent;
        vector<Node*> children;

    public:
        Node () {
            parent = nullptr;
        }

        Node (string name, Node* parent) {
            this->name = name;
            this->parent = parent;
        }

        string getName() {
            return name;
        }

        Node* getParent() {
            return parent;
        }

        vector<Node*> getChildren() {
            return children;
        }

        void setName(string name) {
            this->name = name;
        }

        void appendChild(Node* child) {
            this->children.push_back(child);
        }
};


void create_tree (string xml_input, Node* root) {
    int start = xml_input.find('>');
    root->setName(xml_input.substr(1, start - 1));
    int i = start + 1;
    while (i < xml_input.length()) {
        if (xml_input[i] != '<') {
            start = xml_input.find('<', i);
            root->appendChild(new Node(xml_input.substr(i, start - i), root));
            i = start;
        }

        if (xml_input[i + 1] == '/') {
            root = root->getParent();
            i = xml_input.find('>', i) + 1;
            continue;
        }

        int end = xml_input.find('>', i);
        string tag_name = xml_input.substr(i + 1, end - i - 1);
        Node *node = new Node(tag_name, root);
        root->appendChild(node);
        root = node;
        i = end + 1;
    }
}


void printTree (Node* root, int level) {
    for (int i = 0; i < level; i++) cout << "    ";

    if ((root->getChildren()).size() == 0) {
        cout << "Parent = " << root->getParent()->getName() << " / Value = " << root->getName() << '\n';
        return;
    }

    if (root->getParent() == nullptr) {
        cout << "Parent = ROOT Children:\n";
    } else {
        cout << "Parent = " << root->getParent()->getName() << ":\n";
    }

    for (auto &it : root->getChildren()) {
        printTree (it, level + 1);
    }
}


void printJSON (Node* root, string& json_output, int level, bool is_array) {
    string indentation = "    ", indent = "";
    for (int i = 0; i < level; i++) indent += indentation;
    
    int children_count = root->getChildren().size();

    if (children_count == 0) {
        json_output += '"';
        json_output += root->getName();
        json_output += '"';
        return;
    }

    json_output += indent;

    if (!is_array) {
        json_output += '"';
        json_output += root->getName();
        json_output += "\": ";
    }

    if (root->getChildren()[0]->getChildren().size() != 0) {
        json_output += "{\n";
    }

    bool are_same_children = false;
    if (children_count > 1 && root->getChildren()[0]->getName() == root->getChildren()[1]->getName()) {
        are_same_children = true;
    }

    if (are_same_children) {
        json_output += indent;
        json_output += indentation;
        json_output += '"';
        json_output += root->getChildren()[0]->getName();
        json_output += "\": [\n";
    }

    for (int j = 0; j < children_count; j++) {
        printJSON(root->getChildren()[j], json_output, level + 1 + are_same_children, are_same_children);
        if (j < children_count - 1) {
            json_output += ",\n";
        }
    }

    if (are_same_children) {
        json_output += '\n';
        json_output += indent;
        json_output += indentation;
        json_output += ']';
    }

    if (root->getChildren()[0]->getChildren().size() != 0) {
        json_output += '\n';
        json_output += indent;
        json_output += '}';
    }
}


int main() {
    string input_string = read_file("sample.xml");
    string minified_string = xmlParser::minify(input_string);

    Node* root = new Node();
    create_tree(minified_string, root);

    string json_string = "{\n";
    printJSON(root, json_string, 1, false);
    json_string += "\n}";

    output_file("tree_test.json", json_string);

    return 0;
}