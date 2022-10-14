#include "segment_tree_composite.h"
#include "segment_tree_factory.h"
#include <iostream>

using namespace std;

int a[] = {0, 1, 2, 3, 4, 5};
int main() {
    int _size = sizeof(a) / sizeof(a[0]);
    int _init_val = 0;

    SegTreeFactory<int>* sum_factory = new SumSegTreeFactory<int>();
    SegTree<int>* sum_tree = sum_factory->create(_size, _init_val);

    _init_val = 1000000000;
    SegTreeFactory<int>* min_factory = new MinSegTreeFactory<int>();
    SegTree<int>* min_tree = min_factory->create(_size, _init_val);

    SegTreeComposite<int>* composite = new SegTreeComposite<int>();

    composite->add(sum_tree);
    composite->add(min_tree);

    composite->build(a);

    cout << sum_tree->get(1, 5) << endl;
    cout << min_tree->get(1, 5) << endl;

    composite->upd(1, 6);

    cout << sum_tree->get(1, 5) << endl;
    cout << min_tree->get(1, 5) << endl;
}
