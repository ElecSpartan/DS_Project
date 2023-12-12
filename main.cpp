#include "XML_Parser.h"
int main() {
//    if(!detection_function("C:\\DS_Project\\sample.xml")){
//        cout<<"Error!";
//        return 0;
//    }
    string file = read_file("E:\\College\\Data structures\\Project\\DS_Project\\sample.xml");
    Graph g = parse(file);

    return 0;
}