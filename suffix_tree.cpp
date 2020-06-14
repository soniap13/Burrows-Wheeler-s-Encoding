#include "suffix_tree.hpp"
#include <iostream>

using namespace std;

node::node(int l, int * r, node * parent) : l(l), r(r), parent(parent){
    next_suffix = NULL;
}

node::~node(){
    for(auto child : children)
        delete child;
    if(children.size() != 0) delete r;

}

void node::add_child(node * child){
    children.push_back(child);
}

void node::replace_child(node * old_child, node * new_child){
    children.remove(old_child);
    add_child(new_child);
}

void node::set_suffix(node * suffix){
    next_suffix = suffix;
}

suffix_tree::suffix_tree(vector<uint8_t> &sequence) : sequence(sequence){
    root = new node(-1, new int(-1));
    last_suffix = NULL;
    create();
}

suffix_tree::~suffix_tree(){
    delete root;
    delete n;
}

void suffix_tree::create(){
    n = new int(0); //present end of sequence
    node * curr_node = root;
    int curr_char = 0;
    for(auto elem : sequence){
        if(return_child(curr_char, curr_node, elem) == false){
            cout<<"curr_char "<<curr_char<<" elem "<<elem<<" curr_node ";
            print_info(curr_node, true);
            create_nodes(curr_char, curr_node, n);
            curr_node = root;
            curr_char = 0;
        }
        else{
            cout<<"curr_char "<<curr_char<<" elem "<<elem<<" curr_node ";
            print_info(curr_node, true);
        }
        *n = *n + 1;
    }
    *n = *n - 1;
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


void suffix_tree::create_nodes(int curr_char, node * curr_node, int * n){
    node * prev_node = NULL, * new_node, * new_leaf, * prev_leaf = NULL;
    int j = 0;
    int index = curr_node->l + curr_char;
    if(curr_node == root){
        new_node = new node(*n, n, root);
        if(last_suffix != NULL) last_suffix->set_suffix(new_node);
        last_suffix = new_node;
        root->add_child(new_node);
        return;
    }
    do{
        cout<<"curr node ";
        print_info(curr_node, true);
        cout<<" curr_char "<<curr_char<<endl;
        new_node = new node(curr_node->l, new int (curr_node->l + curr_char), curr_node->parent);
        cout<<"New node ";
        print_info(new_node, true);
        if(prev_node != NULL)
            prev_node->next_suffix = new_node;
        curr_node->parent->replace_child(curr_node, new_node);
        curr_node->l += curr_char + 1;
        curr_node->parent = new_node;
        new_node->add_child(curr_node);
        new_leaf = new node(*n, n);
        if(prev_leaf != NULL)
            prev_leaf->next_suffix = new_leaf;
        cout<<"New leaf ";
        print_info(new_leaf, true);
        cout<<"Curr node ";
        print_info(curr_node, true);
        new_node->add_child(new_leaf);
        prev_node = new_node;
        prev_leaf = new_leaf;
        curr_node = curr_node->next_suffix;
        last_suffix->set_suffix(new_leaf);
        last_suffix = new_leaf;
        curr_char -= 1;
        j++;
    }while(curr_node != NULL && curr_node->l <= index );
    new_node = new node(*n, n, root);
    last_suffix->set_suffix(new_node);
    last_suffix = new_node;
    root->add_child(new_node);
}

void suffix_tree::print_info(node * n, bool go_further){
    cout<<"NODE ["<<n->l<<","<<*(n->r)<<"] mem "<<n<<" ";
    for(int i = n->l; i <= *(n->r) ; i++){
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
