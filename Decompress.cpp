#include "decompress.h"
#include "huffman.h"
#include <bitset>
#include <iostream>
#include <fstream>
using namespace std;
  string decompress(const string& compressedFilePath) {
    ifstream compressedFile(compressedFilePath, ios::binary);
    HuffmanNode* root;
    // Deserialize Huffman tree from compressed file
    root = file_to_HuffmanTree(compressedFile);

    // Decompress the remaining data
    string Bits;
    char c;
    while (compressedFile.get(c)) {
        bitset<8> bits(c);
        Bits += bits.to_string();
    }

    compressedFile.close();

    std::string decompressed;
    HuffmanNode* currentNode = root;

    for (char bit : Bits) {
        if (bit == '0') {
            currentNode = currentNode->left;
        }
        else {
            currentNode = currentNode->right;
        }

        if (!currentNode->left && !currentNode->right) { //leaf node
            decompressed += static_cast<char>(currentNode->value);
            currentNode = root;
        }
    }

    return decompressed;
}
