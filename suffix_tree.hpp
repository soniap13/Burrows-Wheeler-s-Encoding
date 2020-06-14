#include <list>
#include <cstdint>
#include <vector>

class node{
    public:
        int l;
        int * r; //represent substring [i,j]
        node * next_suffix;
        std::list<node*> children;
        node * parent;

        node(int l, int * r, node * parent = NULL);
        ~node();
        void add_child(node * child);
        void replace_child(node * old_child, node * new_child);
        void set_suffix(node * suffix);
};

class suffix_tree{
    public:
        node * root;
        node * last_suffix;
        std::vector<uint8_t> sequence;
        int * n;

        suffix_tree(std::vector<uint8_t> &sequence);
        ~suffix_tree();
        void create();
        bool return_child(int &curr_char, node * &curr_node, uint8_t c);
        void create_nodes(int curr_char, node * curr_node, int * n);
        void print_info(node * n, bool go_further);
        void print_tree(node * n, int i = 0);
};
