#include "huffman.h"
#include <fstream>

Node::Node(int data, int freq) : data(data), frequency(freq), left(nullptr), right(nullptr) {}

bool CompareNodes::operator()(const Node* a, const Node* b) const {
    return a->frequency > b->frequency;
}
Node* buildHuffmanTree(const std::unordered_map<char, int>& frequencies) {
    HuffmanPriorityQueue pq;

    for (auto& pair : frequencies) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* newNode = new Node(0, left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }
    return pq.top();
}

void HuffmanTree_to_file(Node* root, std::ofstream& outFile) {
    if (!root)
        return;

    if (root->left || root->right) {
        outFile.put('\1');  // Non-leaf node marker
        outFile.write(reinterpret_cast<const char*>(&root->data), sizeof(char));
        outFile.write(reinterpret_cast<const char*>(&root->frequency), sizeof(int));

        HuffmanTree_to_file(root->left, outFile);
        HuffmanTree_to_file(root->right, outFile);
    }
    else {
        outFile.put('\0');  // Leaf node marker
        outFile.write(reinterpret_cast<const char*>(&root->data), sizeof(char));
    }
}

HuffmanNode* file_to_HuffmanTree(std::ifstream& inFile) {
    char marker;
    inFile.get(marker);

    if (marker == '\1') {
        int value, frequency;
        inFile.read(reinterpret_cast<char*>(&value), sizeof(char));
        inFile.read(reinterpret_cast<char*>(&frequency), sizeof(int));

        Node* newNode = new Node(value, frequency);
        newNode->left = file_to_HuffmanTree(inFile);
        newNode->right = file_to_HuffmanTree(inFile);

        return newNode;
    }
    else if (marker == '\0') {
        int value;
        inFile.read(reinterpret_cast<char*>(&value), sizeof(char));

        return new Node(value, 0);
    }
    else {
        // Handle error or unexpected marker
        return nullptr;
    }
}

void HuffmanCodes(Node* root, const std::string& code, std::unordered_map<char, std::string>& codes) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        codes[root->data] = code;
        return;
    }

    HuffmanCodes(root->left, code + "0", codes);
    HuffmanCodes(root->right, code + "1", codes);
}
