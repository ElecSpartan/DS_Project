#include "Error_detection_and_correction.h"
int main() {

    string file = read_file("E:\\College\\Data structures\\Project\\DS_Project\\sample.xml");
    Graph g = parse(file);
    visualize_graph(g);
    return 0;
}