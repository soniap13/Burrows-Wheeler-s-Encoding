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
    input >> noskipws;
    ofstream output(output_file);
    if(!output.good())
        ERROR(output_file);

    list<uint8_t> block;
    bool keep_goin = true;

    while(keep_goin){
        keep_goin = read_block(block, input, block_size);
        block = bwt(block);
        block = move_to_front(block);
        block = huffman_encode(block);
        save_to_file(block, output);
    }

    input.close();
    output.close();
}

bool bwe::read_block(list<uint8_t> &input_sequence, ifstream &input, int block_size){
    uint8_t elem;
    for(int i = 0; i < block_size; i++){
        if(input.eof()) return false;
        input >> elem;
        input_sequence.push_back(elem);
    }
    return true;
}

list<uint8_t> bwe::bwt(list<uint8_t> &sequence){
    return sequence;
}

list<uint8_t> bwe::move_to_front(list<uint8_t> &sequence){
    //list<uint8_t> result;
    return sequence;
}

list<uint8_t> bwe::huffman_encode(list<uint8_t> &sequence){
    //list<uint8_t> result;
    return sequence;
}

void bwe::save_to_file(list<uint8_t> &output_sequence, ofstream &output){
    for(auto elem : output_sequence){
        output << elem;
    }
}
