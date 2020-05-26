//
//  Huffman Code 1.0
//  TreeNode.cpp
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
#include <iostream>

TreeNode::TreeNode(std::size_t index, TreeNode * left_node, TreeNode * right_node) :
    index{index},
    key{'\0'},
    frequency{left_node->frequency + right_node->frequency},
    left_index{left_node->index},
    right_index{right_node->index},
    is_leaf{false}
{}

TreeNode::TreeNode(std::size_t index, char key, int frequency) :
    index{index},
    key{key},
    frequency{frequency},
    left_index{0},
    right_index{0},
    is_leaf{true}
{}

bool TreeNode::isLeaf()
{
    return is_leaf;
}
