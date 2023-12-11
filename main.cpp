#include "XML_Parser.h"
int main() {
    string file = read_file("E:\\College\\Data structures\\Project\\DS_Project\\sample.xml");
    Graph g = parse(file);
    return 0;
}