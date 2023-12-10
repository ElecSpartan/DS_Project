#include "XML_Parser.H"
int main() {
    vector<int>errors_in_line;
    pair<string, Graph> p = parsing_with_correcting_errors("E:\\College\\Data structures\\Project\\DS_Project\\sample.xml",errors_in_line);
    string endFile = p.first;
    Graph g = p.second;
    cout << endFile;
    return 0;
}