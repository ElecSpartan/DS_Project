#include "Network_Analysis.h"
using namespace std;
int main() {
    string file = File::readFile("E:\\College\\Data structures\\Project\\DS_Project\\sample.txt");
    Network_Analysis::graph_and_visualization(file);
    return 0;
}