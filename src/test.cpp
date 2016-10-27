#include "avl_tree.cpp"
#include "red_black_tree.cpp"
#include "fstream"

using namespace std;

bool is_pair_with_sum(avl_tree<int, int>& tree, int sum) {
    avl_tree<int, int>::avl_tree_iterator it_left = tree.firstEntry();
    int min = (*tree.firstEntry()).key;
    int max = (*tree.lastEntry()).key;
    if (sum < min + (*tree.higherEntry(min)).key) return false;
    if (sum > max + (*tree.lowerEntry(max)).key) return false;
    for (avl_tree<int, int>::avl_tree_iterator it_right = tree.floorEntry(sum - (*it_left).key);
            (*it_left).key >= min && (*it_right).key <= max && (*it_right).key > (*it_left).key;) {
        int sum2 = (*it_left).key + (*it_right).key;
        if (sum2 == sum) {
            cout << "[" << (*it_left).key << "+" << (*it_right).key << "]: ";
            return true;
        } else if (sum2 > sum) it_right = tree.lowerEntry((*it_right).key);
        else it_left = tree.higherEntry((*it_left).key);
    }
    return false;
}

void avl_test() {
    avl_tree<int, int> tree;
    ifstream ifs;
    ifs.open("input.txt");
    if (ifs.is_open()) {
        int num;
        while (ifs >> num) {
            tree.put(num, 0);
        }
    } else {
        cout << "Could not open file 'input.txt'.\n";
        return;
    }
    //cout << 10 << "->" << (is_pair_with_sum(tree, 10) ? "YES" : "NO") << "\n";
    cout << string(100, '=') << "\n";
}

void rb_test() {
    red_black_tree<int, int> tree;
    ifstream ifs;
    ifs.open("input.txt");
    vector<int> vec;
    if (ifs.is_open()) {
        int num;
        while (ifs >> num) {
            vec.push_back(num);
            tree.insert(num, 0);
        }
    } else {
        cout << "Could not open file 'input.txt'.\n";
        return;
    }
    //cout << "Total Leaves = " << tree.leaves() << "\n";
    // cout << "Tree height = " << tree.height() << "\n";
    /* int a = 1000;
     int b = 2000;
     cout << "Keys between " << a << " and " << b << " are : ";
     vector<int> keys = tree.keys_between(a, b);
     for (int i = 0; i < keys.size(); i++)
     cout << keys[i] << ((i != keys.size() - 1) ? ", " : "");
     cout << "\n";*/
    // cout << string(100, '=') << "\n";
}
int main() {
    //avl_test();
    rb_test();
    return 0;
}
