#include "Network_Analysis.h"
#include "xmlParser.h"
using namespace std;
int main() {
    string file = File::readFile("E:\\College\\Data structures\\Project\\DS_Project\\sample.txt");
    cout << xmlParser::compressAndWriteToFile(file);
    cout << "\n\n"<< xmlParser::readAndDecompressFromFile(
            "E:\\College\\Data structures\\Project\\DS_Project\\cmake-build-debug\\compressed_file.bin");
    return 0;
}