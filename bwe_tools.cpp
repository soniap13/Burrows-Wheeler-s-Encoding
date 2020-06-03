#include "bwe.hpp"
#include "HuffmanEncoder.hpp"
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

    vector<uint8_t> block(block_size);
    bool keep_goin = true;
    list<uint8_t> output_seq;

    while(keep_goin){
        block.clear();
        keep_goin = read_block(block, input, block_size);
        output_seq = bwt(block);
        output_seq = move_to_front(output_seq);
        save_to_file(output_seq, output);
    }
    input.close();
    output.close();
    huffman_encode(output_file);
}

bool bwe::read_block(vector<uint8_t> &input_sequence, ifstream &input, int block_size){
    uint8_t elem;
    for(int i = 0; i < block_size; i++){
        input >> elem;
        if(input.eof()) return false;
        input_sequence.push_back(elem);
    }
    return true;
}

list<uint8_t> bwe_linear::bwt(vector<uint8_t> &sequence){
    list<uint8_t> result;
    for(auto elem : sequence)
        result.push_back(elem);
    return result;
}

list<uint8_t> bwe_nlogn::bwt(vector<uint8_t> &sequence){
    list<uint8_t> result;
    for(auto elem : sequence)
        result.push_back(elem);
    return result;
}

list<uint8_t> bwe::move_to_front(list<uint8_t> sequence){
    list<uint8_t> result, codes;
    uint8_t code;
    for(uint16_t i = 0; i < 256; i++)
        codes.push_back((uint8_t)i);
    for(auto s_elem : sequence){
        code = 0;
        for(auto c_elem : codes){
            if(c_elem == s_elem){
                result.push_back(code);
                codes.remove(c_elem);
                codes.push_front(c_elem);
                break;
            }
            code++;
        }
    }
    return result;
}

void bwe::huffman_encode(char * output_file){
    HuffmanEncoder encoder;
    encoder.encodeMessageAndWriteToFile(output_file, output_file);
}

void bwe::save_to_file(list<uint8_t> &output_sequence, ofstream &output){
    for(auto elem : output_sequence){
        output << elem;
    }
}
