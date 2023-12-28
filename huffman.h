#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <unordered_map>
#include <vector>
#include <queue>

struct HuffmanNode {
    int data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(int data, int freq);
};

struct CompareNodes {
    bool operator()(const HuffmanNode* a, HuffmanNode* b) const;
};

using HuffmanPriorityQueue = priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes>; //min heap to put the min two char at the top of pq

HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& frequencies); //to output the compressed file from the tree
void HuffmanTree_to_file(HuffmanNode* root, std::ofstream& outFile); //to build the tree from the compressed file
HuffmanNode* file_to_HuffmanTree(std::ifstream& inFile);
void HuffmanCodes(HuffmanNode* root, const string& code, unordered_map<char, string>& codes);

#endif // HUFFMAN_H
