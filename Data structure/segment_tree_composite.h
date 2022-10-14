#include "segment_tree_abstract.h"
#include <list>

#ifndef CP_ALGORITHMS_AND_TRICKS_SEGMENT_TREE_COMPOSITE_H
#define CP_ALGORITHMS_AND_TRICKS_SEGMENT_TREE_COMPOSITE_H


template<class T>
class SegTreeComposite {
protected:
    std::list<SegTree<T>* >children_;
public:
    void add(SegTree<T>* child) {
        this->children_.push_back(child);
    }
    void remove(SegTree<T>* child) {
        this->children_.remove(child);
    }
    void build(T a[]) {
        for (SegTree<T>* c : children_) {
            c->build(a);
        }
    }
    void upd(int pos, T x) {
        for (SegTree<T>* c : children_) {
            c->upd(pos, x);
        }
    }
};


#endif //CP_ALGORITHMS_AND_TRICKS_SEGMENT_TREE_COMPOSITE_H
