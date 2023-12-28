#include "huffman.h"


// Node class functions implementation
Node::Node(int val, int freqq) : value(val), freq(freqq), left(nullptr), right(nullptr) {}
int Node::getFrequency() {
    return freq;
}
Node* Node::getLeft() {
    return left;
}
Node* Node::getRight() {
    return right;
}
void Node::setLeft(Node *x) {
    left = x;
}
void Node::setRight(Node *x) {
    right = x;
}
int Node::getValue() {
    return value;
}


// CompareTwoNodes
bool CompareTwoNodes::operator()(Node* a, Node* b) {
    return a->getFrequency() > b->getFrequency();
}


//Huffman Tree
Node* BuildTree(map<char, int>& freqs) {
    priority_queue<Node*, vector<Node*>, CompareTwoNodes> pq;

    for (auto& p : freqs) {
        pq.push(new Node(p.first, p.second));
    }

    while (pq.size() > 1) {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        Node *newNode = new Node(0, left->getFrequency() + right->getFrequency());
        newNode->setLeft(left);
        newNode->setRight(right);

        pq.push(newNode);
    }

    return pq.top();
}
void serializeTree(Node* root, ofstream& outputFile) {
    if (!root)
        return;

    int value = root->getValue();
    int freq = root->getFrequency();
    if (root->getLeft() || root->getRight()) {
        outputFile.put('\1');

        outputFile.write(reinterpret_cast<char *>(&value), sizeof(char));
        outputFile.write(reinterpret_cast<char *>(&freq), sizeof(int));

        serializeTree(root->getLeft(), outputFile);
        serializeTree(root->getRight(), outputFile);
    } else {
        outputFile.put('\0');
        outputFile.write(reinterpret_cast<char *>(&value), sizeof(char));
    }
}
Node* deserializeTree(ifstream& inputFile) {
    char m;
    inputFile.get(m);

    if (m == '\1') {
        int value, freq;
        inputFile.read(reinterpret_cast<char*>(&value), sizeof(char));
        inputFile.read(reinterpret_cast<char*>(&freq), sizeof(int));

        Node* newNode = new Node(value, freq);
        newNode->setLeft( deserializeTree(inputFile));
        newNode->setRight( deserializeTree(inputFile));

        return newNode;
    }
    else if (m == '\0') {
        int value;
        inputFile.read(reinterpret_cast<char*>(&value), sizeof(char));

        return new Node(value, 0);
    }
    else {
        return nullptr;
    }
}
void buildCodes(Node* root, string code, map<char, string>& codes) {
    if (!root)
        return;

    if (!root->getLeft() && !root->getRight()) {
        codes[root->getValue()] = code;
        return;
    }

    buildCodes(root->getLeft(), code + "0", codes);
    buildCodes(root->getRight(), code + "1", codes);
}




map<char, int> calculateFreqs(const string& input) {
    map<char, int> freqs;
    for (char c: input) {
        freqs[c]++;
    }
    return freqs;
}
string compress(string& input, string path) {
    map<char, int> freqs = calculateFreqs(input);
    Node *root = BuildTree(freqs);

    ofstream compressedFile(path, ios::binary);


    serializeTree(root, compressedFile);


    map<char, string> codes;
    buildCodes(root, "", codes);

    string compressed;
    for (char c: input) {
        compressed += codes[c];
    }
    cout<<compressed;


    bitset<8> bits;
    for (int i = 0; i < compressed.size(); ++i) {
        bits[7 - (i % 8)] = compressed[i] == '1';
        if (i % 8 == 7 || i == compressed.size() - 1) {
            char byte = static_cast<char>(bits.to_ulong());
            compressedFile.write(&byte, sizeof(char));
        }
    }

    compressedFile.close();
    return compressed;
}

string decompress(string path) {
    ifstream compressed(path, ios::binary);
    Node *root;

    root = deserializeTree(compressed);

    string compressedBits;
    char c;
    while (compressed.get(c)) {
        bitset<8> bits(c);
        compressedBits += bits.to_string();
    }

    compressed.close();

    string decompressed;
    Node *Node = root;

    for (char bit: compressedBits) {
        if (bit == '0') {
            Node = Node->getLeft();
        } else {
            Node = Node->getRight();
        }

        if (!Node->getLeft() && !Node->getRight()) {
            decompressed += (char) (Node->getValue());
            Node = root;
        }
    }

    return decompressed;
}

