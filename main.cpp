#include "Error_detection_and_correction.h"
int main() {

    string file = read_file("E:\\jj.txt");
    write_to_file("E:\\kk.txt", correct_xml(file));
    vector<pair<int,bool>>v = get_errors(file);
    for(auto x : v) {
        cout << "Missing ";
        if (x.second)
            cout << "closing tag after line ";
        else
            cout << "opening tag before line ";

        cout << x.first << '\n';
    }
    return 0;
}