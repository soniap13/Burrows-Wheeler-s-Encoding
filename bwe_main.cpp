#include "bwe.hpp"
#include "suffix_tree.hpp"
#include <iostream>
using namespace std;

int main(int arg, char**argv){

    if(arg != 4){
        cout<<"usage: ./bwt <block size> <input file> <output file>"<<endl;
        return 0;
    }
    int n = atoi(argv[1]);
    char * input_file = argv[2];
    char * output_file = argv[3];
    cout<<"Block size: "<<n<<endl;
    cout<<"Encoding "<<input_file<<" and saving into "<<output_file<<endl;
    bwe_linear linear_encoder;
    linear_encoder.encode(input_file, output_file, n);

    return 0;
}
