#include "suffix_tree.hpp"

using namespace std;

node::node(int l, int * r) : l(l), r(r){
}

node::~node(){
    for(auto child : children)
        delete child;
}

void node::add_child(node * child){
    children.push_back(child);
}

suffix_tree::suffix_tree(){
    root = new node(0, new int(0));
}

suffix_tree::~suffix_tree(){
    delete root;
}

void suffix_tree::create(vector<uint8_t> &sequence){
    int * n = new int(0); //present end of sequence
    node * curr_node = root;
    for(auto elem : sequence){
        curr_node->add_child(new node(0, n));
        *n++;
    }
}
