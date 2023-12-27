#include "Error_detection_and_correction.h"
#include<map>
string encode(const string &ori) {
    map<string, int> dict;
    int dictSize = 256;
    for (int i = 0; i < dictSize; ++i)
        dict[string(1, char(i))] = i;
    string res = "";
    string s;
    for (char z: ori) {
        if (dict.count(s + z)) s += z;
        else {
            res += to_string(dict[s]);
            dict[s + z] = dictSize++;
            s = z;
        }
    }
    if (!s.empty()) res += to_string(dict[s]);
    return res;
}
int main() {

    string file = read_file("E:\\College\\sample.txt");
    string s = encode(file);
    write_to_file("E:\\College\\xx.txt", s);
    return 0;
}