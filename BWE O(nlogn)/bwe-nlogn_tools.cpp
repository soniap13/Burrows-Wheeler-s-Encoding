#include "bwe-nlogn.hpp"
#include <iostream>
#include <errno.h>
#include <string.h>
using namespace std;

#define ERROR(str) { fprintf(stderr, "%s: %s\n", str, strerror(errno)); exit(EXIT_FAILURE); }

void bwe::encode(char * input_file, char * output_file, int block_size){
    ifstream input(input_file);
    if(!input.good())
        ERROR(input_file);
    ofstream output(output_file);
    if(!output.good())
        ERROR(output_file);

    list<uint8_t> block;
    bool keep_goin = true;

    while(keep_goin){
        keep_goin = read_block(block, input);
        block = bwt(block);
        block = move_to_front(block);
        block = huffman_encode(block);
        save_to_file(block, output);
    }

    input.close();
    output.close();
}

bool bwe::read_block(list<uint8_t> &input_sequence, ifstream &input){
    return false;
}

list<uint8_t> bwe::bwt(list<uint8_t> &sequence){
    list<uint8_t> result;
    return result;
}

list<uint8_t> bwe::move_to_front(list<uint8_t> &sequence){
    list<uint8_t> result;
    return result;
}

list<uint8_t> bwe::huffman_encode(list<uint8_t> &sequence){
    list<uint8_t> result;
    return result;
}

void bwe::save_to_file(list<uint8_t> &output_sequence, ofstream &output){

}
