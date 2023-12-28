#pragma once

#include <unordered_map>
#include <vector>
#include <queue>
#include <fstream>
#include <bitset>
#include <iostream>
#include <string>



struct HuffmanNode {
    int value;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(int val, int freq);
};
struct CompareNodes {
    bool operator()(const HuffmanNode* a, const HuffmanNode* b) const;
};
using HuffmanPriorityQueue = std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes>;
HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& frequencies);
void serializeHuffmanTree(HuffmanNode* root, std::ofstream& outFile);
HuffmanNode* deserializeHuffmanTree(std::ifstream& inFile);
void buildHuffmanCodes(HuffmanNode* root, const std::string& code, std::unordered_map<char, std::string>& codes);


std::unordered_map<char, int> calculateFrequencies(const std::string& input);
std::string compress(const std::string& input, const std::string& compressedPath, const std::string& compressedFilename);


std::string decompress(const std::string& compressedFilename);

