#include "bwe.hpp"
#include "suffix_tree.hpp"
#include <iostream>
#include <algorithm>
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
    /*
    vector<uint8_t> v;
    v.push_back('a');
    //suffix_tree t1(v);
    //t1.print_tree(t1.root);
    v.push_back('b');
    //suffix_tree t2(v);
    //t2.print_tree(t2.root);

    v.push_back('c');
    //suffix_tree t3(v);
    //t3.print_tree(t3.root);
    v.push_back('a');
    //suffix_tree t4(v);
    //t4.print_tree(t4.root);

    v.push_back('b');
    v.push_back('d');
    //suffix_tree t5(v);
    //t5.print_tree*/
    return 0;
}
