#include <bits/stdc++.h>
#include "File.h"
#include "xmlParser.h"
using namespace std;

int main() {
    File* input_file = new File("sample.xml");
    File* output_file = new File("last_test.xml");

    string input_xml = input_file->readFile();
    string output = xmlParser::toJsonByTrees(input_xml);
    output_file->outputFile(output);

    return 0;
}