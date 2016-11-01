#include "red_black_tree.cpp"
#include "fstream"

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
    // TEST FUNCTION EXAMPLES
    //==========================================================================

    //INSERT
    //tree.insert(256, 0);

    //DELETE
    //tree.remove((*tree.search(6)).key);
    //tree.remove(6);

    //FIND
    //red_black_tree<int, int>::rb_tree_iterator it = tree.search(8);

    //HEIGHT
    //cout << tree.height() << "\n";

    //KEYS BETWEEN A AND B
    //int a = 5;
    //int b = 10;
    //vector<int> vec = tree.keys_between(a, b);
    //cout << "[";
    //for (int i = 0; i < vec.size(); i++) {
    //    cout << vec[i] << ((i != vec.size() - 1) ? ", " : "]\n");
    //}

    //PRINT
    //tree.print();

    //LEAVES
    //cout << tree.leaves() << "\n";

    //==========================================================================
    //Enter commands here...

    //==========================================================================
    cout << string(100, '=') << "\n";
}
int main() {
    rb_test();
    return 0;
}
