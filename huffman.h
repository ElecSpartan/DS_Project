#pragma once
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <bitset>
#include <iostream>
#include <string>

using namespace std;

class Node {
    int value;
    int freq;
    Node* left;
    Node* right;

public:
    Node(int val, int freq);
    int getFrequency();
    Node* getLeft();
    Node* getRight();
    void setLeft(Node *x);
    void setRight(Node *x);
    int getValue();
};


struct CompareTwoNodes {
    bool operator()(Node* a, Node* b);
};


Node* BuildTree(map<char, int>& freqs);
void serializeTree(Node* root, ofstream& outFile);
Node* deserializeTree(ifstream& inFile);
void buildCodes(Node* root, string code, map<char, string>& codes);


map<char, int> calculateFreqs(const string& input);
string compress(string& input, string path);


string decompress(string path);

