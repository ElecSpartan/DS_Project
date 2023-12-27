#include "Error_detection_and_correction.h"
int main() {

    string file = read_file("E:\\jj.txt");
    vector<pair<int, bool>> v = get_errors(file);
    for (auto p: v)
        cout << p.first << " " << p.second <<"\n";
    return 0;
}