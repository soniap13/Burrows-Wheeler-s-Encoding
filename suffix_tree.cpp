#include "suffix_tree.hpp"
#include <iostream>

using namespace std;

node::node(int l, int * r, int path_len, node * parent) : l(l), r(r), path_len(path_len), parent(parent){
    next_suffix = NULL;
}

node::~node(){
    for(auto child : children)
        delete child;
    if(children.size() != 0) delete r;

}

void node::set_suffix(node * suffix){
    next_suffix = suffix;
}

suffix_tree::suffix_tree(vector<uint8_t> &sequence) : sequence(sequence){
    root = new node(-1, new int(-1), 0);
    len = new int(-1); //present end of sequence
    last_suffix = NULL;
    if(sequence.size() > 0) create();
}

suffix_tree::~suffix_tree(){
    delete root;
    delete len;
}

void suffix_tree::create(){
    *len = 0;
    node * curr_node = root;
    int curr_char = 0;
    for(auto elem : sequence){
        if(return_child(curr_char, curr_node, elem) == false){
            ////cout<<"curr_char "<<curr_char<<" elem "<<elem<<" curr_node ";
            //print_info(curr_node, true);
            create_nodes(curr_char, curr_node);
            curr_node = root;
            curr_char = 0;
        }
        //else{
            //cout<<"curr_char "<<curr_char<<" elem "<<elem<<" curr_node ";
            //print_info(curr_node, true);
        //}
        *len = *len + 1;
    }
    *len = *len - 1;
}

bool suffix_tree::return_child(int &curr_char, node * &curr_node, uint8_t c){
    if(curr_node != root && curr_char != *(curr_node->r)){
        if(c == sequence[curr_node->l + curr_char + 1]){
            curr_char++;
            return true;
        }
        else
            return false;
    }
    for(auto child : curr_node->children){
        if(c == sequence[child->l]){
            curr_node = child;
            curr_char = 0;
            return true;
        }
    }
    return false;
}


void suffix_tree::create_nodes(int curr_char, node * curr_node){
    node * prev_node = NULL, * new_node, * new_leaf, * prev_leaf = NULL;
    //int j = 0;
    int index = curr_node->l + curr_char;
    if(curr_node == root){
        new_node = new node(*len, len, 0, root);
        if(last_suffix != NULL) last_suffix->set_suffix(new_node);
        last_suffix = new_node;
        add_child(root, new_node);
        return;
    }
    do{
        //cout<<"curr node ";
        //print_info(curr_node, true);
        //cout<<" curr_char "<<curr_char<<endl;
        new_node = new node(curr_node->l, new int (curr_node->l + curr_char), curr_node->path_len, curr_node->parent);
        //cout<<"New node ";
        //print_info(new_node, true);
        if(prev_node != NULL)
            prev_node->next_suffix = new_node;
        replace_child(curr_node->parent, curr_node, new_node);
        curr_node->l += curr_char + 1;
        curr_node->parent = new_node;
        curr_node->path_len += *(new_node->r) - new_node->l + 1;
        add_child(new_node, curr_node);
        new_leaf = new node(*len, len, curr_node->path_len, new_node);
        if(prev_leaf != NULL)
            prev_leaf->next_suffix = new_leaf;
        //cout<<"New leaf ";
        //print_info(new_leaf, true);
        //cout<<"Curr node ";
        //print_info(curr_node, true);
        add_child(new_node, new_leaf);
        prev_node = new_node;
        prev_leaf = new_leaf;
        curr_node = curr_node->next_suffix;
        last_suffix->set_suffix(new_leaf);
        last_suffix = new_leaf;
        curr_char -= 1;
        //j++;
    }while(curr_node != NULL && curr_node->l <= index);
    new_node = new node(*len, len, 0, root);
    last_suffix->set_suffix(new_node);
    last_suffix = new_node;
    add_child(root, new_node);
}

void suffix_tree::print_info(node * n, bool go_further){
    cout<<"NODE ["<<n->l<<","<<*(n->r)<<"] ";//mem "<<n<<" ";
    for(int i = max(0, n->l - n->path_len); i <= *(n->r) ; i++){
        cout<<sequence[i];
    }
    if(go_further && n->next_suffix != NULL){
        cout<<" next suffix ";
        print_info(n->next_suffix, false);
    }
    else
        cout<<endl;
}

void suffix_tree::print_tree(node * n, int i){
    for(int j = 0; j < i; j++) cout<<" ";
    print_info(n, true);
    for(auto child : n->children) print_tree(child, i + 2);
}

void suffix_tree::bwt(node * n, list<uint8_t> &result){
    int last;
    if(n->children.size() == 0){
        last = *len - n->path_len - (*(n->r) - n->l + 1);
        if(last < 0) last += *len + 1;
        result.push_back(sequence[last]);
    }
    for(auto child : n->children){
        bwt(child, result);
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
