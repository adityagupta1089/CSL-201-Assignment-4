#ifndef SRC_RED_BLACK_TREE_CPP_
#define SRC_RED_BLACK_TREE_CPP_

#include <iostream>

using namespace std;

template<typename K, typename V> class red_black_tree {

        // ===========================================================
        // Inner structures and classes
        // ===========================================================
    private:
        enum Color {
            red, black
        };

    public:
        struct rb_tree_entry {
                K key;
                V val;
                rb_tree_entry(K k, V v)
                        : key(k), val(v) {
                }
        };
        // ===========================================================
    private:
        struct rb_tree_node {
                rb_tree_entry* entry;
                rb_tree_node* left_child;
                rb_tree_node* right_child;
                Color col;
                int height;
                rb_tree_node(rb_tree_entry* entry, Color pColor)
                        : entry(entry), left_child(NULL), right_child(NULL), height(height), col(
                                pColor) {
                }
                rb_tree_node()
                        : entry(NULL), left_child(NULL), right_child(NULL), height(0), col(black) {
                }
                inline void update_height() {
                    this->height = 1
                            + max(left_child ? left_child->height : -1,
                                    right_child ? right_child->height : -1);
                }

        };
        // ===========================================================
    public:
        class rb_tree_iterator {
            private:
                rb_tree_node* node;
                rb_tree_iterator(rb_tree_node* node)
                        : node(node) {
                }
            public:
                rb_tree_entry& operator *() {
                    return *(node->entry);
                }
                bool operator ==(const rb_tree_iterator& p) const {
                    return node == p.node;
                }
                bool operator !=(const rb_tree_iterator& p) const {
                    return node != p.node;
                }
                friend class red_black_tree;
        };
        // ===========================================================
        // Fields
        // ===========================================================
    private:
        rb_tree_node* root;
        unsigned mSize;
        rb_tree_node* end_node;
        rb_tree_iterator* end_iterator;
        // ===========================================================
        // Constructor & Destructor
        // ===========================================================
    public:
        red_black_tree() {
            root = NULL;
            mSize = 0;
            end_node = new rb_tree_node();
            end_iterator = new rb_tree_iterator(end_node);
        }

        virtual ~red_black_tree() {
            delete_node(root);
        }
    private:
        void delete_node(rb_tree_node* node) {
            if (!node) return;
            delete_node(node->left_child);
            delete_node(node->right_child);
            delete node;
        }
        // ===========================================================
        // End Iterator
        // ===========================================================
    public:
        rb_tree_iterator end() {
            return *end_iterator;
        }
        // ===========================================================
        // Put/Insert
        // ===========================================================
    public:
        void insert(K k, V v) {
            cout << "Inserting " << k << "\n";
            rb_tree_entry* entry = new rb_tree_entry(k, v);
            root = insert(root, entry);
            this->print();
        }
        // ===========================================================
        // Put/Insert Internal Functions
        // ===========================================================
    private:
        rb_tree_node* rotate_right(rb_tree_node* u) {
            rb_tree_node* v = u->left_child;
            rb_tree_node* t2 = v->right_child;
            u->left_child = t2;
            v->right_child = u;
            u->update_height();
            v->update_height();
            return v;
        }

        rb_tree_node* rotate_left(rb_tree_node* v) {
            rb_tree_node* u = v->right_child;
            rb_tree_node* t2 = u->left_child;
            v->right_child = t2;
            u->left_child = v;
            v->update_height();
            u->update_height();
            return u;
        }

        void tree_balance(rb_tree_node& node) {
            //TODO
        }

        rb_tree_node* insert(rb_tree_node* node, rb_tree_entry* entry) {
            if (node == NULL) {
                return new rb_tree_node(entry, (mSize++ == 0) ? black : red);
            } else {
                // ===========================================================
                // Insertion
                // ===========================================================
                if (entry->key < node->entry->key) node->left_child = insert(node->left_child,
                        entry);
                else if (entry->key > node->entry->key) node->right_child = insert(
                        node->right_child, entry);
                else /*entry->key == node->entry->key*/node->entry->val = entry->val;
                node->update_height();
                this->print();
                if (entry->key == node->entry->key) {
                    cout << "Updated\n";
                    return node;
                }
                // ===========================================================
                // Balancing
                // ===========================================================
                tree_balance(*node);
                return node;
            }
        }

// ===========================================================
// Find
// ===========================================================
    public:
        rb_tree_iterator search(K k) {
            rb_tree_node* node = root;
            if (!node) return end();
            do {
                if (k < node->entry->key) node = node->left_child;
                else if (k > node->entry->key) node = node->right_child;
                else return rb_tree_iterator(node);
            } while (node);
            return end();
        }
// ===========================================================
// Remove
// ===========================================================
    public:
    private:
        rb_tree_node* remove(rb_tree_node* node, K k) {
//TODO remove
            return node;
        }
// ===========================================================
// Printing
// ===========================================================
    private:
        void print(string prefix, rb_tree_node* node, bool left, bool root) {
            if (node->right_child) print(prefix + (!left || root ? "    " : "│   "),
                    node->right_child, false, false);
            cout << prefix << (root ? "X─── " : (left ? "└── " : "┌── ")) << "[" << node->entry->key
                    << (node->col == red ? "(R)" : "(B)") << "]\n";
            if (node->left_child) print(prefix + (left ? "    " : "│   "), node->left_child, true,
                    false);
        }
    public:
        void print() {
            cout << string(100, '=') << "\n";
            print("", root, true, true);
            cout << string(100, '=') << "\n";
        }
}
;

#endif /*SRC_RED_BLACK_TREE_CPP_*/
