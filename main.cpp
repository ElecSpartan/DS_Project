#include "XML_Parser.h"
#include "Error_detection_and_correction.h"
int main() {

    string file = read_file("E:\\jj.txt");
    vector<pair<pair<int, int>, string>> errorss = errors(file);
    for(auto &x : errorss)
        cout<<x.second<<'\n';


    cout<<'\n';
    cout<<correct_xml(file);
    return 0;
}