#include "Error_detection_and_correction.h"
int main() {

    string file = read_file("E:\\jj.txt");
    cout << correct_xml(file);
    vector<pair<int, bool>> v = get_errors();

    cout<<'\n';
    for (auto x: v)
        cout << x.first << " , " << x.second << '\n';
    return 0;
}