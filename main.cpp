#include "Network_Analysis.h"
#include "xmlParser.h"
using namespace std;
int main() {
    string file = File::readFile("E:\\College\\Data structures\\Project\\DS_Project\\sample.txt");
    cout<<xmlParser::compress(file);
    cout<<xmlParser::decompress("E:\\College\\Data structures\\Project\\DS_Project\\cmake-build-debug\\compressed_file.bin");
    return 0;
}