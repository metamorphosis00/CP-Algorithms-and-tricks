#include <iostream>
#include <stdio.h>

using namespace std;

const int N = 200000;
const int INF = 1000000000;

int readInt() {
    bool minus = false;
    int result = 0;
    char ch;
    ch = getchar();
    while (true) {
        if (ch == '-')
            break;
        if (ch >= '0' && ch <= '9')
            break;
        ch = getchar();
    }
    if (ch == '-')
        minus = true;
    else
        result = ch - '0';
    while (true) {
        ch = getchar();
        if (ch < '0' || ch > '9')
            break;
        result = result * 10 + (ch - '0');
    }
    if (minus)
        return -result;
    else
        return result;
}

struct node {
    int sum;
    int mn;
    int mx;
    int col;

    node() {
        sum = 0;
        mx = -INF;
        col = 0;
    }
};

struct segTree {
    int nn;
    node *t = new node[4 * N + 1];

    void init(int n) {
        this->nn = n;
        for (int i = 1; i <= 4 * n; ++i) {
            t[i].sum = 0;
            t[i].mx = -INF;
            t[i].col = 0;
        }
    }

    segTree(int n = 0) {
        init(n);
    }

    void pull(int v, int tl, int tr) {
        int tm = (tl + tr) >> 1;
        t[v].sum = t[2 * v].sum + (tm - tl + 1) * t[2 * v].col + t[2 * v + 1].sum + (tr - tm) * t[2 * v + 1].col;
        t[v].mx = max(t[2 * v].mx + t[2 * v].col, t[2 * v + 1].mx + t[2 * v + 1].col);
    }

    void push(int v) {
        t[2 * v].col += t[v].col;
        t[2 * v + 1].col += t[v].col;
        t[v].col = 0;
    }

    void set(int v, int x) {
        t[v].sum = x;
        t[v].mx = x;
    }

    void build(int v, int tl, int tr, int a[]) {
        if (tl == tr) {
            set(v, a[tl]);

            return;
        }
        int tm = (tl + tr) >> 1;
        build(2 * v, tl, tm, a);
        build(2 * v + 1, tm + 1, tr, a);
        pull(v, tl, tr);
    }

    void build(int a[]) {
        build(1, 1, this->nn, a);
    }

    void add(int v, int tl, int tr, int L, int R, int x) {
        if (tl == L && tr == R) {
            t[v].col += x;
            return;
        }
        push(v);
        int tm = (tl + tr) >> 1;
        if (R <= tm) {
            add(2 * v, tl, tm, L, R, x);
        } else if (L > tm) {
            add(2 * v + 1, tm + 1, tr, L, R, x);
        } else {
            add(2 * v, tl, tm, L, tm, x);
            add(2 * v + 1, tm + 1, tr, tm + 1, R, x);
        }
        pull(v, tl, tr);
    }

    void add(int L, int R, int x) {
        add(1, 1, this->nn, L, R, x);
    }

    node get(int v, int tl, int tr, int L, int R) {
        if (tl == L && tr == R) {
            node cur = t[v];
            cur.sum = t[v].sum + (tr - tl + 1) * t[v].col;
            cur.mx = t[v].mx + t[v].col;
            cur.mn = t[v].mn + t[v].col;

            return cur;
        }
        push(v);
        int tm = (tl + tr) >> 1;
        node result;
        node left;
        node right;

        if (R <= tm) {
            result = get(2 * v, tl, tm, L, R);
        } else if (L > tm) {
            result = get(2 * v + 1, tm + 1, tr, L, R);
        } else {
            left = get(2 * v, tl, tm, L, tm);
            right = get(2 * v + 1, tm + 1, tr, tm + 1, R);
            result.sum = left.sum + right.sum;
            result.mn = min(left.mn, right.mn);
            result.mx = max(left.mx, right.mx);
        }
        pull(v, tl, tr);

        return result;
    }

    node get(int L, int R) {
        return get(1, 1, this->nn, L, R);
    }
};

int a[N + 1];

int main() {
    int n = readInt(), m = readInt(), w = readInt();
    segTree tree(w);
    for (int i = 1; i <= n; i++) {
        int l = readInt(), r = readInt();
        ++l;
        ++r;
        tree.add(l,r,1);
    }
    for (int i = 1; i <= m; i++) {
        int x = readInt();
        ++x;
        cout<<tree.get(x,x).sum<<endl;
    }
}
