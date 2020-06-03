#include<list>
#include <cstdint>
#include<vector>

class node{
    public:
        int l;
        int * r; //represent substring [i,j]
        node * suffix;
        std::list<node*> children;

        node(int l, int * r);
        ~node();
        void add_child(node * child);
        void return_child(uint8_t c);
};

class suffix_tree{
    public:
        node * root;

        suffix_tree();
        ~suffix_tree();
        void create(std::vector<uint8_t> &sequence);
};
