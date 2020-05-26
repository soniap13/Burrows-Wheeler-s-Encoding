//
//  Huffman Code 1.0
//  HuffmanEncoder.hpp
//
//  Created by Amittai Aviram on 2 Sep 2018.
//  Copyright © 2018 Amittai Aviram. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#include "TreeNode.hpp"
#include <bitset>
#include <cstdint>
#include <iostream>
#include <map>
#include <queue>

/**
 * \brief Class that creates a Huffman encoding and a code translation for a given text.
 *
 * This class offers the user the choice of passign to the constructor the name
 * of an input text file to be encoded or passing a string to be encoded directly
 * to a separate function.  The HuffmanEncoder finds the character frequencies
 * in the given text, builds a Huffman tree from those frequencies and a translation
 * table based on the tree, and writes the binary code to a file whose name is 
 * supplied to the encodeMessageAndWriteToFile function.
 */
class HuffmanEncoder
{
    public:

        /**
         * \brief Default constructor.
         *
         * If you use this constructor, call setInputMessage(const std::string& input)
         * with your input message to be encoded.
         */
        HuffmanEncoder();

        /**
         * \brief Destructor: frees memory allocated for Huffman tree.
         */
        ~HuffmanEncoder();

        /**
         * \brief Sets the input text string to be encoded, in the absence of an input file.
         *
         * Use this function if you wish to encode a relatively brief text string, without
         * use of an external file.
         * \param [in] input the string to be encoded.
         */
        void setInputMessage(const std::string& input);

        /**
         * \brief Encodes the text input and writes the binary encoding to a file.
         *
         * Encodes the text input and writes the binary encoding to a binary file
         * in the same directory or elsewhere if a full path is given.
         * The output file contains an encoding of the Huffman tree, needed
         * for decoding, followed by the encoded text itself.
         * \param [in] input_file name of a file containing text to be encoded.
         * Should be in the same directory or else passed in as a full path.
         * \param [in] output_file name or full path of output binary file.
         */
        void encodeMessageAndWriteToFile(const std::string& input_file, const std::string& output_file);

        /**
         * \brief Encodes the text input and writes the binary encoding to a file.
         *
         * Encodes the text input and writes the binary encoding to a binary file
         * in the same directory or elsewhere if a full path is given.
         * The output file contains an encoding of the Huffman tree, needed
         * for decoding, followed by the encoded text itself.
         * \param [in] output_file name or full path of output binary file.
         */
        void encodeMessageAndWriteToFile(const std::string& output_file);

    private:

        class Comparison
        {
            public:
                bool operator() (const TreeNode * lhs, const TreeNode * rhs) const;
        };
        void readInputFromFile();
        void setFrequencies();
        void buildTree();
        void buildTranslationTable();
        void traverseTree(TreeNode * node, int code, int depth);
        void encodeMessage();
        void convertBytesToBits();
        void printBits(uint64_t output);
        void writeMessageToFile(const std::string& file_name);
        void clearTreeNodes();

        std::string input_file_name;
        std::string input_message;
        std::map<char, int> frequencies;
        std::vector<TreeNode *> tree_nodes;
        std::priority_queue<TreeNode *, std::vector<TreeNode *>, Comparison> minima;
        TreeNode * tree;
        std::map<char, std::pair<int, int>> translations;
        std::queue<uint8_t> encoded_bytes;
        std::vector<uint64_t> encoded_message;
};
