#include "segment_tree_factory.h"
#include <iostream>

using namespace std;

int a[] = {0, 1, 2, 3, 4, 5};
int main()
{
    int _size = sizeof(a) / sizeof(a[0]);
    int _init_val = 0;

    SegTreeFactory<int>* factory = new SumSegTreeFactory<int>();
    SegTree<int>* tree = factory->create(_size, _init_val);

    tree->build(a);
    cout << tree->get(1, 3) << endl;
    cout << tree->get(3, 5) << endl;
    tree->upd(1, 5);
    cout << tree->get(1, 3) << endl;
}
