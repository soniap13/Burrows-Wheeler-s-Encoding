#include <list>
#include <cstdint>
#include <fstream>

class bwe{
    public:
        void encode(char * input_file, char * output_file, int block_size);

    public:
        //reads block_size bytes or less if eof was encouterd while reading input file and safes them into list sequence. Returns true if we should continue reading or false if we read whole file
        static bool read_block(std::list<uint8_t> &input_sequence, std::ifstream &input, int block_size);
        virtual std::list<uint8_t> bwt(std::list<uint8_t> &sequence) = 0;
        static std::list<uint8_t> move_to_front(std::list<uint8_t> &sequence);
        static void huffman_encode(char * output_file);
        static void save_to_file(std::list<uint8_t> &output_sequence, std::ofstream &output);
};

class bwe_linear : public bwe {
    std::list<uint8_t> bwt(std::list<uint8_t> &sequence);
};

class bwe_nlogn : public bwe {
    std::list<uint8_t> bwt(std::list<uint8_t> &sequence);
};
