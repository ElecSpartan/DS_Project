#include "compress.h"
#include "huffman.h"
#include <bitset>
#include <iostream>
#include <fstream>
map<char, int> calculateFrequencies(const string& in) {
    map<char, int> frequencies;
    for (char c : input) {
        frequencies[c]++;
    }
    return frequencies;
}

string compress(const string& in, const string& compressedPath, const string& compressedFilename) {
    map<char, int> frequencies = calculateFrequencies(in);
    HuffmanNode* root = buildHuffmanTree(frequencies);

    // Build the full path to the compressed file
    string fullCompressedPath = compressedPath + "\\" + compressedFilename+".bin";

    // Open the compressed file for writing in binary mode
    std::ofstream compressedFile(fullCompressedPath, std::ios::binary);

    // Serialize Huffman tree to compressed file
    HuffmanTree_to_file(root, compressedFile);

    // Compress input and write to file
    map<char, string> codes;
    buildHuffmanCodes(root, "", codes);

    string compressed;
    for (char c : in) {
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
