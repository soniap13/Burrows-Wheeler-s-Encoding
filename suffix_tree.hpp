#include <list>
#include <cstdint>
#include <vector>

class node{
    private:
        int r; //represent substring [i,j]
        std::list<node*> children;
        node * next_suffix;

        void set_suffix(node * suffix);
        node(int l, int r, int path_len, node * parent = NULL);
        void delete_child(node * n);

    public:
        int l;
        node * parent;
        int path_len;

        node();
        virtual ~node();
        int get_begin();
        virtual int get_end();
        void change_begin(int new_begin);
        virtual node* get_suffix();
        friend class suffix_tree;
};

class leaf : public node{
    public:
        int * r;

        int get_end();
        leaf(int l, int * r, int path_len, node * parent = NULL);
        ~leaf();
        node* get_suffix();
        friend class suffix_tree;
};

class suffix_tree{
    public:
        node * root;
        node * last_suffix;
        std::vector<uint8_t> sequence;
        int * len;

        suffix_tree(std::vector<uint8_t> &sequence);
        void create();
        bool follow_sequence(node * &active_node, node * &active_child, int &active_length, int elem_index);
        void create_suffixes(int &remaining, node * &active_node, node * &active_child, int &active_length, int elem_index);
        void print_info(node * n, bool is_suffix = false);
        ~suffix_tree();
        void print_tree(node * n, int i = 0);
        void print_tree(leaf * n, int i);
        void bwt(node * n, std::list<uint8_t> &result, int &first);
        void add_child(node * parent, node * child);
        void replace_child(node * parent, node * old_child, node * new_child);
};

