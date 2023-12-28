#include "Error_detection_and_correction.h"
#include "huffman.h"
int main() {

    string file = read_file("E:\\College\\Data structures\\Project\\DS_Project\\sample.txt");
    compress(file,"E:\\College\\Data structures\\Project\\DS_Project","kk");
    cout<<decompress("E:\\College\\Data structures\\Project\\DS_Project\\kk.bin");
    return 0;
}