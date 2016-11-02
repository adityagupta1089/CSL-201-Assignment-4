#include "avl_tree.cpp"
#include "fstream"
#include <cstdlib>
#include <time.h>
#include <vector>

#define offset (RAND_MAX-1)/2

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
    vector<int> keys_contained;
    while (true) {
        cout << string(100, '=') << "\n";
        cout << "Enter Choice:\n";
        cout << " 1.First Entry       2.Last Entry      3.Ceiling Entry      4.Floor Entry      5.Lower Entry\n";
        cout << " 6.Higher Entry      7.Size            8.Empty              9.Find            10.Put\n";
        cout << "11.Erase            12.Exit           [Erase(rb_tree_iterator*) not testable in this UI]\n";
        cout << string(100, '=') << "\n";
        cout << "Advanced Options:\n";
        cout << "13.Batch 'put'      14.Batch 'erase'\n";
        cout << string(100, '=') << "\n";
        int x;
        cin >> x;
        if (x == 1) {
            if (tree.firstEntry() != tree.end()) cout << tree.firstEntry() << "\n";
            else cout << "Sorry not found.\n";
        } else if (x == 2) {
            if (tree.lastEntry() != tree.end()) cout << tree.lastEntry() << "\n";
            else cout << "Sorry not found.\n";
        } else if (x == 3) {
            int k;
            cout << "Entry key:\n";
            cin >> k;
            if (tree.ceilingEntry(k) != tree.end()) cout << tree.ceilingEntry(k) << "\n";
            else cout << "Sorry not found.\n";
        } else if (x == 4) {
            int k;
            cout << "Entry key:\n";
            cin >> k;
            if (tree.floorEntry(k) != tree.end()) cout << tree.floorEntry(k) << "\n";
            else cout << "Sorry not found.\n";
        } else if (x == 5) {
            int k;
            cout << "Entry key:\n";
            cin >> k;
            if (tree.lowerEntry(k) != tree.end()) cout << tree.lowerEntry(k) << "\n";
            else cout << "Sorry not found.\n";
        } else if (x == 6) {
            int k;
            cout << "Entry key:\n";
            cin >> k;
            if (tree.higherEntry(k) != tree.end()) cout << tree.higherEntry(k) << "\n";
            else cout << "Sorry not found.\n";
        } else if (x == 7) cout << "Size = " << tree.size() << "\n";
        else if (x == 8) cout << ((tree.empty()) ? "Yes, Empty\n" : "No, Not Empty\n");
        else if (x == 9) {
            int k;
            cout << "Entry key:\n";
            cin >> k;
            if (tree.find(k) != tree.end()) cout << tree.find(k) << "\n";
            else cout << "Sorry not found.\n";
        } else if (x == 10) {
            int k, v;
            cout << "Entry key:\n";
            cin >> k;
            cout << "Entry value:\n";
            cin >> v;
            keys_contained.push_back(k);
            tree.put(k, v);
            tree.print();
        } else if (x == 11) {
            int k;
            cout << "Entry key:\n";
            cin >> k;
            if (tree.find(k) != tree.end()) tree.erase(k);
            else {
                cout << "Not found\n";
                continue;
            }
            tree.print();
        } else if (x == 12) break;
        else if (x == 13) {
            srand(time(NULL));
            int n;
            cout << "Enter count of entries to add:\n";
            cin >> n;
            for (int i = 0; i < n; i++) {
                int k = rand() - offset, v = rand() - offset;
                keys_contained.push_back(k);
                tree.put(k, v);
            }
        } else if (x == 14) {
            srand(time(NULL));
            int n;
            cout << "Enter count of keys to remove:\n";
            cin >> n;
            if (n >= tree.size()) {
                cout << "Too many!\n";
                continue;
            }
            for (int i = 0; i < n; i++) {
                int index = rand() % keys_contained.size();
                tree.erase(keys_contained[index]);
                keys_contained.erase(keys_contained.begin() + index);
            }
        }
    }
//==========================================================================
    cout << string(100, '=') << "\n";
}

int main() {
    avl_test();
    return 0;
}
