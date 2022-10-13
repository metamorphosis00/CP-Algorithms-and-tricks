#include "segment_tree_abstract.h"

#ifndef CP_ALGORITHMS_AND_TRICKS_SEGMENT_TREE_FACTORY_H
#define CP_ALGORITHMS_AND_TRICKS_SEGMENT_TREE_FACTORY_H

template<class T> class SegTreeFactory {
public:
    virtual SegTree<T>* create(int size, T _init_val) = 0;
};
template<typename T> class SumSegTreeFactory : public SegTreeFactory<T> {
public:
    static T sum(T a, T b) {
        return a + b;
    }

    SegTree<T>* create(int size, T _init_val) {
        return new SegTree<int> (size, sum, _init_val);
    }
};

template<typename T> class MinSegTreeFactory : public SegTreeFactory<T> {
public:
    static int _min(int a, int b) {
        return ((a > b) ? b : a);
    }

    SegTree<T>* create(int size, T _init_val) {
        return new SegTree<T> (size, _min, _init_val);
    }
};
template<typename T> class MaxSegTreeFactory : public SegTreeFactory<T> {
public:
    static T _max(T a, T b) {
        return ((a > b) ? a : b);
    }

    SegTree<T>* create(int size, T _init_val) {
        return new SegTree<T> (size, _max, _init_val);
    }
};

#endif //CP_ALGORITHMS_AND_TRICKS_SEGMENT_TREE_FACTORY_H
