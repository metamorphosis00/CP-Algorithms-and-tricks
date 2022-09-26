/**
Segment tree with following operations:
MULTIPLY SEGMENT [L;R] to X
ADD X TO SEGMENT [L;R]
GET SUM ON SEGMENT [L;R]
Sources:
https://discuss.codechef.com/t/addmul-editorial/11233
https://codeforces.com/blog/entry/16719?locale=ru
**/

#include <iostream>

#define int long long

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
    int mul;
    int add;

    node() {
        sum = 0;
        mul = 1;
        add = 0;
    }
};

struct segTree {
    int nn;
    node *t = new node[4 * N + 1];

    void init(int n) {
        this->nn = n;
        for (int i = 1; i <= 4 * n; ++i) {
            t[i].sum = 0;
            t[i].mul = 1;
            t[i].add = 0;
        }
    }

    segTree(int n = 0) {
        init(n);
    }

    void pull(int v, int tl, int tr) {
        int tm = (tl + tr) >> 1;
        t[v].sum = t[2 * v].sum * t[2 * v].mul + (tm - tl + 1) * t[2 * v].add + t[2 * v + 1].sum * t[2 * v + 1].mul +
                   (tr - tm) * t[2 * v + 1].add;
    }

    void push(int v) {
        t[2 * v].add *= t[v].mul;
        t[2 * v].add += t[v].add;
        t[2 * v + 1].add *= t[v].mul;
        t[2 * v + 1].add += t[v].add;

        t[2 * v].mul *= t[v].mul;
        t[2 * v + 1].mul *= t[v].mul;

        t[v].add = 0;
        t[v].mul = 1;
    }

    void set(int v, int x) {
        t[v].sum = x;
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
            t[v].add += x;
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

    void mul(int v, int tl, int tr, int L, int R, int x) {
        if (tl == L && tr == R) {
            t[v].add *= x;
            t[v].mul *= x;
            return;
        }

        push(v);

        int tm = (tl + tr) >> 1;

        if (R <= tm) {
            mul(2 * v, tl, tm, L, R, x);
        } else if (L > tm) {
            mul(2 * v + 1, tm + 1, tr, L, R, x);
        } else {
            mul(2 * v, tl, tm, L, tm, x);
            mul(2 * v + 1, tm + 1, tr, tm + 1, R, x);
        }

        pull(v, tl, tr);
    }

    void add(int L, int R, int x) {
        add(1, 1, this->nn, L, R, x);
    }

    void add(int pos, int x) {
        add(pos, pos, x);
    }

    void mul(int L, int R, int x) {
        mul(1, 1, this->nn, L, R, x);
    }

    void mul(int pos, int x)
    {
        mul(pos, pos, x);
    }

    void upd(int L, int R, int x) {
        mul(L, R, 0);
        add(L, R, x);
    }

    void upd(int pos, int x) {
        mul(pos, pos, x);
    }

    node get(int v, int tl, int tr, int L, int R) {
        if (tl == L && tr == R) {
            node cur = t[v];
            cur.sum = t[v].sum * t[v].mul + (tr - tl + 1) * t[v].add;

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
        }

        pull(v, tl, tr);

        return result;
    }

    node get(int L, int R) {
        return get(1, 1, this->nn, L, R);
    }

    node get(int pos) {
        get(pos, pos);
    }
};

int a[N];

main() {
    segTree tree;

    int n;
    cin >> n;

    tree.init(n);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    tree.build(a);

    int t;
    cin >> t;
    while (t--) {
        int tp, l, r, x;
        cin >> tp;
        if (tp == 1) {
            cin >> l >> r >> x;
            tree.mul(l, r, x); // multiply every element on segment [l;r] to x
        } else if (tp == 2) {
            cin >> l >> r >> x;
            tree.add(l, r, x); // add x to every element on segment [l;r]
        } else {
            cin >> l >> r;
            cout << tree.get(l, r).sum << endl; // get sum elements on segment [l;r]
        }
    }
}
