#include "XML_Parser.h"
#include "Error_detection_and_correction.h"
int main() {

    string file = read_file("E:\\College\\Data structures\\Project\\DS_Project\\sample.xml");
    cout << xml_is_correct(file);
    Graph g = parse(file);

    return 0;
}