#include "avl_tree.cpp"
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
int main() {
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
        return 0;
    }
    for (int i = -10; i < 200; i++)
        cout << i << "->" << (is_pair_with_sum(tree, i) ? "YES" : "NO") << "\n";
}
