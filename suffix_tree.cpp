#include "suffix_tree.hpp"
#include <iostream>

using namespace std;

node::node(){
    next_suffix = NULL;
}

node::node(int l, int r, int path_len, node * parent) : r(r), l(l), parent(parent), path_len(path_len){
    next_suffix = NULL;
}

node::~node(){
    for(auto child : children)
        delete child;
}

void node::set_suffix(node * suffix){
    next_suffix = suffix;
}

void node::delete_child(node * n){
    children.remove(n);
}

int node::get_begin() { return l;}

int node::get_end() { return r;}

void node::change_begin(int new_begin){
    path_len += new_begin - l;
    l = new_begin;
}

node * node::get_suffix(){ return next_suffix;}

leaf::leaf(int left, int * r, int path_length, node * leaf_parent) : r(r){
    l = left;
    path_len = path_length;
    parent = leaf_parent;
}

leaf::~leaf(){}

int leaf::get_end(){ return *r;};

node * leaf::get_suffix(){ return NULL;}

suffix_tree::suffix_tree(vector<uint8_t> &sequence) : sequence(sequence){
    root = new node(-1, -1, 0);
    len = new int(-1); //present end of sequence
    last_suffix = NULL;
    if(sequence.size() > 0) create();
}

suffix_tree::~suffix_tree(){
    delete root;
    delete len;
}

void suffix_tree::create(){
    int remaining = 0, active_len = 0;
    node * active_child = root;
    node * active_node = NULL;

    for(unsigned int i = 0; i < sequence.size(); i++){
        remaining++;
        *len = *len + 1;
        //cout<<*len<<") "<<sequence[i]<<endl;
        if(follow_sequence(active_node, active_child, active_len, i) == false){
            //cout<<"creating nodes"<<endl;
            create_suffixes(remaining, active_node, active_child, active_len, i);
            remaining = 0;
            active_len = 0;
            active_child = root;
            active_node = NULL;
        }
        //print_tree(root, 0);
    }

}

// follows path on tree corresponding to our suffix
// if we can find one more corresponding symbol in tree(in our case char c) it returns true, and false if an action is needed (creating new nodes)
// function changes curr_char and curr_node to tell us wehere in tree searching we are
bool suffix_tree::follow_sequence(node * &active_node, node * &active_child, int &active_len, int elem_index){
    //print_info(curr_node, false);
    if(active_child != root && active_len != active_child->get_end() - active_child->get_begin() + 1){ //we are somewhere in the middle of substring in searching the path
        //cout<<"curr char "<<curr_char<<endl;
        if(sequence[elem_index] == sequence[active_child->get_begin() + active_len]){
            active_len++;
            return true;
        }
        else{
            //cout<<"bład"<<endl;
            return false;
        }
    }
    for(auto child : active_child->children){ //we have to search path in other node
        if(sequence[elem_index] == sequence[child->get_begin()]){
            active_node = active_child;
            active_child = child;
            active_len = 1;
            return true;
        }
    }
    return false;
}


void suffix_tree::create_suffixes(int &remaining, node * &active_node, node * &active_child, int &active_len, int elem_index){
    node * prev_node = NULL, * new_node = NULL;
    leaf * new_leaf;
    int spliting_edge = active_len - 1, path_len;

    while(remaining > 0){
        /*
        cout<<"active_len "<<active_len<<endl;
        cout<<"remaining "<<remaining<<endl;
        cout<<"active node ";
        if(active_node != NULL) print_info(active_node);
        else cout<<"NULL";
        cout<<endl<<"active child ";
        if(active_child != NULL) print_info(active_child);
        else cout<<"NULL";
        cout<<endl;
        */
        //if(remaining == 2) break;
        if(active_child == NULL){
            if(active_node == NULL) active_node = root;
            active_child = active_node;
            spliting_edge = active_child->get_end();
            if(follow_sequence(active_node, active_child, spliting_edge, elem_index - active_len)){
                if(follow_sequence(active_node, active_child, spliting_edge, elem_index)) break;
            }
        }
        if(spliting_edge == active_child->get_end() || (active_node == NULL && remaining == 1)){
            if(active_node == NULL && remaining == 1) active_child = root;
            //cout<<"adding leaf to active child"<<endl;
            if(active_child == root)
                path_len = 0;
            else
                path_len = active_child->path_len + (active_child->get_end() - active_child->get_begin() + 1);
            new_leaf = new leaf(elem_index, len, path_len);
            add_child(active_child, new_leaf);
            if(prev_node != NULL) prev_node->set_suffix(active_child);
            prev_node = active_child;
            if(active_node != NULL) active_node = active_node->get_suffix();
            active_child = active_child->get_suffix();
        }
        else{
           // cout<<"spliting edge"<<endl;
            new_node = new node(active_child->get_begin(), active_child->get_begin() + active_len - 1, active_child->path_len, active_node);
            new_leaf = new leaf(elem_index, len, active_child->path_len + active_len, new_node);
            active_child->change_begin(active_child->get_begin() + active_len);
            active_node->delete_child(active_child);
            add_child(active_node, new_node);
            add_child(new_node, active_child);
            add_child(new_node, new_leaf);
            new_node->set_suffix(root);
            if(prev_node != NULL) prev_node->set_suffix(new_node);

            if(active_node == root) active_len--;
            active_node = active_node->get_suffix();
            active_child = active_child->get_suffix();
            prev_node = new_node;
        }
        remaining--;
    }
}

void suffix_tree::print_info(node * n, bool is_suffix){
    cout<<"NODE ["<<n->get_begin()<<","<<n->get_end()<<"] ";//mem "<<n<<" ";
    int i;
    if(is_suffix) i = max(0, n->l - n->path_len);
    else i = max(0, n->l);
    for(i = i; i <= n->get_end() ; i++){
        cout<<sequence[i];
    }
}


void suffix_tree::print_tree(node * n, int i){
    for(int j = 0; j < i; j++) cout<<" ";
    print_info(n, false);
    if(n->next_suffix != NULL){
        cout<<" next suffix ";
        print_info(n->next_suffix, true);
    }
    cout<<endl;
    for(auto child : n->children) print_tree(child, i + 2);
}

void suffix_tree::print_tree(leaf * n, int i){
    for(int j = 0; j < i; j++) cout<<" ";
    print_info(n, false);
}

void suffix_tree::bwt(node * n, list<uint8_t> &result, int &first){
    int last;
    static int i = 0;
    if(n->children.size() == 0){
        last = *len - n->path_len - (n->get_end() - n->get_begin() + 1);
        if(last < 0) last += *len + 1;
        if(last == *len) first = i;
        result.push_back(sequence[last]);
        i++;
    }
    for(auto child : n->children){
        bwt(child, result, first);
    }
}

void suffix_tree::add_child(node * parent, node * child){
    for(auto c = parent->children.begin(); c != (parent->children).end(); c++){
        if(sequence[(*c)->l] > sequence[child->l]){
            (parent->children).insert(c, child);
            return;
        }
    }
    parent->children.push_back(child);
}

void suffix_tree::replace_child(node * parent, node * old_child, node * new_child){
    parent->children.remove(old_child);
    add_child(parent, new_child);
}
