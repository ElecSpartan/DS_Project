#include "Network_Analysis.h"
#include "xmlParser.h"
using namespace std;
int main() {
    string file = File::readFile("E:\\College\\Data structures\\Project\\DS_Project\\sample.txt");
    Network_Analysis::graph_and_visualization(file);
    cout<<Network_Analysis::post_search("economy");
    return 0;
}