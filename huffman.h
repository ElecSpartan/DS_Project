#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <unordered_map>
#include <vector>
#include <queue>

struct Node {
    int data;
    int frequency;
    Node* left;
    Node* right;

    Node(int data, int freq);
};

struct CompareNodes {
    bool operator()(const Node* a, Node* b) const;
};

using HuffmanPriorityQueue = priority_queue<Node*, vector<Node*>, CompareNodes>; //min heap to put the min two char at the top of pq

Node* buildHuffmanTree(const unordered_map<char, int>& frequencies); //to output the compressed file from the tree
void HuffmanTree_to_file(Node* root, std::ofstream& outFile); //to build the tree from the compressed file
Node* file_to_HuffmanTree(std::ifstream& inFile);
void buildHuffmanCodes(Node* root, const string& code, unordered_map<char, string>& codes);

#endif // HUFFMAN_H
