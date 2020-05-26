//
//  Huffman Code 1.0
//  TreeNode.hpp
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

#pragma once

#include <cstddef>

/*
 * Data structure used as the node in the Huffman tree built by
 * HuffmanEncoder and read from the binary file by HuffmanDecoder.
 * The Huffman tree in this application avoids the usual practice of using
 * pointers to link parent nodes to children, in order to facilitate
 * serialization in the binary file.  Instead, the nodes use indices
 * to refer to themselves and their children, which index into a vector
 * of TreeNode addresses held in the HuffmanEncoder and HuffmanDecoder objects.
 * This way, the actual TreeNode addresses can vary, yet the tree can be 
 * reconstructed out of the data written to file.
 */
struct TreeNode
{
    /**
     * \brief Default constructor -- used by HuffmanDecoder.
     *
     * HuffmanDecoder uses this constructor in order to create a TreeNode
     * onto which to read the actual fields of a specific TreeNode instance
     * from the metadata section of the input binary file.
     */
    TreeNode() = default;
    
    /**
     * \brief Constructor for a leaf node.
     *
     * Constructs a leaf TreeNode, containing the character, as well as
     * its frequency.  The left and right indices are not used.
     * \param [in] index the index of this TreeNode in the vector of all TreeNodes.
     * \param [in] key the character that this leaf node represents.
     * \param [in] frequency the frequency of the character in the input text.
     */
    TreeNode(std::size_t index, char key, int frequency);

    /**
     * \brief Constructor for an internal node.
     *
     * Constructs a TreeNode above the leaf level in the Huffman tree,
     * containing the sum of the frequencies of both children.
     * \param [in] index the index of this TreeNode in the vector of all TreeNodes.
     * \param [in] left_node the address of the left child TreeNode.
     * \param [in] right_node the address of the right child TreeNode.
     */
    TreeNode(std::size_t index, TreeNode * left_node, TreeNode * right_node);

    /**
     * \brief Whether this TreeNode is a leaf, and therefore contains a character.
     */
    bool isLeaf();

    /**
     * \brief Index of this TreeNode in the vector of TreeNodes in HuffmanEncoder
     * and (as reconstructed) in HuffmanDecoder.
     */
    std::size_t index;

    /**
     * \brief The character represented by this TreeNode, if it is a leaf.
     */
    char key;

    /**
     * \brief If this is a leaf, then the computed frequency of the character (key).
     * If it is an internal node, then the sum of the frequencies held by the two children.
     */
    int frequency;

    /**
     * \brief Index of the left child node, if this is an internal node.  Not used in
     * leaf nodes.
     */
    std::size_t left_index;

    /**
     * \brief Index of the right child node, if this is an internal node.  Not used in
     * leaf nodes.
     */
    std::size_t right_index;

    /**
     * \brief Whether this is a leaf node.
     */
    bool is_leaf;
};
