#include <list>
#include <cstdint>
#include <fstream>

class bwe{
    public:
        static void encode(char * input_file, char * output_file, int block_size);

    public:
        //reads block_size bytes or less if eof was encouterd while reading input file and safes them into list sequence. Returns true if we should continue reading or false if we read whole file
        static bool read_block(std::list<uint8_t> &sequence, std::ifstream input);
        static std::list<uint8_t> bwt(std::list<uint8_t> &input_sequence);
        static std::list<uint8_t> move_to_front(std::list<uint8_t> &input_sequence);
        static std::list<uint8_t> huffman_encode(std::list<uint8_t> &input_sequence);
        static std::list<uint8_t> save_to_file(std::ofstream output);
};
