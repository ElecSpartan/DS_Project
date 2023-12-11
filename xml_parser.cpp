#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("sample.xml");
    // string line;
    // getline(in, line);

    stringstream buffer;
    buffer << in.rdbuf();
    // cout << buffer.str();

    string s;
    int i = 0, j;
    string input_string = buffer.str();

    
    while(i < input_string.length()) {
        if (input_string[i] == '>') {
            s += '>';

            // check if it is closing then opeing tags or tag value
            bool flag = false;
            int k = i + 1;
            while(k < input_string.length() && input_string[k] != '<') {
                if(isalnum(input_string[k])) {
                    flag = true;
                    break;
                }
                k++;
            }

            if (flag) {
                j = i + 1;
                while (j < input_string.length() && input_string[j] != '<') {
                    s += input_string[j];
                    j++;
                }
                i = j;
                continue;
            }
            i = k;
        }
        
        if(input_string[i] == ' ' || input_string[i] == '\t' || input_string[i] == '\n') continue;
        s += input_string[i];

        cout << i << " " << input_string[i] << "\t";
        i++;
        cout << i << "\n";
    }

    // cout << s;
    cout << input_string.length();

    return 0;
}