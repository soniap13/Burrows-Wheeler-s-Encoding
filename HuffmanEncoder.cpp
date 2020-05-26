//
//  Huffman Code 1.0
//  HuffmanEncoder.cpp
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

#include "HuffmanEncoder.hpp"
#include "TreeNode.hpp"
#include <bitset>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>

HuffmanEncoder::HuffmanEncoder() :
    input_file_name{""}
{}

HuffmanEncoder::~HuffmanEncoder()
{
    clearTreeNodes();
}

void HuffmanEncoder::readInputFromFile()
{
    std::ifstream input(input_file_name);
    std::stringstream sstream;
    sstream << input.rdbuf();
    input_message = sstream.str();
}

void HuffmanEncoder::setInputMessage(const std::string& input)
{
    input_message = input;
}

void HuffmanEncoder::encodeMessageAndWriteToFile(const std::string& input_file, const std::string& output_file)
{
    input_file_name = input_file;
    readInputFromFile();
    encodeMessageAndWriteToFile(output_file);
}

void HuffmanEncoder::encodeMessageAndWriteToFile(const std::string& output_file)
{
    setFrequencies();
    buildTree();
    buildTranslationTable();
    encodeMessage();
    writeMessageToFile(output_file);
    clearTreeNodes();
}

void HuffmanEncoder::setFrequencies()
{
    for (auto c : input_message)
    {
        ++frequencies[c];
    }
    frequencies['\0'] = 1;
}

void HuffmanEncoder::buildTree()
{
    std::size_t index = 0;
    for (auto& entry : frequencies) {
        TreeNode * new_node = new TreeNode(index, entry.first, entry.second);
        tree_nodes.push_back(new_node);
        minima.push(new_node);
        ++index;
    }
    for (int i = 1; i < frequencies.size(); ++i)
    {
        TreeNode * x = minima.top();
        minima.pop();
        TreeNode * y = minima.top();
        minima.pop();

        TreeNode * new_node = new TreeNode(index, x, y);
        tree_nodes.push_back(new_node);
        minima.push(new_node);
        ++index;
    }
    tree = minima.top();
}

void HuffmanEncoder::buildTranslationTable()
{
    traverseTree(tree, 0, 0);
}

void HuffmanEncoder::traverseTree(TreeNode * node, int code, int depth)
{
    if (node->isLeaf())
    {
        translations[node->key] = std::make_pair(code, depth);
    }
    else
    {
        ++depth;
        code <<= 1;
        traverseTree(tree_nodes[node->left_index], code, depth);
        code |= 1;
        traverseTree(tree_nodes[node->right_index], code, depth);
    } 
}

void HuffmanEncoder::encodeMessage()
{
    const char * input_message_array = input_message.c_str();
    for (int i = 0; i < input_message.size() + 1; ++i)
    {
        char current_char = input_message_array[i];
        int value = translations[current_char].first;
        int length = translations[current_char].second;
        int mask = 1 << (length - 1);
        while (mask)
        {
            if (value & mask)
            {
                encoded_bytes.push(1);
            }
            else
            {
                encoded_bytes.push(0);
            }
            mask >>= 1;
        }
        if (encoded_bytes.size() >= 64)
        {
            convertBytesToBits();
        }
    }
    for (int i = encoded_bytes.size(); i <= 64; ++i)
    {
        encoded_bytes.push(0);
    }
    convertBytesToBits();
}

void HuffmanEncoder::convertBytesToBits()
{
    uint64_t entry = 0ULL;
    uint64_t mask = 1ULL;
    for (int i = 0; i < 64; ++i)
    {
        if (encoded_bytes.front())
        {
            entry |= mask;
        }
        encoded_bytes.pop();
        mask <<= 1;
    }
    encoded_message.push_back(entry);
}

void HuffmanEncoder::printBits(uint64_t output)
{
    std::bitset<64> output_bitset{output};
    for (int i = 0; i < 32; ++i) {
        bool tmp = output_bitset[i];
        output_bitset[i] = output_bitset[64 - i - 1];
        output_bitset[64 - i - 1] = tmp;
    }
    std::cout << output_bitset << std::endl;
}

void HuffmanEncoder::writeMessageToFile(const std::string& file_name)
{
    std::ofstream output(file_name, std::ofstream::out | std::ofstream::binary);
    output.write(reinterpret_cast<char *>(&tree->index), sizeof(size_t));
    size_t tree_nodes_size = tree_nodes.size();
    output.write(reinterpret_cast<char *>(&tree_nodes_size), sizeof(size_t));
    for (auto& n : tree_nodes)
    {
        output.write(reinterpret_cast<char *>(n), sizeof(TreeNode));
    }
    size_t encoded_message_size = encoded_message.size();
    output.write(reinterpret_cast<char *>(&encoded_message_size), sizeof(size_t));
    for (uint64_t num : encoded_message)
    {
        output.write(reinterpret_cast<char *>(& num), sizeof(uint64_t));
    }
}

void HuffmanEncoder::clearTreeNodes()
{
    for (auto node : tree_nodes)
    {
        delete node;
    }
    tree_nodes.clear(); 
}

bool HuffmanEncoder::Comparison::operator() (const TreeNode * lhs, const TreeNode * rhs) const
{
    return lhs->frequency >= rhs->frequency;
}
