#include "red_black_tree.cpp"
#include "fstream"
#include <cstdlib>
#include <time.h>
#include <vector>

#define offset (RAND_MAX-1)/2

using namespace std;

void rb_test() {
    red_black_tree<int, int> tree;
    ifstream ifs;
    ifs.open("input.txt");
    if (ifs.is_open()) {
        int num;
        while (ifs >> num) {
            tree.insert(num, 0);
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
        cout << "1.Insert      2.Remove          3.Search          4.Leaves\n";
        cout << "5.Height      6.Keys Between    7.Exit\n";
        cout << string(100, '=') << "\n";
        cout << "Advanced Options:\n";
        cout << "8.Batch 'put'      9.Batch 'erase'\n";
        cout << string(100, '=') << "\n";
        int x;
        cin >> x;
        if (x == 1) {
            int k, v;
            cout << "Entry key:\n";
            cin >> k;
            cout << "Entry value:\n";
            cin >> v;
            keys_contained.push_back(k);
            tree.insert(k, v);
            tree.print();
        } else if (x == 2) {
            int k;
            cout << "Entry key:\n";
            cin >> k;
            if (tree.search(k) != tree.end()) tree.remove(k);
            else {
                cout << "Not found\n";
                continue;
            }
            tree.print();
        } else if (x == 3) {
            int k;
            cout << "Entry key:\n";
            cin >> k;
            if (tree.search(k) != tree.end()) cout << tree.search(k) << "\n";
            else cout << "Sorry not found.\n";
        } else if (x == 4) cout << "Leaves = " << tree.leaves();
        else if (x == 5) cout << "Height = " << tree.height() << "\n";
        else if (x == 6) {
            int a, b;
            cout << "Enter a and b:\n";
            cin >> a >> b;
            vector<int> vec = tree.keys_between(a, b);
            if (vec.size() == 0) cout << "No such keys\n";
            else {
                for (int i = 0; i < vec.size(); i++)
                    cout << vec[i] << ((i != vec.size() - 1) ? ", " : "\n");
            }
        } else if (x == 7) break;
        else if (x == 8) {
            srand(time(NULL));
            int n;
            cout << "Enter count of entries to add:\n";
            cin >> n;
            for (int i = 0; i < n; i++) {
                int k = rand() - offset, v = rand() - offset;
                keys_contained.push_back(k);
                tree.insert(k, v);
            }
        } else if (x == 9) {
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
                tree.remove(keys_contained[index]);
                keys_contained.erase(keys_contained.begin() + index);
            }
        }
    }
    //==========================================================================
    cout << string(100, '=') << "\n";
}
int main() {
    rb_test();
    return 0;
}
