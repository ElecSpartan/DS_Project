#include "huffman.h"
using namespace std;

HuffmanNode::HuffmanNode(int val, int freq) : value(val), frequency(freq), left(nullptr), right(nullptr) {}
bool CompareNodes::operator()(const HuffmanNode* a, const HuffmanNode* b) const {
    return a->frequency > b->frequency;
}
HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& frequencies) {
    HuffmanPriorityQueue pq;

    for (auto& pair : frequencies) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode(0, left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}
void serializeHuffmanTree(HuffmanNode* root, std::ofstream& outFile) {
    if (!root)
        return;

    if (root->left || root->right) {
        outFile.put('\1');  // Non-leaf node marker
        outFile.write(reinterpret_cast<const char*>(&root->value), sizeof(char));
        outFile.write(reinterpret_cast<const char*>(&root->frequency), sizeof(int));

        serializeHuffmanTree(root->left, outFile);
        serializeHuffmanTree(root->right, outFile);
    }
    else {
        outFile.put('\0');  // Leaf node marker
        outFile.write(reinterpret_cast<const char*>(&root->value), sizeof(char));
    }
}
HuffmanNode* deserializeHuffmanTree(std::ifstream& inFile) {
    char marker;
    inFile.get(marker);

    if (marker == '\1') {
        int value, frequency;
        inFile.read(reinterpret_cast<char*>(&value), sizeof(char));
        inFile.read(reinterpret_cast<char*>(&frequency), sizeof(int));

        HuffmanNode* newNode = new HuffmanNode(value, frequency);
        newNode->left = deserializeHuffmanTree(inFile);
        newNode->right = deserializeHuffmanTree(inFile);

        return newNode;
    }
    else if (marker == '\0') {
        int value;
        inFile.read(reinterpret_cast<char*>(&value), sizeof(char));

        return new HuffmanNode(value, 0);
    }
    else {
        // Handle error or unexpected marker
        return nullptr;
    }
}
void buildHuffmanCodes(HuffmanNode* root, const std::string& code, std::unordered_map<char, std::string>& codes) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        codes[root->value] = code;
        return;
    }

    buildHuffmanCodes(root->left, code + "0", codes);
    buildHuffmanCodes(root->right, code + "1", codes);
}

std::unordered_map<char, int> calculateFrequencies(const std::string& input) {
    std::unordered_map<char, int> frequencies;
    for (char c : input) {
        frequencies[c]++;
    }
    return frequencies;
}
std::string compress(const std::string& input, const std::string& compressedPath, const std::string& compressedFilename) {
    std::unordered_map<char, int> frequencies = calculateFrequencies(input);
    HuffmanNode* root = buildHuffmanTree(frequencies);

    // Build the full path to the compressed file
    std::string fullCompressedPath = compressedPath + "\\" + compressedFilename+".bin";

    // Open the compressed file for writing in binary mode
    std::ofstream compressedFile(fullCompressedPath, std::ios::binary);

    // Serialize Huffman tree to compressed file
    serializeHuffmanTree(root, compressedFile);

    // Compress input and write to file
    std::unordered_map<char, std::string> codes;
    buildHuffmanCodes(root, "", codes);

    std::string compressed;
    for (char c : input) {
        compressed += codes[c];
    }

    // Convert the binary string to bytes and write to the compressed file
    std::bitset<8> bits;
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

string decompress(const string& compressedFilename) {
    ifstream compressedFile(compressedFilename, ios::binary);
    HuffmanNode* root;
    // Deserialize Huffman tree from compressed file
    root = deserializeHuffmanTree(compressedFile);

    // Decompress the remaining data
    std::string compressedBits;
    char c;
    while (compressedFile.get(c)) {
        std::bitset<8> bits(c);
        compressedBits += bits.to_string();
    }

    compressedFile.close();

    std::string decompressed;
    HuffmanNode* currentNode = root;

    for (char bit : compressedBits) {
        if (bit == '0') {
            currentNode = currentNode->left;
        }
        else {
            currentNode = currentNode->right;
        }

        if (!currentNode->left && !currentNode->right) {
            decompressed += static_cast<char>(currentNode->value);
            currentNode = root;
        }
    }

    return decompressed;
}

