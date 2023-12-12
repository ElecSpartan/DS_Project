#include "XML_Parser.h"
int main() {
//    if(!detection_function("C:\\DS_Project\\sample.xml")){
//        cout<<"Error!";
//        return 0;
//    }
    string file = read_file("C:\\DS_Project\\Sample (2).xml");
    Graph g = parse(file);
    return 0;
}