#include "avl_tree.cpp"
#include "fstream"

using namespace std;

bool is_pair_with_sum(avl_tree<int, int>& tree, int sum) {
    avl_tree<int, int>::avl_tree_iterator it_left = tree.firstEntry();
    int min = (*tree.firstEntry()).key;
    int max = (*tree.lastEntry()).key;
    if (sum < min + (*tree.higherEntry(min)).key) return false;
    if (sum > max + (*tree.lowerEntry(max)).key) return false;
    for (avl_tree<int, int>::avl_tree_iterator it_right = tree.floorEntry(sum - (*it_left).key); (*it_left).key >= min && (*it_right).key <= max && (*it_right).key > (*it_left).key;) {
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

    //==========================================================================
    // TEST FUNCTION EXAMPLES
    //==========================================================================

    //INSERT
    //tree.put(256, 0);

    //DELETE
    //tree.erase((*tree.find(6)).key);
    //tree.erase(6);

    //FIND
    // avl_tree<int, int>::avl_tree_iterator it = tree.find(8);

    //LOWER_ENTRY
    // avl_tree<int, int>::avl_tree_iterator it = tree.lowerEntry(8);

    //HIGHER_ENTRY
    // avl_tree<int, int>::avl_tree_iterator it = tree.higherEntry(8);

    //CEILING_ENTRY
    // avl_tree<int, int>::avl_tree_iterator it = tree.ceilingEntry(8);

    //FLOOR_ENTRY
    // avl_tree<int, int>::avl_tree_iterator it = tree.floorEntry(8);

    //SIZE
    // cout<<tree.size()<<"\n";

    //EMPTY
    //cout << ((tree.empty()) ? "YES, EMPTY\n" : "NO, NOT EMPTY\n");

    //PAIR WITH SUM 10
    // int k=10;
    // cout << k << "->" << (is_pair_with_sum(tree, k) ? "YES" : "NO") << "\n";

    //PRINT
    //tree.print();

    //==========================================================================
    //Enter commands here...
    //==========================================================================
    cout << string(100, '=') << "\n";
}

int main() {
    avl_test();
    return 0;
}
