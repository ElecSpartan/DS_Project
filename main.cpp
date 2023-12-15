#include "XML_Parser.h"
#include "Error_detection_and_correction.h"
int main() {

    string file = read_file("E:\\jj.txt");
    cout << correct_xml(file);

    return 0;
}