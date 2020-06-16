#include "bwe.hpp"
#include "suffix_tree.hpp"
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

#define bad_input() { cout<<"usage: ./bwe [-b block size] [-v version (linear or nlogn)] <input file> <output file>"<<endl; return 0;}

int main(int arg, char**argv){

    if(arg < 3) bad_input();
    int n = -1;
    int i = 1;
    bwe * encoder = NULL;
    char * input_file = NULL;
    char * output_file = NULL;
    while(i < arg){
        if(strcmp(argv[i], "-b") == 0){
            if(i + 1 != arg && n == -1){
                n = atoi(argv[i + 1]);
                i++;
            }
            else
                bad_input();

        }
        else if(strcmp(argv[i], "-v") == 0){
            if(i + 1 != arg && encoder == NULL){
                if(strcmp(argv[i + 1], "nlogn") == 0)
                    encoder = new bwe_nlogn();
                else if(strcmp(argv[i + 1], "linear") == 0)
                    encoder = new bwe_linear();
                else bad_input();
                i++;
            }
            else
                bad_input();
        }
        else{
            if(i == arg - 2)
                input_file = argv[i];
            if(i == arg - 1)
                output_file = argv[i];
        }
        i++;
    }
    if(input_file == NULL || output_file == NULL) bad_input();
    if(n == -1) n = 1000;
    cout<<"Block size: "<<n<<endl;
    cout<<"Encoding "<<input_file<<" and saving into "<<output_file<<endl;
    if(encoder == NULL) encoder = new bwe_linear();
    encoder->encode(input_file, output_file, n);
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
