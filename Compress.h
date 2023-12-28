#pragma once
#ifndef COMPRESS_H
#define COMPRESS_H

#include <string>
#include <map>

map<char, int> calculateFrequencies(const string& in);
string compress(const string& in, const string& compressedPath, const string& compressedFilename);

#endif // COMPRESS_H
