#include <vector>

#ifndef CP_ALGORITHMS_AND_TRICKS_SEGMENT_TREE_ABSTRACT_H
#define CP_ALGORITHMS_AND_TRICKS_SEGMENT_TREE_ABSTRACT_H

/**
 * SegTree();
 * SegTree(int size, merge _mFunc, T init_val);
 * void setDefaultVal(T val);
 * T getDefaultVal();
 * void pull(int v);
 * void build(int v, int tl, int tr, T a[]);
 * void build(T a[]);
 * void upd(int v, int tl, int tr, int pos, T x);
 * void upd(int pos, T x);
 * T get(int v, int tl, int tr, int L, int R);
 * T get(int pos);
 * @tparam T
 */
template<typename T>
class SegTree {
protected:
    std::vector <T> t;
    T default_val;
    int n = 0; // tree size
    typedef T (*merge)(T a, T b);
    merge mFunc;
public:

    SegTree() {}

    SegTree(int size, merge _mFunc, T init_val) {
        init(size, _mFunc, init_val);
    }

    void init(int size, merge _mFunc, T init_val) {
        this->mFunc = _mFunc;
        this->n = size;
        this->default_val = init_val;

        t.clear();
        t.resize(4 * size + 1);
        for (int i = 1; i <= 4 * size; i++) {
            t[i] = init_val;
        }
    }

    void setDefaultVal(T val) {
        this->default_val = val;
    }

    T getDefaultVal() {
        return this->default_val;
    }

    void pull(int v) {
        t[v] = this->mFunc(t[2 * v], t[2 * v + 1]);
    }

    void build(int v, int tl, int tr, T a[]) {
        if (tl == tr) {
            t[v] = a[tl];

            return;
        }
        int tm = (tl + tr) >> 1;
        build(2 * v, tl, tm, a);
        build(2 * v + 1, tm + 1, tr, a);
        pull(v);
    }

    void build(T a[]) {
        build(1, 1, this->n, a);
    }

    void upd(int v, int tl, int tr, int pos, T x) {
        if (tl == tr) {
            t[v] = x;

            return;
        }

        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            upd(2 * v, tl, tm, pos, x);
        } else {
            upd(2 * v + 1, tm + 1, tr, pos, x);
        }
        pull(v);
    }

    void upd(int pos, T x) {
        upd(1, 1, this->n, pos, x);
    }

    T get(int v, int tl, int tr, int L, int R) {
        if (L > R) {
            return default_val;
        }
        if (tl == L && tr == R) {
            return t[v];
        }

        int tm = (tl + tr) >> 1;

        T result;

        if (R <= tm) {
            result = get(2 * v, tl, tm, L, R);
        } else if (L > tm) {
            result = get(2 * v + 1, tm + 1, tr, L, R);
        } else {
            result = mFunc(get(2 * v, tl, tm, L, tm), get(2 * v + 1, tm + 1, tr, tm + 1, R));
        }

        return result;
    }

    T get(int L, int R) {
        return get(1, 1, this->n, L, R);
    }

    T get(int pos) {
        get(1, 1, this->n, pos, pos);
    }
};


#endif //CP_ALGORITHMS_AND_TRICKS_SEGMENT_TREE_ABSTRACT_H
