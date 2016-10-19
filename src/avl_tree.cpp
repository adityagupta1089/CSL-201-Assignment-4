#ifndef SRC_AVL_TREE_CPP_
#define SRC_AVL_TREE_CPP_

#include <iostream>

using namespace std;

template<typename K, typename V> class avl_tree {

        // ===========================================================
        // Inner structures and classes
        // ===========================================================
    public:
        struct avl_tree_entry {
                K key;
                V val;
                avl_tree_entry(K k, V v)
                        : key(k), val(v) {
                }
        };
        // ===========================================================
    private:
        struct avl_tree_node {
                avl_tree_entry* entry;
                avl_tree_node* left_child;
                avl_tree_node* right_child;
                int height;
                avl_tree_node(avl_tree_entry* entry)
                        : entry(entry), left_child(NULL), right_child(NULL), height(0) {
                }
                avl_tree_node()
                        : entry(NULL), left_child(NULL), right_child(NULL), height(0) {
                }
                inline void update_height() {
                    this->height = 1
                            + max(left_child ? left_child->height : -1,
                                    right_child ? right_child->height : -1);
                }
        };
        inline static int height(avl_tree_node* node) {
            return ((node) ? node->height : -1);
        }
        // ===========================================================
    public:
        class avl_tree_iterator {
            private:
                avl_tree_node* node;
                avl_tree_iterator(avl_tree_node* node)
                        : node(node) {
                }
            public:
                avl_tree_entry& operator *() {
                    return *(node->entry);
                }
                bool operator ==(const avl_tree_iterator& p) const {
                    return node == p.node;
                }
                bool operator !=(const avl_tree_iterator& p) const {
                    return node != p.node;
                }
                friend class avl_tree;
        };
        // ===========================================================
        // Fields
        // ===========================================================
    private:
        avl_tree_node* root;
        unsigned mSize;
        avl_tree_node* end_node;
        avl_tree_iterator* end_iterator;
        // ===========================================================
        // Constructor & Destructor
        // ===========================================================
    public:
        avl_tree() {
            root = NULL;
            mSize = 0;
            end_node = new avl_tree_node();
            end_iterator = new avl_tree_iterator(end_node);
        }
        virtual ~avl_tree() {
            delete_node(root);
        }
    private:
        void delete_node(avl_tree_node* node) {
            if (!node) return;
            delete_node(node->left_child);
            delete_node(node->right_child);
            delete node;
        }
        // ===========================================================
        // Map functions to get specific entries/iterators
        // ===========================================================
    public:
        avl_tree_iterator firstEntry() {
            avl_tree_node* node = root;
            if (!node) return end();
            while (node->left_child) {
                node = node->left_child;
            }
            return avl_tree_iterator(node);
        }
        avl_tree_iterator lastEntry() {
            avl_tree_node* node = root;
            if (!node) return end();
            while (node->right_child) {
                node = node->right_child;
            }
            return avl_tree_iterator(node);
        }

        avl_tree_iterator ceilingEntry(K k) {
            return ceilingEntry(root, k);
        }

        avl_tree_iterator floorEntry(K k) {
            return floorEntry(root, k);
        }

        avl_tree_iterator lowerEntry(K k) {
            return lowerEntry(root, k);
        }

        avl_tree_iterator higherEntry(K k) {
            return higherEntry(root, k);
        }

        avl_tree_iterator end() {
            return *end_iterator;
        }
        // ===========================================================
        // Internal functions to get specific entries/iterators
        // ===========================================================
    private:
        avl_tree_iterator ceilingEntry(avl_tree_node* node, K k) {
            if (!node) return end();
            else if (k > node->entry->key) return ceilingEntry(node->right_child, k);
            else if (k == node->entry->key) return avl_tree_iterator(node);
            else {
                avl_tree_iterator ceil_left = ceilingEntry(node->left_child, k);
                return (ceil_left == end() || (*ceil_left).key < k) ?
                        avl_tree_iterator(node) : ceil_left;
            }
        }
        avl_tree_iterator floorEntry(avl_tree_node* node, K k) {
            if (!node) return end();
            else if (k < node->entry->key) return floorEntry(node->left_child, k);
            else if (k == node->entry->key) return avl_tree_iterator(node);
            else {
                avl_tree_iterator floor_right = floorEntry(node->right_child, k);
                return (floor_right == end() || (*floor_right).key > k) ?
                        avl_tree_iterator(node) : floor_right;
            }
        }
        avl_tree_iterator lowerEntry(avl_tree_node* node, K k) {
            if (!node) return end();
            else if (k <= node->entry->key) return lowerEntry(node->left_child, k);
            else {
                avl_tree_iterator lower_right = lowerEntry(node->right_child, k);
                return (lower_right == end()) ? avl_tree_iterator(node) : lower_right;
            }
        }
        avl_tree_iterator higherEntry(avl_tree_node* node, K k) {
            if (!node) return end();
            else if (k >= node->entry->key) return higherEntry(node->right_child, k);
            else {
                avl_tree_iterator higher_left = higherEntry(node->left_child, k);
                return (higher_left == end()) ? avl_tree_iterator(node) : higher_left;
            }
        }
        // ===========================================================
        // Basic map functions
        // ===========================================================
    public:
        unsigned size() {
            return mSize;
        }
        bool empty() {
            return mSize == 0;
        }

        // ===========================================================
        // Put/Insert
        // ===========================================================
    public:
        void put(K k, V v) {
            cout << "Inserting " << k << "\n";
            avl_tree_entry* entry = new avl_tree_entry(k, v);
            root = insert(root, entry);
            this->print();
        }
        // ===========================================================
        // Put/Insert Internal Functions
        // ===========================================================
    private:
        avl_tree_node* rotate_right(avl_tree_node* u) {
            cout << "Rotating right at " << u->entry->key << "\n";
            avl_tree_node* v = u->left_child;
            avl_tree_node* t2 = v->right_child;
            u->left_child = t2;
            v->right_child = u;
            u->update_height();
            v->update_height();
            return v;
        }

        avl_tree_node* rotate_left(avl_tree_node* v) {
            cout << "Rotating left at " << v->entry->key << "\n";
            avl_tree_node* u = v->right_child;
            avl_tree_node* t2 = u->left_child;
            v->right_child = t2;
            u->left_child = v;
            v->update_height();
            u->update_height();
            return u;
        }

        avl_tree_node* insert(avl_tree_node* node, avl_tree_entry* entry) {
            if (!node) {
                mSize++;
                return new avl_tree_node(entry);
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
                int delta_height = height(node->left_child) - height(node->right_child);
                if (delta_height > 1) {
                    if (entry->key < node->left_child->entry->key) return rotate_right(node);
                    else {
                        node->left_child = rotate_left(node->left_child);
                        return rotate_right(node);
                    }
                } else if (delta_height < -1) {
                    if (entry->key < node->right_child->entry->key) {
                        node->right_child = rotate_right(node->right_child);
                        return rotate_left(node);
                    } else return rotate_left(node);
                } else /*-1<=delta_height<=1*/{
                    cout << "No Rotations at " << node->entry->key << "\n";
                    return node;
                }
            }
        }
        // ===========================================================
        // Find
        // ===========================================================
    public:
        avl_tree_iterator find(K k) {
            avl_tree_node* node = root;
            if (!node) return end();
            do {
                if (k < node->entry->key) node = node->left_child;
                else if (k > node->entry->key) node = node->right_child;
                else return avl_tree_iterator(node);
            } while (node);
            return end();
        }
        // ===========================================================
        // Erase
        // ===========================================================
    public:
        void erase(K k) {
            cout << "Deleting " << k << "\n";
            root = erase(root, k);
            mSize--;
            this->print();
        }
        void erase(avl_tree_iterator p) {
            cout << "Deleting " << p.node->entry->key << "\n";
            if (p == end()) {
                cout << "No such Node.\n";
                throw;
            }
            erase(p.node->entry->key);
            mSize--;
            this->print();
        }
    private:
        avl_tree_node* erase(avl_tree_node* node, K k) {
            // ===========================================================
            // Erase
            // ===========================================================
            if (!node) {
                cout << "No such Node.\n";
                throw;
            } else if (k < node->entry->key) node->left_child = erase(node->left_child, k);
            else if (k > node->entry->key) node->right_child = erase(node->right_child, k);
            else /* k==node->entry->key */{
                if (!node->left_child && !node->right_child) {
                    avl_tree_node* node2 = node;
                    node = NULL;
                    delete node2;
                } else if (!node->left_child || !node->right_child) {
                    avl_tree_node* node2 = node;
                    avl_tree_node* child = node->left_child ? node->left_child : node->right_child;
                    *node = *child;
                    delete child;
                } else {
                    avl_tree_node* min_right = node->right_child;
                    while (min_right->left_child)
                        min_right = min_right->left_child;
                    *(node->entry) = *(min_right->entry);
                    node->right_child = erase(node->right_child, min_right->entry->key);
                }
            }
            if (!node) return NULL;
            node->update_height();
            // ===========================================================
            // Balancing
            // ===========================================================
            int delta_height = height(node->left_child) - height(node->right_child);
            if (delta_height > 1) {
                if (node->left_child->left_child->height >= node->left_child->right_child->height) {
                    cout << "Rotating right at " << node->entry->key << "\n";
                    return rotate_right(node);
                } else {
                    cout << "Rotating left at " << node->left_child->entry->key << "\n";
                    node->left_child = rotate_left(node->left_child);
                    cout << "Rotating right at " << node->entry->key << "\n";
                    return rotate_right(node);
                }
            } else if (delta_height < -1) {
                if (node->right_child->left_child->height
                        <= node->right_child->right_child->height) {
                    cout << "Rotating right at " << node->right_child->entry->key << "\n";
                    node->right_child = rotate_right(node->right_child);
                    cout << "Rotating left at " << node->entry->key << "\n";
                    return rotate_left(node);
                } else {
                    cout << "Rotating left at " << node->entry->key << "\n";
                    return rotate_left(node);
                }
            } else /*-1<=delta_height<=1*/{
                cout << "No Rotations at " << node->entry->key << "\n";
                return node;
            }
            // ===========================================================
            return node;
        }
        // ===========================================================
        // Printing
        // ===========================================================
    private:
        void print(string prefix, avl_tree_node* node, bool left, bool root) {
            if (node->right_child) print(prefix + (!left || root ? "    " : "│   "),
                    node->right_child, false, false);
            cout << prefix << (root ? "X─── " : (left ? "└── " : "┌── ")) << "[" << node->entry->key
                    << "]\n";
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

#endif /* SRC_AVL_TREE_CPP_ */
